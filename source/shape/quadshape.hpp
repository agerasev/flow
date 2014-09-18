#ifndef QUADSHAPE_HPP
#define QUADSHAPE_HPP

#include"shape.hpp"

class QuadShape : public Shape
{
private:
	fvec2 vertices[4] = {fvec2(-1.0,-1.0),fvec2(1.0,-1.0),fvec2(1.0,1.0),fvec2(-1.0,1.0)};
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

#endif // QUADSHAPE_HPP
