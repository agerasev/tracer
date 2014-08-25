#ifndef LIGHT_H
#define LIGHT_H

#include<4u/la/vec.hpp>

class Color
{
private:
	vec3 col;

public:
	inline Color() {

	}
	inline Color(const vec3 &v) :
		col(v)
	{

	}
	inline Color(const Color &l) :
		col(l.col)
	{

	}
	inline Color(double ar, double ag, double ab) :
		col(ar,ag,ab)
	{

	}
	inline double r() const {return col[0];}
	inline double &r() {return col[0];}
	inline double g() const {return col[1];}
	inline double &g() {return col[1];}
	inline double b() const {return col[2];}
	inline double &b() {return col[2];}

	// Basic operations
	  // Addition
	inline friend Color operator +(const Color &a, const Color &b) {
		return Color(a.col + b.col);
	}
	  // Multiplication by constatnt
	inline friend Color operator *(double a, const Color &b) {
		return Color(a*b.col);
	}
	  // Component product
	inline friend Color operator *(const Color &a, const Color &b) {
		return Color(a.col & b.col);
	}
	  // Division by Color
	inline friend Color operator /(double a, const Color &b) {
		return Color(a/b.r(),a/b.g(),a/b.b());
	}

	// Derivative operations
	inline friend Color operator *(const Color &b, double a) {
		return a*b;
	}
	inline friend Color operator -(const Color &a) {
		return Color(-a.col);
	}
	inline friend Color operator -(const Color &a, const Color &b) {
		return a+(-b);
	}
	inline friend Color operator /(const Color &b, double a) {
		return b*(1.0/a);
	}
	inline friend Color operator /(const Color &a, const Color &b) {
		return a*(1.0/b);
	}

	// Assign operations
	inline friend Color &operator +=(Color &a, const Color &b) {
		return a = a + b;
	}
	inline friend Color &operator -=(Color &a, const Color &b) {
		return a = a - b;
	}
	inline friend Color &operator *=(Color &a, double b) {
		return a = a*b;
	}
	inline friend Color &operator /=(Color &a, double b) {
		return a = a/b;
	}
};

const Color WHITE(1,1,1);
const Color BLACK(0,0,0);

#endif // LIGHT_H
