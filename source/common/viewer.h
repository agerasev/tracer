#ifndef VIEWER_H
#define VIEWER_H

#include<memory>
#include<render/container/surface.h>

class Viewer
{
public:

	/* Informs viewer about resizing viewport */
	virtual void resize(int w, int h) = 0;

	/* Gives rendered slice to viewer */
	virtual void update(std::unique_ptr<const Surface> surface) = 0;
};

#endif // VIEWER_H
