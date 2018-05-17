#include "utils/math.h"


int G_MATH_INT_MAX_CLAMP(int x, int max)
{
	return G_MATH_INT_MIN(x, max);	
}

int G_MATH_INT_MIN_CLAMP(int x, int min)
{
	return G_MATH_INT_MAX(x, min);	
	
}
