# Breakout
Breakout game written in C for linux terminal.

# Compiling
gcc collision.c draw.c input.c logic.c main.c nextLvl.c -lm -o game

# Running
./game

# Controls
Left/Right key for movement \
'Q' - quit

# Resolution
Resize terminal or use *--no-res* option

# Level Building
**1.** First line must contain the exact number of bricks \
the number not being larger than three digits.
**2.** Adjacent characters are considered an entire unit.
