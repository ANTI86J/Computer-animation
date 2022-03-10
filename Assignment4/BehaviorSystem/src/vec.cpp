#include "vec.h"

vec2::vec2() {
	this->x = 0.0;
	this->y = 0.0;
}

vec2::vec2(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
}

float vec2::magnitude() {
	return sqrtf(pow(x, 2) + pow(y, 2));
}

vec2 vec2::normalize() {
	float magnitude = this->magnitude();
	if(magnitude == 0) return (*this);
	return vec2(x / magnitude, y / magnitude);
}

float vec2::sqrDist(const vec2& rhs) {
	return pow(this->x - rhs.x, 2) + pow(this->y - rhs.y, 2);
}

float vec2::dist(const vec2& rhs) {
	return sqrtf(pow(this->x - rhs.x, 2) + pow(this->y - rhs.y, 2));
}

// rotates counter-clockwise
vec2 vec2::rotate(float angle) {
	float rad = angle * (PI / 180.0f);
	float cosine = cos(rad);
	float sine = sin(rad);

	return vec2(cosine * x - sine * y, sine * x + cosine * y);
}

vec2 vec2::operator+(const vec2& rhs) {
	vec2 result = vec2(this->x + rhs.x, this->y + rhs.y);
	return result;
}

vec2 vec2::operator-(const vec2& rhs) {
	vec2 result = vec2(this->x - rhs.x, this->y - rhs.y);
	return result;
}

vec2 vec2::operator-() {
	return vec2(-this->x, -this->y);
}

vec2 vec2::operator*(const vec2& rhs) {
	vec2 result = vec2(this->x * rhs.x, this->y * rhs.y);
	return result;
}

vec2 vec2::operator*(const float& rhs) {
	return vec2(this->x * rhs, this->y * rhs);
}

