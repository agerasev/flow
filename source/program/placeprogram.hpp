#ifndef PLACEPROGRAM_HPP
#define PLACEPROGRAM_HPP

#include<GL/glew.h>

#include<4u/gl/program.hpp>
#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>

class PlaceProgram : public Program
{
private:
	/* Attribs */
	GLuint vertex;
	GLuint transform;
	GLuint translate;

public:
	virtual void pull() override
	{
		vertex = getAttribute("vertex");
		translate = getUniform("transform");
		translate = getUniform("translate");
	}
	void enableAttribs()
	{
		glEnableVertexAttribArray(vertex);
	}
	void disableAttribs()
	{
		glDisableVertexAttribArray(vertex);
	}
	void pointVertex(const fvec2 p[] = nullptr)
	{
		glVertexAttribPointer(vertex, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const float*>(p));
	}
	GLuint getVertexAttrib() const {
		return vertex;
	}
	void setTransformation(const fmat2 &mat)
	{
		glUniformMatrix2fv(transform,1,GL_FALSE,mat.data);
	}
	void setTranslation(const fvec2 &vec)
	{
		glUniform2fv(translate,1,vec.data);
	}
};


#endif // PLACEPROGRAM_HPP
