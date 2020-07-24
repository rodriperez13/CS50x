import cs50

# 0.0588 * L - 0.296 * S - 15.8
# L = Average number of letters per 100 words
# S = Average number of sentences per 100 words

# j = contador de letras
j = 0.00

# k = Contador de palabras
k = 0.00

# z = contador de oraciones
z = 0.00

text = input("Text: ")
for i in range(len(text)):
    if (text[i] >= "a" and text[i] <= "z") or (text[i] >= "A" and text[i] <= "Z"):
        j = j + 1;
    elif (text[i] == " "):
        k = k + 1
    elif text[i] == "." or text[i] == "!" or text[i] == "?":
        z = z + 1

k = k + 1
l = (100 * j / k)
s = (100 * z / k )

grade = round(0.0588 * l - 0.296 * s - 15.8)

if grade >= 1 and grade <= 16:
    print("Grade " + str(grade))
elif grade < 1:
    print("Before Grade 1")
else:
    print("Grade 16+")