import sys
import csv

# Checking proper usage.
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)

# Storing which sequeance and database are going to be used

sequence = sys.argv[2]
database = sys.argv[1]

# Initialize counters
maxSTRc = 0
currentSTRc = 0

# Open CSV file into dictionary
with open(database, 'r') as csv_file:
    db = csv.reader(csv_file)
    for row in reader
# Open .txt
with open(sequence, 'r') as txt_file:
    dna = txt_file.read()

lenght = len(dna)

# iteration
#print(dna[0:4])

type(db)

