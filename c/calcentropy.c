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
#include <math.h>

#define INBUFSIZE 4096		/* choose 32kbyte large input buffer */
#define LOG2 0.69314718055994530941723212145817656807550013436025525

long double
calcrat (int a, int b) // this calculates the ratio of two numbers
{
  long double rat;           // the variable
  rat = (long double) a / b; // simply by division
  return rat;		     // return the value
}

long double
calcshent (int tot, int z, int o) // calculate the Shannon entropy
{
  long double pz, po, ent; // variables
  pz = (double) z / tot; // probability of zeros
  po = (double) o / tot; // probability of ones
  pz *= log (pz) / LOG2; // times the binary log of the probability (/by LOG2 to get bin log)
  po *= log (po) / LOG2; // times the binary log of the probability (/by LOG2 to get bin log)
  ent = -(long double) (pz + po); // this is the negative sum of all
  return ent; // return the value
}

int
main (int argc, char *argv[])
{
  int i;

  long int arr[10];

  char line[1024], *p, *e;
  long v;
  while (fgets (line, sizeof (line), stdin)) // parse the input
    {
      p = line;
      i = 0;
      for (p = line;; p = e)
	{
	  i++;
	  v = strtol (p, &e, 10);
	  if (p == e)
	    break;
	  arr[i] = v;
	}

      printf ("%.10Lf %.20Lf\n", calcrat (arr[2], arr[1]),
	      calcshent (arr[1], arr[2], arr[3])); // simply return the ratio and the entropy
    }

}
