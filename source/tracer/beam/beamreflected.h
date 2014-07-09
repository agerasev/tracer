#ifndef BEAMREFLECTED_H
#define BEAMREFLECTED_H

#include<cmath>

#include"beamdistrib.h"
#include"../../util/random.h"
#include"../../util/vec.hpp"

class BeamReflected : public BeamDistrib {
private:
	vec3 point;
	vec3 norm;
	vec3 reflection;
	vec3 nx, ny;
public:
	BeamReflected(const vec3 &p, const vec3 &n, const vec3 &r) {
		if(vec3(0,0,1)*norm > 0.0) {

		} else {

		}
	}
	virtual Ray get(int n) const {
		// getting continuous distribution
		double phi = Random::get(2*PI);
		double theta = acos(1.0 - Random::get());
		vec3 =
	}
};

#endif // BEAMREFLECTED_H
