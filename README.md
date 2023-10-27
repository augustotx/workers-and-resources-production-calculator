# Workers and Resources Production Calculator
Production Calculator for the game Workers and Resources: Soviet Republic programmed in C.

Honestly, I don't even know if this program is correct, but I hope it is lol

# How to run it
To run it, compile it with GCC and run the executable. There's a build script which you can modify for your own uses.

You can also just download it from the releases tab, but I wouldn't recommend it because I pretend to change it all the time, and I don't really know much about releases on github.

# License
The code is free and open source. You can download it, run it, modify it and redistribute it (GPLv3). Just credit me if you make a fork, ok?

# Stuff I haven't done yet
Right now basically everything works. You can calculate every factory's production line from top to bottom. The next thing is to put vehicle production chains. I also want to calculate if the production chain is enough for the amount of workers it requires (e.g. if food production sustains the workers it requires and if there's anything remaining, as well as how many remaining workers that food factory can feed).

# Example output
```
Welcome to the calculator, comrade!
Ready to build your republic?
Choose a factory type: (type in "list" to see options)
-> electronics

Type in the amount of factories you want to account for.
-> 1
Remaining resources from factories (able to export):

gravel:
  Amount: 77.680000
  Factory Count: 1.000000
stone:
  Amount: 20.000000
  Factory Count: 1.000000
coal ore:
  Amount: 84.000000
  Factory Count: 1.000000
coal:
  Amount: 105.000000
  Factory Count: 4.000000
iron ore:
  Amount: 550.000000
  Factory Count: 1.000000
iron:
  Amount: 10.000000
  Factory Count: 2.000000
steel:
  Amount: 19.300000
  Factory Count: 1.000000
wood:
  Amount: 184.080000
  Factory Count: 1.000000
crops:
  Amount: 0.240000
  Factory Count: 6.000000
chemicals:
  Amount: 0.060000
  Factory Count: 6.000000
plastics:
  Amount: 2.400000
  Factory Count: 1.000000
mechanical components:
  Amount: 31.300000
  Factory Count: 1.000000
electronic components:
  Amount: 1.700000
  Factory Count: 1.000000
electronics:
  Amount: 4.100000
  Factory Count: 1.000000
oil:
  Amount: 2.800000
  Factory Count: 41.000000
fuel:
  Amount: 114.000000
  Factory Count: 1.000000
bitumen:
  Amount: 75.000000
  Factory Count: 1.000000
water:
  Amount: 140.000000
  Factory Count: 1.000000

Industry-made sewage to take care of: 60.000000

Workers needed: 7020

University workers needed: 0
```
