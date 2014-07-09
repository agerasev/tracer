#ifndef DISTRIB_HPP
#define DISTRIB_HPP

class Distrib {
public:
	virtual static double get() const = 0;
	virtual static unsigned long card() const = 0;
};

#endif // DISTRIB_HPP
