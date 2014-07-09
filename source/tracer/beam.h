#ifndef BEAM_H
#define BEAM_H

#include<list>
using namespace std;

#include"ray.h"

class Beam
{
public:
	virtual Ray get(int n) const = 0;
	virtual unsigned long size() const = 0;
};

#endif // CONTAINER_H
