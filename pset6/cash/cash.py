from cs50 import get_float

owed = 0
owed_change = 0
i = 0

owed = get_float("Owed: ")
while owed <= 0.00:
    owed = get_float("Owed: ")
owed = float(owed)
owed_change = round(owed*100)
while owed_change != 0:
    if owed_change >= 25:
        owed_change = owed_change - 25
    elif 10 <= owed_change < 25:
        owed_change = owed_change - 10
    elif    5 <= owed_change < 10:
        owed_change = owed_change - 5
    else:
        owed_change = owed_change - 1
    i = i + 1
print(i)