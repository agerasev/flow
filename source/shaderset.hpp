#ifndef SHADERSET_HPP
#define SHADERSET_HPP

#include<4u/gl/program.hpp>
#include<4u/gl/shader.hpp>
#include<4u/gl/vertexshader.hpp>
#include<4u/gl/fragmentshader.hpp>

#include"shaderset.hpp"

#include"program/advectprogram.hpp"
#include"program/diffusestepprogram.hpp"
#include"program/drawprogram.hpp"
#include"program/fillprogram.hpp"
#include"program/forceprogram.hpp"
#include"program/pressurestepprogram.hpp"
#include"program/subtractprogram.hpp"

class ShaderSet
{
public:
	VertexShader place_vs;

	FragmentShader
	  advect_fs,
	  diffuse_step_fs,
	  force_fs,
	  pressure_step_fs,
	  subtract_fs,
	  fill_fs,
	  draw_fs;

	AdvectProgram advect_prog;
	DiffuseStepProgram diffuse_step_prog;
	ForceProgram force_prog;
	PressureStepProgram pressure_step_prog;
	SubtractProgram subtract_prog;
	FillProgram fill_prog;
	DrawProgram draw_prog;

	void loadShader(Shader &shader, const char *addr, const char *name = "glsl shader")
	{
		try
		{
			shader.loadSourceFromFile(addr);
		}
		catch(const Exception &exception)
		{
			std::cerr << name << ":\n" << exception.getMessage() << std::endl;
		}
	}

	void loadShaders()
	{
		loadShader( place_vs,         "../source/shader/place.vert",         "place shader" );
		loadShader( advect_fs,        "../source/shader/advect.frag",        "advection shader" );
		loadShader( diffuse_step_fs,  "../source/shader/diffuse_step.frag",	 "diffusion step shader" );
		loadShader( force_fs,         "../source/shader/force.frag",	     "force shader" );
		loadShader( pressure_step_fs, "../source/shader/pressure_step.frag", "pressure step shader" );
		loadShader( subtract_fs,      "../source/shader/subtract.frag",      "subtraction shader" );
		loadShader( fill_fs,          "../source/shader/fill.frag",          "fill shader" );
		loadShader( draw_fs,          "../source/shader/draw.frag",          "draw shader" );
	}

	void compileShader(Shader &shader, const char *name = "glsl shader")
	{
		try
		{
			shader.compile();
		}
		catch(const Exception &exception)
		{
			std::cerr << name << ":\n" << exception.getMessage() << std::endl;
		}
	}

	void compileShaders()
	{
		compileShader( place_vs,         "place shader" );
		compileShader( advect_fs,        "advection shader" );
		compileShader( diffuse_step_fs,  "diffusion step shader" );
		compileShader( force_fs,         "force shader" );
		compileShader( pressure_step_fs, "pressure step shader" );
		compileShader( subtract_fs,      "subtraction shader" );
		compileShader( fill_fs,          "fill shader" );
		compileShader( draw_fs,          "draw shader" );
	}

	void attachShadersToProgram(Program &prog, VertexShader &vert, FragmentShader &frag)
	{
		prog.attach(&vert);
		prog.attach(&frag);
	}

	void attachShadersToPrograms()
	{
		attachShadersToProgram( advect_prog,        place_vs, advect_fs );
		attachShadersToProgram( diffuse_step_prog,  place_vs, diffuse_step_fs );
		attachShadersToProgram( force_prog,         place_vs, force_fs );
		attachShadersToProgram( pressure_step_prog, place_vs, pressure_step_fs );
		attachShadersToProgram( subtract_prog,      place_vs, subtract_fs );
		attachShadersToProgram( fill_prog,          place_vs, fill_fs );
		attachShadersToProgram( draw_prog,          place_vs, draw_fs );
	}

	void linkProgram(Program &prog, const char *name = "glsl program")
	{
		try
		{
			prog.link();
		}
		catch(const Exception &exception)
		{
			std::cerr << name << ":\n" << exception.getMessage() << std::endl;
		}
	}

	void linkPrograms()
	{
		linkProgram( advect_prog,        "advection program" );
		linkProgram( diffuse_step_prog,  "diffusion step program" );
		linkProgram( force_prog,         "force program" );
		linkProgram( pressure_step_prog, "pressure step program" );
		linkProgram( subtract_prog,      "subtraction program" );
		linkProgram( fill_prog,          "fill program" );
		linkProgram( draw_prog,          "draw program" );
	}

	void pullVariablesFromPrograms()
	{
		/* Pull atrribs and uniforms */
		advect_prog.pull();
		diffuse_step_prog.pull();
		force_prog.pull();
		pressure_step_prog.pull();
		subtract_prog.pull();
		fill_prog.pull();
		draw_prog.pull();
	}
};

#endif // SHADERSET_HPP
