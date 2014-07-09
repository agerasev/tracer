#ifndef COLOR_HPP
#define COLOR_HPP

struct Color {
	double data[3];
	inline Color() {

	}
	inline Color(const Color &av) {
		data[0] = av.data[0];
		data[1] = av.data[1];
		data[2] = av.data[2];
	}
	inline Color(double ax, double ay, double az) {
		data[0] = ax;
		data[1] = ay;
		data[2] = az;
	}
	inline Color &operator = (const Color &av) {
		data[0] = av.data[0];
		data[1] = av.data[1];
		data[2] = av.data[2];
		return *this;
	}
	inline double &operator ()(int n) {
		return data[n];
	}
	inline double operator ()(int n) const {
		return data[n];
	}
	inline double &r() {return data[0];}
	inline double &g() {return data[1];}
	inline double &b() {return data[2];}
	inline double r() const {return data[0];}
	inline double g() const {return data[1];}
	inline double b() const {return data[2];}
};

// Basic operations
  // Addition
inline Color operator +(const Color &a, const Color &b) {
	return Color(
				a.r() + b.r(),
				a.g() + b.g(),
				a.b() + b.b()
				);
}
  // Multiplication by constatnt
inline Color operator *(double a, const Color &b) {
	return Color(
				a*b.r(),
				a*b.g(),
				a*b.b()
				);
}
  // Multiplication by color
inline Color operator *(const Color &a, const Color &b) {
	return Color(
			a.r()*b.r(),
			a.g()*b.g(),
			a.b()*b.b()
				);
}

// Derivative operations
inline Color operator *(const Color &b, double a) {
	return a*b;
}
inline Color operator -(const Color &a) {
	return -1.0*a;
}
inline Color operator -(const Color &a, const Color &b) {
	return a+(-b);
}
inline Color operator /(const Color &b, double a) {
	return b*(1.0/a);
}


// Cross product
inline double weight(const Color &a) {
	return a.r() + a.g() + a.b();
}

#endif // COLOR_HPP
