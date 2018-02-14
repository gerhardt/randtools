#!/usr/bin/python
# 
# Copyright (c) 2018 Ilja Gerhardt, ilja@quantumlah.org
# 
# This program is free software: you can redistribute it and/or modify  
# it under the terms of the GNU General Public License as published by  
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#


import sys
import os

if len(sys.argv) > 2:
   infile=str(sys.argv[1])
   outfile=str(sys.argv[2])
elif len(sys.argv) > 1:
   infile=str(sys.argv[1])
   outfile=infile.rsplit('.')[0]+".bin"
else: 
   print "usage: ./dat2bin.py infile (outfile)"
   exit (1)

with open(infile,'rb') as f1:
    with open(outfile,'wb') as f2:
        while True: 
            buf=f1.read(8*16)
            if buf: 
                myb=0
                for i in xrange(8):
                    # print int(ord(buf[16*i+4]))*2**(7-i)
                    myb+=int(ord(buf[16*i+4]))*2**(7-i)
                f2.write(chr(myb))
            else:
                break

f1.close()
f2.close()
