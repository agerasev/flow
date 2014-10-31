#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include<functional>

#include<4u/window/glwindow.hpp>

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>

#include<4u/gl/texture.hpp>
#include<4u/gl/vertexbuffer.hpp>
#include<4u/gl/framebuffer.hpp>

#include"shaderset.hpp"
#include"doubleframebuffer.hpp"

#include"shape/screenshape.hpp"
#include"shape/quadshape.hpp"

class Simulator : public Window::Render, public Window::Listener
{
private:
	int width, height;

	DoubleFrameBuffer velocity, substance;

	ShaderSet shaders;

	ScreenShape screen_shape;
	QuadShape quad_shape;

    double delta = 1e-2;
    fvec2 force = fvec2(0.0,1.0);
    int visc_iter = 0x20, sub_iter = 0x1, pres_iter = 0x200;
    double viscous_factor = 0.0001;
    double diffuse_factor = 0.000001;

    bool save_flag = false;
	SDL_Surface *image_buffer = nullptr;
	int frame_count = 0;

	void loadShapes()
	{
		screen_shape.loadBuffers();
		quad_shape.loadBuffers();
	}

	void performOperation(
			PlaceProgram &prog,
			Shape &shape,
			std::function<void()> setter,
			FrameBuffer *buffer = nullptr
			)
	{
		if(buffer != nullptr)
		{
			buffer->bind();
		}

		prog.enable();

		setter();

		prog.enableAttribs();
		shape.bind();
		prog.pointVertex();
		shape.unbind();
		shape.draw();
		prog.disableAttribs();
		prog.disable();

		FrameBuffer::unbind();
	}

	void performOperation(
			PlaceProgram &prog,
			std::function<void()> setter,
			FrameBuffer *buffer = nullptr
			)
	{
		performOperation(prog, screen_shape, [this,&prog,setter]()
		{
			prog.setTransformation(fmat2{2.0,0.0,0.0,2.0});
			prog.setTranslation(fvec2(-1.0,-1.0));
			setter();
		},
		buffer);
	}

public:
	virtual void init() throw(Exception) override
	{
		shaders.loadShaders();
		shaders.compileShaders();
		shaders.attachShadersToPrograms();
		shaders.linkPrograms();
		shaders.pullVariablesFromPrograms();

		loadShapes();
	}

	virtual void dispose() override
	{
		velocity.free();
		substance.free();
		if(image_buffer != nullptr)
		{
			SDL_FreeSurface(image_buffer);
			image_buffer = nullptr;
		}
	}

