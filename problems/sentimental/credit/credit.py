# Imports get_string and get_int function from cs50 library
from cs50 import get_string, get_int

# Do while python equivalent
while True:
    number = get_int("Number: ")
    if number > 0:
        break
# Converts integer to string
strnumber = str(number)
length = len(strnumber)
sum = 0
# Multiplies numbers and adds products' digits starting with number's second-to-last digit
for i in range(length - 2, -1, -2):
    mult = int(strnumber[i]) * 2
    ld = mult // 10
    rd = mult % 10
    sum += ld + rd
# Adds the remaining digits
for i in range(length - 1, -1, -2):
    sum += int(strnumber[i])
# Prints output
if sum % 10 == 0:
    td = int(strnumber[:2])
    if td == 34 or td == 37:
        print("AMEX")
    elif td in range(51, 56):
        print("MASTERCARD")
    elif int(strnumber[:1]) == 4:
        print("VISA")
else:
    print("INVALID")