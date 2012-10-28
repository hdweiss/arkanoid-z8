#ifndef _ARKAOBJS_H_
#define _ARKAOBJS_

typedef struct point_s pos_t;
typedef struct point_s vector_t;
typedef struct brick_s brick_t;
typedef struct ball_s ball_t;
typedef struct striker_s striker_t;

struct point_s {long x; long y;};

struct brick_s {
		pos_t pos;
		int	status;
		int	colour;
		int points;
	       };


struct ball_s {
		pos_t pos;
		long angle;
	      };


struct striker_s{
		pos_t pos;
		  };
		  
#endif
