#pragma once
#include <algorithm>

//////////////
// arduino map
// https://www.arduino.cc/reference/en/language/functions/math/map/
float arduino_map(const float& val, const float& in_min, const float& in_max, const float& out_min, const float& out_max);

//////////////
// clamp
// clamps given value between min and max
float clamp(const float& val, const float& min, const float& max);
