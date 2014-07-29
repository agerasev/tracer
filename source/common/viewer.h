#ifndef VIEWER_H
#define VIEWER_H

#include"slice.h"

class Viewer
{
public:

	/* Informs viewer about resizing viewport */
	virtual void resize(int w, int h) = 0;

	/* Gives rendered slice to viewer */
	virtual void update(const Slice &slice) = 0;
};

#endif // VIEWER_H
