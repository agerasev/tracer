#ifndef BEAMDISTRIB_H
#define BEAMDISTRIB_H

#include"beam.h"
#include"../../util/distrib.hpp"

class BeamDistrib : public Beam {
protected:
	static const unsigned long CARD = 0x100000000;
public:
	virtual unsigned long size() const {
		return CARD;
	}
};

#endif // BEAMDISTRIB_H
