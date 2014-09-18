#ifndef DIFFUSESTEPPROGRAM_HPP
#define DIFFUSESTEPPROGRAM_HPP

#include"placeprogram.hpp"

class DiffuseStepProgram : public PlaceProgram
{
private:
	/* Uniform */
	GLuint source;
	GLuint factor;
	GLuint delta;

public:
	virtual void pull() override
	{
		PlaceProgram::pull();
		source = getUniform("uSource");
		factor = getUniform("uFactor");
		delta = getUniform("uDelta");
	}
	void bindSourceSampler(GLuint sampler) {
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(source,1);
		glBindTexture(GL_TEXTURE_2D, sampler);
	}
	void setFactor(float f)
	{
		glUniform1f(factor,f);
	}
	void setDelta(float dt)
	{
		glUniform1f(delta,dt);
	}
};

#endif // DIFFUSESTEPPROGRAM_HPP
