import cs50
import csv
from sys import argv, exit

if len(argv) != 2:
    print("usage: python import.py file.csv")
    exit(1)
else:
    csvFile = argv[1]

open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")
db.execute("CREATE TABLE students (id INTEGER PRIMARY KEY AUTOINCREMENT, first VARCHAR(255), middle VARCHAR(255), last VARCHAR(255), house VARCHAR(10), birth INTEGER);")

with open(csvFile, "r") as characters:
    reader = csv.DictReader(characters, delimiter=",")
    identity = 0
    for row in reader:
        names = row["name"].split(" ")
        if len(names) == 2:
            first = names[0]
            last = names[1]
            middle = None
        else:
            first = names[0]
            middle = names[1]
            last = names[2]
        house = row["house"]
        birth = int(row["birth"])
        db.execute("INSERT INTO students (id, first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?, ?);",
                   identity, first, middle, last, house, birth)
        identity += 1

exit(0)