#include "sin_LUT.h"
// ADDED LINE - THIS IS NORMALLY NOT PART OF THIS FILE
#include "arkanoid_objects.h";

// typedef struct{long x,y; } vector_t;

long sinus(long value, int formatin, int formatout)
// formatin and formatout determines the number of bits used to express values less than 1.
{
    value = fix_round(value, formatin, 0);	// Rounds value from formatin to format 32.0.

	value = value % 512;		// n*512 + x = x (mod 512)

    if(value < 0)
		value = 512 + value;	// (-x) = 512 - x
	
    return (fix_round(SIN[value], 14, formatout));
}


long cosinus(long value, int formatin, int formatout)
// formatin and formatout determines the number of bits used to express values less than 1.
{
    value = fix_round(value, formatin, 0);	// Rounds value from formatin to format 32.0.
	return sinus(value+128,0, formatout);	// cos(x) = sin(x+90degrees)
}


void rotate(vector_t *vp, long angle, int format1, int format2, int formatout)
/*	format1 and 2 and formatout determines the number of bits used to express values less than 1.
	format1 is related to the vector and format2 to the angle. */
{
	long tmp1, tmp2;
	long x, y;
	
	// the new x value is calculated in format 18.14 using sin and cos.
	tmp1 = fix_mps( (*vp).x , cosinus(angle, format2, 14), format1, 14, formatout);
	tmp2 = fix_mps( (*vp).y , sinus(angle, format2, 14), format1, 14, formatout);
	
	x = tmp1 - tmp2;
	
	
	// the new y value is calculated in format 18.14 using sin and cos.
	tmp1 = fix_mps( (*vp).x, sinus(angle, format2, 14), format1, 14, formatout);
	tmp2 = fix_mps( (*vp).y, cosinus(angle, format2, 14), format1, 14, formatout);
	
	y = tmp1 + tmp2;
	
	// the rotation is applied to the vector.
	(*vp).x = x;
	(*vp).y = y;
}

long sp_angle(angle, formatin, formatout)				//angle converted to smallest equivalent angle
{
long tmp512, tmp2;

	tmp512=fix_round(512,0,formatin);
	tmp2 = angle % tmp512;
	
	if (tmp2 < 0)
		tmp2=tmp2+tmp512;
	
	return fix_round(tmp2, formatin, formatout);

}

