#include<cstdlib>
#include<cmath>
#include<ctime>

Random::Initializer() {
	srand(time(nullptr));
}

static double Random::get(double a = 1.0) {
	return a*static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

