#ifndef BEAMSET_H
#define BEAMSET_H

#include"beam.h"

#include<vector>
using namespace std;

class BeamSet : public Beam {

private:
	vector<Ray> container;

public:
	void add(const Ray &ray) {
		container.push_back(ray);
	}
	virtual Ray get(int n) const {
		return container.at(n);
	}
	virtual unsigned long size() const {
		return container.size();
	}
};

#endif // BEAMSET_H
