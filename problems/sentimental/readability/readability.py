# Imports get_string from cs50 library
from cs50 import get_string


def main():
    text = get_string("Text: ")
    let = count_letters(text)
    wor = count_words(text)
    sen = count_sentences(text)
    L = let / wor * 100
    S = sen / wor * 100
    # Calculates index
    index = round(0.0588 * L - 0.296 * S - 15.8)
    # Checks grade
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


# Counts letters
def count_letters(text):
    let = 0
    for i in text:
        if ord(i.upper()) >= 65 and ord(i.upper()) <= 90:
            let += 1
    return let


# Counts words
def count_words(text):
    wor = 0
    for i in text:
        if i == ' ':
            wor += 1
    return wor + 1


# Counts sentences
def count_sentences(text):
    sen = 0
    for i in text:
        if i == '.' or i == '!' or i == '?':
            sen += 1
    return sen


main()