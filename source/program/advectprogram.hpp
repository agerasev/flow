#ifndef ADVECTPROGRAM_HPP
#define ADVECTPROGRAM_HPP

#include"placeprogram.hpp"

class AdvectProgram : public PlaceProgram
{
private:
	/* Uniform */
	GLuint velocity;
	GLuint source;
	GLuint delta;

public:
	virtual void pull() override
	{
		PlaceProgram::pull();
		velocity = getUniform("uVelocity");
		source = getUniform("uSource");
		delta = getUniform("uDelta");
	}
	void setDelta(float dt)
	{
		glUniform1f(delta,dt);
	}
	void bindVelocitySampler(GLuint sampler) {
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(velocity,0);
		glBindTexture(GL_TEXTURE_2D, sampler);
	}
	void bindSourceSampler(GLuint sampler) {
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(source,1);
		glBindTexture(GL_TEXTURE_2D, sampler);
	}
};

#endif // ADVECTPROGRAM_HPP
