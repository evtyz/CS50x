from cs50 import get_string


def main():
    text = get_string("Text: ")
    W = w(text)
    L = l(text)/(W/100)
    S = s(text)/(W/100)
    index = round(0.0588 * L - 0.296 * S - 15.8)
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade", index)


def w(text):
    counter = 1
    for x in range(len(text)):
        if text[x] == " ":
            counter += 1
    return counter


def l(text):
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    counter = 0
    for x in range(len(text)):
        if text[x].lower() in alphabet:
            counter += 1
    return counter


def s(text):
    alphabet = ".?!"
    counter = 0
    for x in range(len(text)):
        if text[x] in alphabet:
            counter += 1
    return counter


main()
