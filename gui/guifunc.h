#ifndef GUIFUNC_H
#define GUIFUNC_H
#include <gtk/gtk.h>
#include "../vars.h"

// GUI data fetch functions
void gui_copy_label_text(GtkLabel *label, gchararray str);
gchar *gui_find_resource_name(gint64 id);
gint64 gui_get_factory_type();
gint gui_get_factory_amount();

// GUI update functions
void gui_init(); // Start GUI
void gui_add_result_resource(gchararray name, gdouble amount, guint factories); // Add a resource to the result table
void gui_set_workers(guint total, guint educated); // Set number of required workers in GUI
void gui_set_sewage(gdouble amount); // Set displayed sewage amount

void gui_clear_results(); // Clear results
// Replacement for results() function from ../func.h
void gui_results(struct factory *resource_pool, double factory_count[],
                 int worker_population, int university_worker_population, double sewage);

// Callbacks
void gui_start_clicked(GtkWidget *button, gpointer data);
void gui_check_factory_amount(GtkSpinButton *spin_button, gpointer data);
#endif