#!/usr/bin/python
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
        data.append(l[opts.col])
    fsource.close()
    ih = IntelHex()
    for n in range(opts.row, len(data)):
        ih[n-opts.row] = int(data[n])
    ih.tofile(opts.out, format='hex')


def init_parser():
    parser = OptionParser()
    parser.add_option('-f', '--file', help='Input csv file (REQUIRED)',
                      dest='file', action='store')
    parser.add_option('-o', '--output', help='Output hex file (REQUIRED)',
                      dest='out', action='store')
    parser.add_option('-d', '--delimitier', help='Delimiter used for csv '
                      'separation (default ",")', dest='delim',
                      action='store', default=',')
    parser.add_option('-c', '--column', help="Number of column where the"
                      " data is located (starts at 0)", dest='col',
                      action='store', type=int, default=-2)
    parser.add_option('-r', '--row', help="Number of row where the data "
                      "is located (starts at 0)", dest='row', action='store',
                      type=int, default=5)
    (opts, args) = parser.parse_args()
    mandatory = ['file', 'out']
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
