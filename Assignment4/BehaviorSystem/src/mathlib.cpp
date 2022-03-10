#include "mathlib.h"

float min(const float &a, const float &b) {
	return (a < b) ? a : b;
}

float max(const float &a, const float &b) {
	return (a > b) ? a : b;
}

float clampMin(const float &value, const float &min) {
	float result = value;
	return max(result, min);
}

float clampMax(const float &value, const float& max) {
	return min(value, max);
}

float clamp(const float& value, const float& min, const float& max) {
	float result = value;
	result = clampMin(result, min);
	result = clampMax(result, max);
	return result;
}

float lerp(const float& start, const float& end, const float& t) {
	float tClamped = clamp(t, 0, 1);
	return start * (1 - tClamped) + end * tClamped;
}

float easeOutExpo(const float& start, const float& end, const float& t) {
	float tClamped = clamp(t, 0, 1);
	float dist = end - start;
	return dist * (-pow(2.0, -10.0 * t) + 1.0) + start;
}