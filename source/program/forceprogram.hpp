#ifndef FORCEPROGRAM_HPP
#define FORCEPROGRAM_HPP

#include"placeprogram.hpp"

class ForceProgram : public PlaceProgram
{
private:
	/* Uniform */
	GLuint velocity;
    GLuint delta;
	GLuint force;

public:
	virtual void pull() override
	{
		PlaceProgram::pull();
        velocity = getUniform("uVelocity");
        delta = getUniform("uDelta");
        force = getUniform("uForce");
	}
	void bindVelocitySampler(GLuint sampler) {
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(velocity,0);
		glBindTexture(GL_TEXTURE_2D, sampler);
	}
    void setDelta(float d)
    {
        glUniform1f(delta,d);
    }
    void setForce(const fvec2 &f)
	{
        glUniform2fv(force,1,f.data);
	}
};

#endif // FORCEPROGRAM_HPP
