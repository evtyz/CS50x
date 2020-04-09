from cs50 import get_int

while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

for i in range(height):
    print(" " * (height - 1 - i) + "#" * (i + 1) + " " * 2 + "#" * (i + 1))

