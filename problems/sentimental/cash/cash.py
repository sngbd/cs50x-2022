# Import get_float function from cs50 python library
from cs50 import get_float

# Main function


def main():
    while True:
        dollars = get_float("Change owed: ")
        if dollars > 0:
            break
    cents = int(dollars * 100)

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(f"{coins}")


def calculate_quarters(cents):
    x = cents // 25
    return x


def calculate_dimes(cents):
    x = cents // 10
    return x


def calculate_nickels(cents):
    x = cents // 5
    return x


def calculate_pennies(cents):
    x = cents // 1
    return x


main()
