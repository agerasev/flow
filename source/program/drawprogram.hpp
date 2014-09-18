#ifndef DRAWPROGRAM_HPP
#define DRAWPROGRAM_HPP

#include"placeprogram.hpp"

class DrawProgram : public PlaceProgram
{
private:
	/* Uniform */
	GLuint substance;
	GLuint velocity;

public:
	virtual void pull() override
	{
		PlaceProgram::pull();
		substance = getUniform("substance");
		velocity = getUniform("velocity");
	}
	void bindSubstanceSampler(GLuint sampler) {
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(substance,0);
		glBindTexture(GL_TEXTURE_2D, sampler);
	}
	void bindVelocitySampler(GLuint sampler) {
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(velocity,1);
		glBindTexture(GL_TEXTURE_2D, sampler);
	}
};


#endif // DRAWPROGRAM_HPP