vec2 vec2::operator+=(const vec2& rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

vec2 vec2::operator/(const float& rhs) {
	return vec2(this->x/rhs, this->y/rhs);
}

vec2 vec2::operator/=(const float& rhs) {
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

vec2 vec2::operator/(const vec2& rhs) {
	return vec2(this->x/rhs.x, this->y/rhs.y);
}

vec2 vec2::operator/=(const vec2& rhs) {
	this->x /= rhs.x;
	this->y /= rhs.y;
	return *this;
}

float vec2::dotProduct(const vec2& rhs){
	return this->x * rhs.x + this->y * rhs.y;
}

vec3::vec3() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

vec3::vec3(GLfloat x, GLfloat y, GLfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float vec3::magnitude() {
	return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

vec3 vec3::normalize() {
	float magnitude = this->magnitude();
	if(magnitude == 0) return (*this);
	return vec3(x / magnitude, y / magnitude, z / magnitude);
}

float vec3::sqrDist(const vec3& rhs) {
	return pow(this->x - rhs.x, 2) + pow(this->y - rhs.y, 2) + pow(this->z - rhs.z, 2);
}

vec3 vec3::operator+(const vec3& rhs) {
	vec3 result = vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	return result;
}

vec3 vec3::operator-(const vec3& rhs) {
	vec3 result = vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
	return result;
}

vec3 vec3::operator-() {
	return vec3(-this->x, -this->y, -this->z);
}

vec3 vec3::operator*(const vec3& rhs) {
	vec3 result = vec3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
	return result;
}

vec3 vec3::operator*(const float& rhs) {
	return vec3(this->x * rhs, this->y * rhs, this->z * rhs);
}

vec3 vec3::operator+=(const vec3 &rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

vec3 vec3::operator/(const float& rhs) {
	return vec3(this->x/rhs, this->y/rhs, this->z/rhs);
}

vec3 vec3::operator/=(const float& rhs) {
	this->x /= rhs;
	this->y /= rhs;
	this->z /= rhs;
	return *this;
}

vec3 vec3::operator/(const vec3& rhs) {
	return vec3(this->x/rhs.x, this->y/rhs.y, this->z/rhs.z);
}

vec3 vec3::operator/=(const vec3& rhs) {
	this->x /= rhs.x;
	this->y /= rhs.y;
	this->z /= rhs.z;
	return *this;
}

vec4::vec4() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->w = 0.0;
}

vec4::vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float vec4::magnitude() {
	return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
}

vec4 vec4::normalize() {
	float magnitude = this->magnitude();
	if(magnitude == 0) return (*this);
	return vec4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
}

float vec4::sqrDist(const vec4& rhs) {
	return pow(this->x - rhs.x, 2) + pow(this->y - rhs.y, 2) + pow(this->z - rhs.z, 2) + pow(this->w - rhs.w, 2);
}

vec4 vec4::operator+(const vec4& rhs) {
	vec4 result = vec4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
	return result;
}

vec4 vec4::operator-(const vec4& rhs) {
	vec4 result = vec4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
	return result;
}

vec4 vec4::operator-() {
	return vec4(-this->x, -this->y, -this->z, -this->w);
}

vec4 vec4::operator*(const vec4& rhs) {
	vec4 result = vec4(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->w * rhs.w);
	return result;
}

vec4 vec4::operator*(const float& rhs) {
	return vec4(this->x * rhs, this->y * rhs, this->z * rhs, this->w * rhs);
}

vec4 vec4::operator+=(const vec4& rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	this->w += rhs.w;
	return *this;
}

vec4 vec4::operator/(const float& rhs) {
	return vec4(this->x/rhs, this->y/rhs, this->z/rhs, this->w/rhs);
}

vec4 vec4::operator/=(const float& rhs) {
	this->x /= rhs;
	this->y /= rhs;
	this->z /= rhs;
	this->w /= rhs;
	return *this;
}

vec4 vec4::operator/(const vec4& rhs) {
	return vec4(this->x/rhs.x, this->y/rhs.y, this->z/rhs.z, this->w/rhs.w);
}

vec4 vec4::operator/=(const vec4& rhs) {
	this->x /= rhs.x;
	this->y /= rhs.y;
	this->z /= rhs.z;
	this->w /= rhs.w;
	return *this;
}

vec3 vec3Lerp(const vec3& start, const vec3& end, const float& t) {
	return vec3(lerp(start.x, end.x, t), lerp(start.y, end.y, t), lerp(start.z, end.z, t));
}

void debugLog(const vec3& vector, const char* message) {
	std::cout << message << vector.x << ", " << vector.y << ", " << vector.z << std::endl;
}

bool intersect(const vec2& p0, const vec2& p1, const vec2& p2, const vec2& p3, vec2* i)
{
	float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
	s10_x = p1.x - p0.x;
	s10_y = p1.y - p0.y;
	s32_x = p3.x - p2.x;
	s32_y = p3.y - p2.y;

	denom = s10_x * s32_y - s32_x * s10_y;
	if (denom == 0)
		return false; // Collinear
	bool denomPositive = denom > 0;

	s02_x = p0.x - p2.x;
	s02_y = p0.y - p2.y;
	s_numer = s10_x * s02_y - s10_y * s02_x;
	if ((s_numer < 0) == denomPositive)
		return false; // No collision

	t_numer = s32_x * s02_y - s32_y * s02_x;
	if ((t_numer < 0) == denomPositive)
		return false; // No collision

	if (((s_numer > denom) == denomPositive) || ((t_numer > denom) == denomPositive))
		return false; // No collision
	// Collision detected
	t = t_numer / denom;
	if (i != nullptr)
		//i = p0.x + (t * s10_x);
		//*i.y = p0.y + (t * s10_y);
		(*i) = vec2(p0.x + (t * s10_x), p0.y + (t * s10_y));

	return true;
}

bool intersect(const vec2& c, float r, const vec2& p1, const vec2& p2)
{
	float x = c.x, y = c.y;
	float x1 = p1.x, x2 = p2.x, y1 = p1.y, y2 = p2.y;
	float vx1= x - x1;
	float vy1= y - y1;
	float vx2= x2 - x1;
	float vy2= y2 - y1;

	//assert(fabs(vx2) > 0.00001f || fabs(vy2) > 0.00001f);

	// len = v2.length()
	float len= sqrt(vx2 * vx2 + vy2 * vy2);

	// v2.normalize()
	vx2 /= len;
	vy2 /= len;

	// u = v1.dot(v2)
	// u is the vector projection length of vector v1 onto vector v2.
	float u = vx1* vx2+ vy1* vy2;

	// determine the nearest point on the lineseg
	float x0 = 0.f;
	float y0 = 0.f;
	if (u <= 0)
	{
		// p is on the left of p1, so p1 is the nearest point on lineseg
		x0 = x1;
		y0 = y1;
	}
	else if (u >= len)
	{
		// p is on the right of p2, so p2 is the nearest point on lineseg
		x0 = x2;
		y0 = y2;
	}
	else
	{
		// p0 = p1 &#43; v2 * u
		// note that v2 is already normalized.
		x0 = x1 + vx2* u;
		y0 = y1 + vy2* u;
	}

	return (x - x0) * (x - x0) + (y - y0)* (y - y0) <= r * r;
}