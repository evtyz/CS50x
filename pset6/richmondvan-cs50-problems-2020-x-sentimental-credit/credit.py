from cs50 import get_int


def main():
    n = get_int("Number: ")
    if amex(n):
        print("AMEX")
    elif mastercard(n):
        print("MASTERCARD")
    elif visa(n):
        print("VISA")
    else:
        print("INVALID")


def amex(n):
    strn = str(n)
    possibilities = ["34", "37"]
    if len(strn) == 15 and strn[:2] in possibilities:
        return luhn(strn)
    return False


def mastercard(n):
    strn = str(n)
    possibilities = ["51", "52", "53", "54", "55"]
    if len(strn) == 16 and strn[:2] in possibilities:
        return luhn(strn)
    return False


def visa(n):
    strn = str(n)
    possibleDigits = [13, 16]
    if len(strn) in possibleDigits and strn[0] == "4":
        return luhn(strn)
    return False


def luhn(strn):
    sum = 0
    for x in range(1, len(strn)+1):
        num = int(strn[len(strn)-x])
        if x % 2 == 1:
            sum += num
        else:
            strnum = str(2 * num)
            for y in range(len(strnum)):
                sum += int(strnum[y])
    if sum % 10 == 0:
        return True
    return False


main()
