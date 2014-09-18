#ifndef PRESSURESTEPPROGRAM_HPP
#define PRESSURESTEPPROGRAM_HPP

#include"placeprogram.hpp"

class PressureStepProgram : public PlaceProgram
{
private:
	/* Uniform */
	GLuint velocity;

public:
	virtual void pull() override
	{
		PlaceProgram::pull();
		velocity = getUniform("uVelocity");
	}
	void bindVelocitySampler(GLuint sampler) {
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(velocity,0);
		glBindTexture(GL_TEXTURE_2D, sampler);
	}
};

#endif // PRESSURESTEPPROGRAM_HPP
