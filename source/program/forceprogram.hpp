#ifndef FORCEPROGRAM_HPP
#define FORCEPROGRAM_HPP

#include"placeprogram.hpp"

class ForceProgram : public PlaceProgram
{
private:
	/* Uniform */
	GLuint velocity;
	GLuint source;
	GLuint force;

public:
	virtual void pull() override
	{
		PlaceProgram::pull();
		velocity = getUniform("velocity");
		source = getUniform("source");
		force = getUniform("force");
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
	void setForce(const fvec4 &f)
	{
		glUniform4fv(force,1,f.data);
	}
};

#endif // FORCEPROGRAM_HPP
