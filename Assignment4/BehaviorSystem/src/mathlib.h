#pragma once
#include <math.h>
#define PI 3.1415926f

float min(const float &a, const float &b);
float max(const float& a, const float& b);

float clampMin(const float &value, const float &min);
float clampMax(const float &value, const float &max);
float clamp(const float &value, const float &min, const float &max);

float lerp(const float& start, const float& end, const float& t);
float easeOutExpo(const float& start, const float& end, const float& t);