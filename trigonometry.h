#ifndef _TRIGONOM_H_
#define _TRIGONOM_H_

// NORMALLY PART OF THIS FILE
//typedef struct{ long x,y; } vector_t;

/*
	The results of the sinus and cosinus functions are based on a LUT returning values in 18.14 format.
	Hence the results simply contain trailing zeroes if formatout > 14.
	
	the format arguments determines the number of bits used to express values less than 1.
	For the rotation function format1 is related to the provided vector and format2 to the angle.
	formatout always determines the format of the returned result.
*/

long sinus(long value, int formatin, int formatout);
long cosinus(long value, int formatin, int formatout);
void rotate(vector_t *vp, long angle, int format1, int format2, int formatout);
long sp_angle(angle, formatin, formatout);

#endif
