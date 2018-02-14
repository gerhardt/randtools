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

import struct
import sys

if len(sys.argv) > 3:
   infile=str(sys.argv[1])
   outfile=str(sys.argv[2])
   timediff=int(sys.argv[3])
elif len(sys.argv) > 2:
   infile=str(sys.argv[1])
   outfile=infile.rsplit('.')[0]+"_"+str(sys.argv[2])+".sel"
   timediff=int(sys.argv[2])
else:
   print "usage: ./dat2sel.py infile (outfile) timerange"
   exit (1)

def tims(arr):
   bu=0
   apd=int(ord(arr[4]))
   if len(arr) == 16:
      for i in xrange(8):
         bu+=int(ord(arr[15-i]))*256**(7-i)
   else:
      bu=-1
      apd=-1
   return apd,bu

with open(infile,'rb') as f1:
    with open(outfile,'wb') as f2:
        oldtime=0;oldapd=0;
        while True: 
           buf=f1.read(16)
           if buf:
              thisapd,thistime=tims(buf)
              diff=oldtime-thistime
              if abs(diff)<=timediff:
                 if thisapd==0:
                    diff=-diff;
                 # f2.write(str(oldapd)+" "+str(thisapd)+" "+str(diff)+"\n")
                 f2.write(chr(2*int(oldapd)+int(thisapd)))
                 f2.write(struct.pack('<i', diff))
              oldtime=thistime
              oldapd=thisapd
           else:
              break

f1.close()
f2.close()
