#include "common.h"
void
increment
(
t_RGBA &dest,
t_RGBA src,
float coef
)
{
	dest.r += src.r / coef;
	dest.g += src.g / coef;
	dest.b += src.b / coef;
	dest.a += src.a / coef;
}