#include"contdistrib.h"

#include<cstdlib>
#include<cmath>
#include<ctime>

class __Random {
public:
    __Random() {
        srand(time(nullptr));
    }
	static double get() {
        return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
    }
    static const int CARD = RAND_MAX;
};
static const __Random __random;

ContDistrib::ContDistrib(double a, double b) {
    if(b > a) {
        double c = a;
        a = b;
        b = c;
    }
    begin = b;
    width = a - b;
}
double ContDistrib::get(double a, double b) const {
	return a + (b - a)*__random.get();
}
unsigned long ContDistrib::card() const {
	return static_cast<unsigned long>(__random.CARD);
}
