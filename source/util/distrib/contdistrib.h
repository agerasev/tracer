#ifndef CONTDISTRIB_H
#define CONTDISTRIB_H

#include"distrib.hpp"

// Continuous distribution
class ContDistrib : public Distrib {
private:
    double begin, width;
public:
    ContDistrib(double a = 1.0, double b = 0.0);
	virtual static double get() const;
	virtual static unsigned long card() const;
};

#endif // CONTDISTRIB_H
