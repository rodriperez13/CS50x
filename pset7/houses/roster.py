import sys
import csv
from cs50 import SQL

if len(sys.argv) != 2:
    print("Usage: python roster.py house")
    sys.exit(1)

db = SQL("sqlite:///students.db")

house = sys.argv[1]

if house != "Gryffindor" and house != "Hufflepuff" and house != "Ravenclaw" and house != "Slytherin":
    print("Please enter a valid house name")
    sys.exit(1)

data = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", house)
for i in data:
    if i['middle'] == None:
        print(str(i['first']) + " " + str(i['last']) + ", born " + str(i['birth']))
    else:
        print(str(i['first']) + " " + str(i['middle']) + " " + str(i['last']) + ", born " + str(i['birth']))
