#ifndef SHAPE_HPP
#define SHAPE_HPP

#include<4u/gl/vertexbuffer.hpp>

class Shape : public VertexBuffer
{
public:
	virtual void loadBuffers() = 0;
    virtual void draw() = 0;
};

#endif // SHAPE_HPP
