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

if len(sys.argv) > 1:
   linestoread=int(sys.argv[1])
else: 
   print "usage: ./tss.py num"
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

lins=abs(linestoread)
fin='/home/ilja/science/projects/trng/data/2017/05/24/a60cde33.dat'
lele=os.stat(fin)[6]

with open(fin,'rb') as f1:
   if linestoread<0:
       f1.seek(lele-16*lins)
   for xx in xrange(lins):
       outbits=f1.read(16)
       apd,bu=tims(outbits)
       if 'oldbu' in locals():
          print "\t+"+str((bu-oldbu)/1000.)+"\t ns = "
       print apd,
       print ' ',
       print bu,
       print 'ps',
       oldbu=bu
f1.close()
