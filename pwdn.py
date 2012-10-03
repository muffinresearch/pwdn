#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""Simple command that prints out the current n last levels of the CWD 
replacing the prefix with a horizontal ellipsis

Usage pwdn [numdirs]

"""

from os import getcwd
from sys import argv, exit

try:
    numdir = (len(argv) > 1) and int(argv[1]) or 2
except ValueError:
    print "Usage: pwdn [numdirs]"
    exit(1)

cwd = getcwd()[1:].split("/")
print "%s%s" % (len(cwd) > numdir and "…/" or "/", '/'.join(cwd[-numdir:]))
exit(0)
