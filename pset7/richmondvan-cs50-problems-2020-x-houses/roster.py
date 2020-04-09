# TODO
import cs50
from sys import argv, exit

if len(argv) != 2:
    print("usage: python import.py file.csv")
    exit(1)
else:
    house = argv[1]

db = cs50.SQL("sqlite:///students.db")
results = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first;", house)

for row in results:
    print(row['first'], end=" ")
    if row['middle'] != None:
        print(row['middle'], end=" ")
    print(row['last'] + ",", f"born {row['birth']}")

