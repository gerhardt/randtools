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
calcrat (int a, int b)
{
  long double rat;
  rat = (long double) a / b;
  return rat;
}

long double
calcshent (int tot, int z, int o)
{
  long double p1, p2, ent;
  p1 = (double) z / tot;
  p2 = (double) o / tot;
  p1 *= log (p1) / LOG2;
  p2 *= log (p2) / LOG2;
  ent = -(long double) (p1 + p2);
  return ent;
}

int
main (int argc, char *argv[])
{
  int i, j;

  long int arr[10];

  char line[1024], *p, *e;
  long v;
  while (fgets (line, sizeof (line), stdin))
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
	      calcshent (arr[1], arr[2], arr[3]));
    }

}
