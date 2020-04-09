import csv
from sys import argv, exit


def main():

    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    databasetemp = []
    with open(argv[1], newline='') as csvfile:
        databasereader = csv.reader(csvfile, delimiter=' ', quotechar='|')
        for row in databasereader:
            databasetemp.append(row[0].split(','))
    listSTR = databasetemp[0][1:]

    database = []
    for i in range(1, len(databasetemp)):
        database.append([databasetemp[i][0], []])
        for j in range(1, len(databasetemp[i])):
            database[i - 1][1].append(int(databasetemp[i][j]))
    
    with open(argv[2], 'r') as f:
        dna = f.read()
    dnaSTR = []
    
    for STR in listSTR:
        lengthSTR = len(STR)
        consec = 0
        currentconsec = 0
        i = 0
        while i <= len(dna):
            if dna[i:i + lengthSTR] == STR:
                currentconsec += 1
                i = i + lengthSTR
            else:
                if currentconsec > consec:
                    consec = currentconsec
                currentconsec = 0
                i += 1
        
        if currentconsec > consec:
            consec = currentconsec
        dnaSTR.append(consec)
    
    for person in database:
        possible = True
        for i in range(len(person[1])):
            if dnaSTR[i] != person[1][i]:
                possible = False
                break
        if possible:
            print(person[0])
            exit(0)
    print("No match")


main()