#include "guifunc.h"
#include "../func.h"
#include <string.h>
#define RESOURCE_COUNT 40

// GUI builder pointer
GtkBuilder *ui_builder = NULL;

// Template strings
char gui_workers_label_template[256];
char gui_waste_label_template[256];

void gui_copy_label_text(GtkLabel *label, gchararray str)
{
    const char *text = gtk_label_get_text(label);
    if (!str)
        free(str);
    strcpy(str, text);
}

gchar *gui_find_resource_name(gint64 id)
{
    GtkTreeModel *resources_list = GTK_TREE_MODEL(gtk_builder_get_object(ui_builder, "resources_list"));
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first (resources_list, &iter);
    while (valid)
    {
        gchar *got_name;
        gint64 got_id;
        gboolean sensitive;
        gtk_tree_model_get(resources_list, &iter, 0, &got_id, 1, &got_name, 2, &sensitive, -1);
        if (sensitive && got_id == id) {
            return got_name; // Do not forget to call g_free() after use
        }
        g_free(got_name);
        valid = gtk_tree_model_iter_next(resources_list, &iter);
    }
    return NULL; // Not found
}

gint64 gui_get_factory_type()
{
    GtkTreeModel *resources_list = GTK_TREE_MODEL(gtk_builder_get_object(ui_builder, "resources_list"));
    GtkComboBox *cb = GTK_COMBO_BOX(gtk_builder_get_object(ui_builder, "calculated_resource_combobox"));
    GtkTreeIter iter;
    gint64 type = -1;
    
    gboolean ok = gtk_combo_box_get_active_iter(cb, &iter);
    if (ok)
        gtk_tree_model_get(resources_list, &iter, 0, &type, -1);
    return type;
}

gint gui_get_factory_amount()
{
    GtkSpinButton *spin = GTK_SPIN_BUTTON(gtk_builder_get_object(ui_builder, "factory_number_spin"));
    return gtk_spin_button_get_value_as_int(spin);
}

void gui_init()
{
    gtk_init(NULL, NULL);
    
    // UI Builder
    GError *err = NULL;
    ui_builder = gtk_builder_new();
    
    // Loading GUI from a Glade file
    if(!gtk_builder_add_from_file(ui_builder, "gui/mainwindow.glade", &err)) {
        g_critical("Failed to load UI file: %s", err->message);
        g_error_free(err);
    }

    // Main window widget
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(ui_builder, "main_window"));

    // Set template strings
    GtkLabel *workers_label = GTK_LABEL(gtk_builder_get_object(ui_builder, "workers_label"));
    GtkLabel *waste_label = GTK_LABEL(gtk_builder_get_object(ui_builder, "waste_label"));
    gui_copy_label_text(workers_label, gui_workers_label_template);
    gui_copy_label_text(waste_label, gui_waste_label_template);

    // Widgets with signals
    GtkWidget *start_button = GTK_WIDGET(gtk_builder_get_object(ui_builder, "start_button"));
    GtkWidget *factory_number_spin = GTK_WIDGET(gtk_builder_get_object(ui_builder, "factory_number_spin"));

    // Signal connection
    gtk_builder_connect_signals(ui_builder, NULL);
    g_signal_connect(G_OBJECT(start_button), "clicked", G_CALLBACK(gui_start_clicked), NULL);
    g_signal_connect(G_OBJECT(factory_number_spin), "value-changed", G_CALLBACK(gui_check_factory_amount), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // Exit callback

    // Set GUI elements to their initial state
    gui_check_factory_amount(factory_number_spin, NULL);
    gui_clear_results();

    // Show the main window and run its loop
    gtk_widget_show_all(window);
    gtk_main();
}

void gui_add_result_resource(gchararray name, gdouble amount, guint factories)
{
    GtkListStore *result_list = GTK_LIST_STORE(gtk_builder_get_object(ui_builder, "result_list"));
    GtkTreeIter iter; // Iterator of the new row in gtk_list_store
    gtk_list_store_append(result_list, &iter); 
    gtk_list_store_set(result_list, &iter, 0, name, 1, amount, 2, factories, -1);
}

void gui_set_workers(guint total, guint educated)
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(ui_builder, "workers_label"));
    char str[256];
    sprintf(str, gui_workers_label_template, total, educated);
    gtk_label_set_text(label, str);
}

void gui_set_sewage(gdouble amount)
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(ui_builder, "waste_label"));
    char str[256];
    sprintf(str, gui_waste_label_template, amount);
    gtk_label_set_text(label, str);
}

void gui_clear_results()
{
    GtkListStore *result_list = GTK_LIST_STORE(gtk_builder_get_object(ui_builder, "result_list"));
    gtk_list_store_clear(result_list);

    gui_set_workers(0, 0);
    gui_set_sewage(0);   
}

void gui_results(struct factory *resource_pool, double factory_count[],
                 int worker_population, int university_worker_population, double sewage)
{
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        double amount = resource_pool->inputs[i];
        if (amount != 0.0)
        {
            char *name = gui_find_resource_name(i); 
            gui_add_result_resource(name, amount, factory_count[i]);
            g_free(name);
        }
    }
    if (resource_pool->inputs[39] > 0.0)
        gui_set_sewage(sewage);
    gui_set_workers(worker_population, university_worker_population);
}

void gui_start_clicked(GtkWidget *button, gpointer data)
{
    // Clear old results
    gui_clear_results();

    // Get data from GUI
    gint64 type = gui_get_factory_type();
    gint amount = gui_get_factory_amount();
    // g_print("Type: %li, amount: %d\n", type, amount);

    // TODO: refactor code copied from ../main.c
    struct factory *resource_pool = malloc(sizeof(struct factory));
    zerofactory(resource_pool);
    double factory_count[RESOURCE_COUNT] = {0.0};

    char resourceNames[RESOURCE_COUNT][64];
    define_resource_names(resourceNames);

    int worker_population = 0;
    int university_worker_population = 0;
    double sewage = 0.0;

    struct factory *factory = malloc(sizeof(struct factory));
    newfactory(factory, type);

    calculate(factory, amount, resource_pool, factory_count, resourceNames, &worker_population, &university_worker_population, &sewage);
    gui_results(resource_pool, factory_count, worker_population, university_worker_population, sewage);

    free(factory);
    free(resource_pool);
}

void gui_check_factory_amount(GtkSpinButton *spin_button, gpointer data)
{
    GtkWidget *start_button = GTK_WIDGET(gtk_builder_get_object(ui_builder, "start_button"));
    gint amount = gui_get_factory_amount();
    gtk_widget_set_sensitive(start_button, amount > 0);
}