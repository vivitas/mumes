#ifndef _FILIP_MUMES_COMMON_H_
#define _FILIP_MUMES_COMMON_H_
struct t_RGBA
{
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 0;
};


#define CORDS(X, Y, Z) ((X) + (Y)*width + (Z)*width*height)

void
increment
(
t_RGBA &dest,
t_RGBA src,
float coef
);
#endif