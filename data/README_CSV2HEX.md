# Generate ".hex" file from csv

- Open the given ".ods" file
- Modify all the values necessaries for the case
- Save the last sheet ("EE Data") as ".csv"
- Run the csv2hex.py script, for help: `./csv2hex.py -h`

### Libraries requiered:
- optparse
- intelhex

### Example run:
`./csv2hex.py -f /some/file.csv -o output/file.hex`
