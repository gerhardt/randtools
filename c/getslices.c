/* 
 * Copyright (c) 2018 Ilja Gerhardt, ilja@quantumlah.org
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#define INBUFSIZE 50000000 /* choose large input buffer */

int main(int argc, char *argv[])
{
    FILE *inhandle;
    //unsigned char inbuf[INBUFSIZE]; /* input buffer */
    unsigned char* inbuf; /* input buffer */
    int index,retval;

int b,lb;
long totalc=0; // look how many bits have been processed
long ccount=0; // this counts the numbers of ones
long zzcount=0; // tuples: 0-0
long zocount=0; // tuples: 0-1
long ozcount=0; // tuples: 1-0
long oocount=0; // tuples: 1-1
unsigned char ocb,thisc,oldb,firstbit;
long size;

size=atoi(argv[1]); // read the size (in bytes which should be calculated)
inbuf=malloc(size); // reserve some space, depending on the size 

inhandle=stdin; // read from std input

while (0<(retval=fread(inbuf,sizeof(ocb),size,inhandle)))
	{
for (index=0;index<retval;index++) {
	ocb = thisc = (unsigned char) inbuf[index];
	totalc += 8; // add 8 bits, since a byte is now processed
	for (b = 0; b < 7; b++) // do the next loop 7 times (<7!)
		{
		switch (ocb & 3) // make an AND with the number 1 (i.e. 11 at the end)
		{  case 0: zzcount++; break; // this means 00
		   case 1: zocount++; ccount++; break; // this means 01 - bits+1
		   case 2: ozcount++; break; // this means 10
		   case 3: oocount++; ccount++; break; // this means 11 - bits+1
		}
		ocb >>= 1; // roll the byte
		}
	
	lb=ocb & 1; // last bit of this file
	ccount+=lb; // if this bit was set, then add
	
	if (totalc<=8) // first byte which is read, then true...
		{
		firstbit=lb; // set the firstbit as the last bit of this loop
		}
	else           // this is done normally 
		{
		switch (((oldb & 1)<<1) + (thisc>>7 & 1)) // take the last bit*2 plus the current byte to the right
		{  case 0: zzcount++; break; // tuples 00
		   case 1: zocount++; break; // tuples 01
		   case 2: ozcount++; break; // tuples 10
		   case 3: oocount++; break; // tuples 11
		}
		}
	oldb = thisc; // this is the byte which has just been processed - called oldb
	}

switch ((firstbit & 1) + ((thisc & 1)<<1)) // determine the first bit (of all read ones!) and the very last bit
	{  case 0: zzcount++; break; // only process the tuples 00
	   case 1: zocount++; break; // only process the tuples 01
	   case 2: ozcount++; break; // only process the tuples 10 
	   case 3: oocount++; break; // only process the tuples 11
	}


printf("%10ld %10ld %10ld %10ld %10ld %10ld %10ld\n",totalc,totalc-ccount,ccount,zzcount,zocount,ozcount,oocount); // give the values out
totalc=0; // reset all the values 
ccount=0;
zzcount=0;
zocount=0;
ozcount=0;
oocount=0;
	}

}
