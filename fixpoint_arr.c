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

#include <stdio.h>

long power(long value, long pwr)
{
	int i = 1;
	while(++i < pwr)
		value*=value;
	
	return(value);
}


long fix_round(long value, int formatin, int formatout)
{
/*
	rounds value in formatin to formatout.
*/

	if (formatin>formatout)
	{
		// the usual case: formatin > formatout
		
		value = (value >> (formatin-formatout-1) );		// value is shifted one less than the conversion
		value++;										// in order to round properly. The last shift is
		value = value >> 1;								// carried out after adding 1. This is the actual rounding.
	}
	else
	{
		// in case formatin < formatout no rounding is needed and only the format is converted. 
		value = value << (formatout - formatin);
	}
	
	return value;
}


long fix_mpl(long value1, long value2, int format1, int format2, int formatout)
{
	value1 = fix_round(value1, format1, formatout);				// converts value1 into formatout.
	value2 = fix_round(value2, format2, formatout);				// converts value2 into formatout.
	return ( fix_round(value1*value2, 2*formatout, formatout) );// the numbers are multiplied and returned in formatout.
}

long fix_mps(long value1, long value2, int format1, int format2, int formatout)
{
	// first the numbers are multiplied and then th result is converted into formatout and returned.
	return ( fix_round(value1*value2, format1+format2, formatout) );
}

long fix_div(long dividend, long divisor, int format1, int format2, int formatout)
{
	// first the division is carried out and secondly the result is converted into formatout and returned.
	dividend = fix_round(dividend, format1, format2+formatout);
	return dividend/divisor;
}

void printFix(long value, int format, int decimals)
{
	// checks if value is negaive and in that case print a minus-sign. Then the sign of value is changed to positive.
    if((value & 0x80000000) != 0){
		printf("-");
		value = ~value+1;						// converts to positive value: 1101 = -3, 0010+0001=3
    }

	// the value is printed to stdout.
	printf("%ld.%ld",	value >> format,
						(power(10,decimals) * ( (power(2,format)-1) & value) ) >> format);
}
