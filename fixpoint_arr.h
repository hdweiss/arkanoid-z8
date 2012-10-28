/*
	This file provides functions to perform fixed point arithmetic.
	Each function has formatin og formatout arguments. These tell the function
	the number of bits used to describe values less than 1.
	
	Example:
		a number x in format 16.16 is rounded and returned in format 24.8. For this
		purpose we use the function
		fix_round(long value, int formatin, int formatout):
	
		x = fix_round(x, 16, 8);
	
	
	The functions fix_mpl and fix_mps both perform multiplication of two numbers.
	However, there is a slight difference in their operation. fix_mpl is sometimes
	less precise than fix_mps but is less likely to overflow.
*/

#ifndef _FIXARR_H_
#define _FIXARR_H_

long fix_round(long value, int formatin, int formatout);
long fix_mpl(long value1, long value2, int format1, int format2, int formatout);
long fix_mps(long value1, long value2, int format1, int format2, int formatout);
long fix_div(long dividend, long divisor, int format1, int format2, int formatout);
void printFix(long value, int format, int decimals);

#endif
