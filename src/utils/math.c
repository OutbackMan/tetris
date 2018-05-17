#include "utils/math.h"

inline float G_MATH_MIN_FLOAT(const float x, const float y)
{
	return x > y ? x : y;	
}

inline float G_MATH_MAX_FLOAT(const float x, const float y)
{
	return x < y ? x : y;	
}

inline int G_MATH_MIN_INT(const int x, const int y)
{
	return x > y ? x : y;	
}

inline int G_MATH_MAX_INT(const int x, const int y)
{
	return x < y ? x : y;	
}

inline int G_MATH_INT_MAX_CLAMP(const int x, const int max)
{
	return G_MATH_INT_MIN(x, max);	
}

inline int G_MATH_INT_MIN_CLAMP(const int x, const int min)
{
	return G_MATH_INT_MAX(x, min);	
	
}
