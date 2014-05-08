#ifndef _FILIP_MUMES_COMMON_H_
#define _FILIP_MUMES_COMMON_H_
/**
 * Structure designed to store information about single pixel. 
 */
struct t_RGBA
{
	float r;
	float g;
	float b;
	float a;
    t_RGBA() : r(0.f), g(0.f), b(0.f), a(0.f)
    {}
};

#define CORDS(X, Y, Z) ((X) + (Y)*width + (Z)*width*height)

/**
 * Function that increments every channel of dest by apropriate channel from src scaled (divided) by coef
 *     dest += src / coef;
 */
void
increment
(
	t_RGBA &dest,
	t_RGBA src,
	float coef
);
#endif