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
current_c = 0

# Open CSV file into dictionary
with open(database, 'r') as csv_file:
    db = csv.DictReader(csv_file)
    # Save the STRs on a list
    STRs = db.fieldnames
    # Remove first fieldname because we don't need the name here
    STRs.pop(0)

# Open .txt
with open(sequence, 'r') as txt_file:
    dna = txt_file.read()

# Inicializo lista donde voy a guardar para cada STR el maximo numero de repeticiones
max_count = [0] * len(STRs)
# For each STR we are going to check the sequence to see the matches
j = 0
# Lenght of DNA sequence
a = len(dna)
# For each STR we are going to check the matches


for i in range(0,len(STRs)):
    # Lenght of the current STR
    b = len(STRs[i])
    # For each position on the sequence we are going to count on that point foward, how many times the STR repeats
    for j in range(0,a):
        # Mientras que la secuencia se repita consecutivamente, voy a incrementar el contador y j va a avanzar la longitud del STR en cuestion
        # , para ver si se repite
        while STRs[i] == dna[j:b + j]:
            current_c = current_c + 1
            j = j + b
        if current_c > maxSTRc:
            maxSTRc = current_c
        # Reset the counter to prepare for next position
        current_c = 0
    # Ahora ya chequee todas las posiciones, por lo que maxSTRc tiene que ser el maximo numero de sequencias repetidas, lo pongo en la lista
    max_count[i] = maxSTRc
    # Reset the counter to prepare for next STR
    maxSTRc = 0

match = False
print(max_count)
with open(database, 'r') as csv_file:
    db = csv.DictReader(csv_file)
    for row in db:
        #print(row['name'])
        j = 0
        for i in range(len(STRs)):
            if max_count[i] == int(row[STRs[i]]):
                j = j + 1
                if j == len(max_count) - 1:
                    match = True
                    name = row['name']
            else:
                j = 0

if match == True:
    print(name)
else:
    print("No match")
















