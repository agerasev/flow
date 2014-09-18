#ifndef SCREEN_HPP
#define SCREEN_HPP

#include"shape.hpp"

class ScreenShape : public Shape
{
private:
	fvec2 vertices[4] = {fvec2(0.0,0.0),fvec2(0.0,1.0),fvec2(1.0,1.0),fvec2(1.0,0.0)};
public:
	virtual void loadBuffers() override
	{
		buffer(vertices,4);
	}
	virtual void draw() override
	{
		glDrawArrays(GL_QUADS,0,4);
	}
};

#endif // SCREEN_HPP
