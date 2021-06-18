#include "functions.h"

float arduino_map(const float& val, const float& in_min, const float& in_max, const float& out_min, const float& out_max)
{
	return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float clamp(const float& val, const float& min, const float& max)
{
	return std::min(std::max(val, min), max);
}