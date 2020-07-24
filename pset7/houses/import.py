import sys
import csv
from cs50 import SQL

if len(sys.argv) != 2:
    print("Usage: python import.py data.csv")
    sys.exit(1)

db = SQL("sqlite:///students.db")

with open(sys.argv[1],'r') as csv_file:
    characters = csv.DictReader(csv_file)
    for row in characters:
        tmp = row['name'].split()
        house = row['house']
        birth = row['birth']
        if len(tmp) == 2:
           first_name = tmp[0]
           middle_name = None
           last_name = tmp[1]
        else:
            first_name = tmp[0]
            middle_name = tmp[1]
            last_name = tmp[2]
        insert = [(first_name, middle_name, last_name, house, birth)]
        db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)', first_name, middle_name, last_name, house, birth)

