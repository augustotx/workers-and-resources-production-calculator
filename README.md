# Workers and Resources Production Calculator
Production Calculator for the game Workers and Resources: Soviet Republic programmed in C.

Honestly, I don't even know if this program is correct, but I hope it is lol

# How to run it
To run it, compile it with GCC and run the executable. There's a Linux build script which you can modify for your own uses.

# License
The code is free and open source. You can download it, run it, modify it and redistribute it (GPLv3). Just credit me if you make a fork, ok?

# Stuff I haven't done yet
Right now the production chains I've tested to work are food and steel. You can calculate water or chemicals or wood as well, for example, because they're in the food production, but the objective is to put every factory in the game in this algorithm to actually have it compute everything from scratch.

I don't know yet if I want to put stuff like nuclear or vehicle production chains in here right now because those are rather complex. I want to focus more on the normal factories (coal, iron, food, electronics, clothes, etc) and then put in the complex stuff.

After all that is done, I want to calculate if the production chain is enough for the amount of workers it requires (e.g. if food production sustains the workers it requires and if there's anything remaining).

# Example output
```
Welcome to the calculator, comrade!
Ready to build your republic?
Choose a factory type: (e.g. gravel, food, electronic components, etc)
-> food

Type in the amount of factories you want to account for.
-> 1

Remaining resources from factories (able to export):

gravel:
  Amount: 81.280000
  Factory Count: 1.000000
stone:
  Amount: 20.000000
  Factory Count: 1.000000
wood:
  Amount: 188.180000
  Factory Count: 1.000000
crops:
  Amount: 0.680000
  Factory Count: 53.000000
chemicals:
  Amount: 0.310000
  Factory Count: 1.000000
food:
  Amount: 20.000000
  Factory Count: 1.000000
oil:
  Amount: 0.800000
  Factory Count: 36.000000
fuel:
  Amount: 43.500000
  Factory Count: 1.000000
bitumen:
  Amount: 75.000000
  Factory Count: 1.000000
water:
  Amount: 181.500000
  Factory Count: 1.000000

Industry-made sewage to take care of: 18.500000

Workers needed: 2370
```
