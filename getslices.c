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
long totalc=0;
long ccount=0;
long zzcount=0;
long zocount=0;
long ozcount=0;
long oocount=0;
long ttotalc=0;
long tccount=0;
long tzzcount=0;
long tzocount=0;
long tozcount=0;
long toocount=0;
unsigned char ocb,thisc,oldb,firstbit;
long size;

size=atoi(argv[1]);
inbuf=malloc(size);

inhandle=stdin; 

while (0<(retval=fread(inbuf,sizeof(ocb),size,inhandle)))
	{
for (index=0;index<retval;index++) {
	ocb = thisc = (unsigned char) inbuf[index];
	totalc += 8;
	for (b = 0; b < 7; b++)
		{
		switch (ocb & 3)
		{  case 0: zzcount++; break;
		   case 1: zocount++; ccount++; break;
		   case 2: ozcount++; break;
		   case 3: oocount++; ccount++; break;
		}
		ocb >>= 1;
		}
	
	lb=ocb & 1; // last bit of this file
	ccount+=lb; // if set, then add
	
	if (totalc<=8) // first byte which is read
		{
		firstbit=lb;
		}
	else 
		{
		switch (((oldb & 1)<<1) + (thisc>>7 & 1))
		{  case 0: zzcount++; break;
		   case 1: zocount++; break;
		   case 2: ozcount++; break;
		   case 3: oocount++; break;
		}
		}
	oldb = thisc;
	}

switch ((firstbit & 1) + ((thisc & 1)<<1)) // determine the first bit and the very last bit
	{  case 0: zzcount++; break;
	   case 1: zocount++; break;
	   case 2: ozcount++; break;
	   case 3: oocount++; break;
	}


printf("%10ld %10ld %10ld %10ld %10ld %10ld %10ld\n",totalc,totalc-ccount,ccount,zzcount,zocount,ozcount,oocount);
totalc=0;
ccount=0;
zzcount=0;
zocount=0;
ozcount=0;
oocount=0;
	}

//printf("%10ld %10ld %10ld %10ld %10ld %10ld %10ld\n",totalc,totalc-ccount,ccount,zzcount,zocount,ozcount,oocount);
}
