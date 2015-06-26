from optparse import OptionParser
from intelhex import IntelHex
import os
import csv


def main():
    (opts, args) = init_parser()
    fsource = open(opts.file, 'r')
    reader = csv.reader(fsource, delimiter=opts.delim)
    data = []
    for l in reader:
        data.append(l[-1])
    fsource.close()
    ih = IntelHex()
    for n in range(4):
        data.pop(0)
    for n in range(len(data)):
        ih[n]=int(data[n])
    ih.tofile(opts.out, format='hex')

def init_parser():
    parser = OptionParser()
    parser.add_option('-f', '--file', help='Input csv file (REQUIRED)', dest='file', action='store')
    parser.add_option('-o', '--output', help='Output hex file (REQUIRED)', dest='out', action='store')
    parser.add_option('-d', '--delimitier', help='Delimiter used for csv separation', dest='delim', action='store', default=',')
    (opts, args) = parser.parse_args()
    mandatory = ['file','out']
    for m in mandatory:
        if not opts.__dict__[m]:
            parser.print_help()
            exit()
    if not os.access(opts.file, os.R_OK):
        print("File is not readable check permissions!")
        exit()
    return (opts, args)

if __name__ == "__main__":
    main()
