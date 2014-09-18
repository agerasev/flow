#ifndef DOUBLEFRAMEBUFFER_HPP
#define DOUBLEFRAMEBUFFER_HPP

#include<4u/gl/framebuffer.hpp>

class DoubleFrameBuffer
{
public:
	FrameBuffer *src = nullptr, *dst = nullptr;
	void resize(int w, int h)
	{
		free();
		src = new FrameBuffer(w,h);
		dst = new FrameBuffer(w,h);

		glBindTexture(GL_TEXTURE_2D, src->getTexture());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, dst->getTexture());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	void free()
	{
		if(src != nullptr)
		{
			delete src;
			src = nullptr;
		}
		if(dst != nullptr)
		{
			delete dst;
			dst = nullptr;
		}
	}
	void swap()
	{
		FrameBuffer *tmp = src;
		src = dst;
		dst = tmp;
	}
};

#endif // DOUBLEFRAMEBUFFER_HPP
