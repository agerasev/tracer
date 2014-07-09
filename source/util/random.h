#ifndef RANDOM_H
#define RANDOM_H

const double PI = 3.1415; //... to be continued...

class Random{
private:
	Random() {}
	class Initializer {
	public:
		Initializer();
	};
	static Initializer initiaizer;
public:
	static double get(double a = 1.0);
};

#endif // RANDOM_H
