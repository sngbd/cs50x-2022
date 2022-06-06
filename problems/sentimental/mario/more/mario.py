# Import get_int function from cs50 python library
from cs50 import get_int

# do while python equivalent
while True:
    height = get_int("Height: ")
    if height in range(1, 9):
        for i in range(1, height+1):
            print(" " * (height - i), end="")
            print("#" * i, end="")
            print("  ", end="")
            print("#" * i)
        break