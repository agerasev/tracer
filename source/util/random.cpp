#include<cstdlib>
#include<cmath>
#include<ctime>

#include"random.h"

Random::Initializer::Initializer() {
	srand(time(nullptr));
}

double Random::get(double a) {
	return a*static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