	virtual void resize(const Window::Size &size) override
	{
		dispose();
		width = size.w;
		height = size.h;

		velocity.resize(width,height);
		substance.resize(width,height);

		/* Clear velocity */
		performOperation(shaders.fill_prog, [this]()
		{
			shaders.fill_prog.setColor(fvec4(0.0,0.0,0.0,0.0));
		},
		velocity.src);
		/* Clear substance */
		performOperation(shaders.fill_prog, [this]()
		{
			shaders.fill_prog.setColor(fvec4(0.0,0.0,0.0,0.0));
		},
		substance.src);

		/* Fill velocity */
		performOperation(shaders.fill_prog, quad_shape, [this]()
		{
			shaders.fill_prog.setTransformation(0.2f*fmat2{(1.0*height)/width,0.0,0.0,1.0});
            shaders.fill_prog.setTranslation(fvec2(-0.32,0.1));
            shaders.fill_prog.setColor(fvec4(2.0,0.0,0.0,1.0));
		},
		velocity.src);
		/* Draw quadraic substance */
		performOperation(shaders.fill_prog, quad_shape, [this]()
		{
			shaders.fill_prog.setTransformation(0.2f*fmat2{(1.0*height)/width,0.0,0.0,1.0});
			shaders.fill_prog.setTranslation(fvec2(-0.32,0.1));
			shaders.fill_prog.setColor(fvec4(1.0,1.0,0.0,0.0));
		},
		substance.src);
		/* Fill velocity */
		performOperation(shaders.fill_prog, quad_shape, [this]()
		{
			shaders.fill_prog.setTransformation(0.2f*fmat2{(1.0*height)/width,0.0,0.0,1.0});
			shaders.fill_prog.setTranslation(fvec2(0.32,-0.1));
            shaders.fill_prog.setColor(fvec4(-2.0,0.0,0.0,1.0));
		},
		velocity.src);
		/* Draw quadraic substance */
		performOperation(shaders.fill_prog, quad_shape, [this]()
		{
			shaders.fill_prog.setTransformation(0.2f*fmat2{(1.0*height)/width,0.0,0.0,1.0});
			shaders.fill_prog.setTranslation(fvec2(0.32,-0.1));
			shaders.fill_prog.setColor(fvec4(0.0,1.0,1.0,0.0));
		},
		substance.src);

		image_buffer = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,24,0x0000ff,0x00ff00,0xff0000,0x000000);
	}

	virtual void display() override
	{
		/* Advection of velocity */
		performOperation(shaders.advect_prog, [this]()
		{
			shaders.advect_prog.bindSourceSampler(velocity.src->getTexture());
			shaders.advect_prog.bindVelocitySampler(velocity.src->getTexture());
			shaders.advect_prog.setDelta(delta);
		},
		velocity.dst);
		velocity.swap();

		/* Viscous diffusion of velocity */
		for(int i = 0; i < visc_iter; ++i)
		{
			performOperation(shaders.diffuse_step_prog, [this]()
			{
				shaders.diffuse_step_prog.bindSourceSampler(velocity.src->getTexture());
				shaders.diffuse_step_prog.setFactor(viscous_factor);
				shaders.diffuse_step_prog.setDelta(delta);
			},
			velocity.dst);
			velocity.swap();
		}

        /* Viscous diffusion of substance */
        for(int i = 0; i < visc_iter; ++i)
        {
            performOperation(shaders.diffuse_step_prog, [this]()
            {
                shaders.diffuse_step_prog.bindSourceSampler(substance.src->getTexture());
                shaders.diffuse_step_prog.setFactor(diffuse_factor);
                shaders.diffuse_step_prog.setDelta(delta);
            },
            substance.dst);
            substance.swap();
        }

        /* Force application */
        performOperation(shaders.force_prog, [this]()
        {
            shaders.force_prog.bindVelocitySampler(velocity.src->getTexture());
            shaders.force_prog.setDelta(delta);
            shaders.force_prog.setForce(force);
        },
        velocity.dst);
        velocity.swap();

		for(int j = 0; j < sub_iter; ++j)
		{
			/* Computing pressure */
			for(int i = 0; i < pres_iter; ++i)
			{
				performOperation(shaders.pressure_step_prog, [this]()
				{
					shaders.pressure_step_prog.bindVelocitySampler(velocity.src->getTexture());
				},
				velocity.dst);
				velocity.swap();
			}

			/* Subtracting pressure gradient */
			performOperation(shaders.subtract_prog, [this]()
			{
				shaders.subtract_prog.bindVelocitySampler(velocity.src->getTexture());
			},
			velocity.dst);
			velocity.swap();
		}

		/* Advection of substance */
		performOperation(shaders.advect_prog, [this]()
		{
			shaders.advect_prog.bindSourceSampler(substance.src->getTexture());
			shaders.advect_prog.bindVelocitySampler(velocity.src->getTexture());
			shaders.advect_prog.setDelta(delta);
		},
		substance.dst);
		substance.swap();

		/* Draw */
		performOperation(shaders.draw_prog, [this]()
		{
			shaders.draw_prog.bindSubstanceSampler(substance.src->getTexture());
			shaders.draw_prog.bindVelocitySampler(velocity.src->getTexture());
		});

		/* Save to file */
		if(save_flag)
		{
			glReadPixels(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE,image_buffer->pixels);
			char filename[22] = "renderoutput/0000.bmp";
			const char *symbols = "0123456789";
			filename[16] = symbols[(frame_count/1)%10];
			filename[15] = symbols[(frame_count/10)%10];
			filename[14] = symbols[(frame_count/100)%10];
			filename[13] = symbols[(frame_count/1000)%10];
			SDL_SaveBMP(image_buffer,filename);
		}

		++frame_count;
	}

	virtual void handle(const Event &) override
	{

	}
};

#endif // SIMULATOR_HPP
