#pragma once
#define GLEW_STATIC
#include <gl/glew.h>
#include <vector>

class Plottable {
protected:
	bool graphicsInitialized;
	std::vector<GLuint> buffers;
public:
	virtual void initGraphics()=0;
	virtual void draw()=0;
};