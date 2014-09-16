#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include<4u/window/glwindow.hpp>

#include<4u/gl/texture.hpp>
#include<4u/gl/program.hpp>
#include<4u/gl/shader.hpp>
#include<4u/gl/vertexshader.hpp>
#include<4u/gl/fragmentshader.hpp>
#include<4u/gl/vertexbuffer.hpp>
#include<4u/gl/framebuffer.hpp>

class Simulator : public Window::Render
{
private:
	FrameBuffer *velocity, *substance;

	VertexShader *placement;

	FragmentShader
	  *advection_velocity,
	  *advection_substance,
	  *diffusion_velocity_initial,  //
	  *diffusion_velocity_step,     //
	  *diffusion_substance_initial, //
	  *diffusion_substance_step,    //
	  *forcing,
	  *pressure_initial, //
	  *pressure_step,    //
	  *velocity_pressure_subtraction,
	  *filling_velocity,
	  *filling_substance,
	  *drawing;

	Program
	  *advect_velocity,
	  *advect_substance,
	  *diffuse_velocity_initial,  //
	  *diffuse_velocity_step,     //
	  *diffuse_substance_initial, //
	  *diffuse_substance_step,    //
	  *force,
	  *press_initial, //
	  *press_step,    //
	  *subtract,
	  *fill_velocity,
	  *fill_substance,
	  *draw;
};

#endif // SIMULATOR_HPP
