# Workers and Resources Production Calculator
Production Calculator for the game Workers and Resources: Soviet Republic programmed in C.

# How to run it
To run it, compile it with GCC and run the executable. There's a Linux build script which you can modify for your own uses.

# License
The code is free and open source. You can download it, run it, modify it and redistribute it (GPLv3). Just credit me if you make a fork, ok?

# Stuff I haven't done yet
Right now the only production chain able to be calculated is food. You can calculate water as well, for example, because it's interlaced with food, but the objective is to put every factory in the game in this algorithm to actually have it compute everything from scratch.

I don't know yet if I want to put stuff like nuclear of vehicle production chains in here right now because those are rather complex. I want to focus more on the normal factories (coal, iron, food, electronics, clothes, etc).

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
[... so on and so on ...]
water:
  Amount: 181.500000
  Factory Count: 1.000000

Industry-made sewage to take care of: 181.500000

Workers needed: 2370
```
