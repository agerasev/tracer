#ifndef COLOR_HPP
#define COLOR_HPP

#include"../util/vec.hpp"

struct Color : public tvecn<float,4> {
public:
    Color() : tvecn<float,4>(0,0,0,1) {}
    Color(float ar, float ag, float ab, float aa = 1.0f) : tvecn<float,4>(ar,ag,ab,aa) {}
    Color(const tvecn<float,4> &c) : tvecn<float,4>(c) {}
    Color &operator = (const tvecn<float,4> &c) {
		x() = c.x();
		y() = c.y();
		z() = c.z();
		w() = c.w();
		return *this;
	}

	float &r() {
		return x();
	}
	float &g() {
		return y();
	}
	float &b() {
		return z();
	}
	float &a() {
		return w();
	}
	float r() const {
		return x();
	}
	float g() const {
		return y();
	}
	float b() const {
		return z();
	}
	float a() const {
		return w();
	}
};

#endif // COLOR_HPP
