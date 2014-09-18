#ifndef FILLPROGRAM_HPP
#define FILLPROGRAM_HPP

#include"placeprogram.hpp"

class FillProgram : public PlaceProgram
{
private:
	/* Uniform */
	GLuint color;

public:
	virtual void pull() override
	{
		PlaceProgram::pull();
		color = getUniform("uColor");
	}
	void setColor(const fvec4 &f)
	{
		glUniform4fv(color,1,f.data);
	}
};

#endif // FILLPROGRAM_HPP
