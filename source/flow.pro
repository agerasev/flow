TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lSDL2main -lSDL2 -lGLEW -lGL

HEADERS += \
    4u/complex/complex.hpp \
    4u/complex/quaternion.hpp \
    4u/exception/compilationexception.hpp \
    4u/exception/exception.hpp \
    4u/exception/filenotfoundexception.hpp \
    4u/exception/glexception.hpp \
    4u/exception/linkageexception.hpp \
    4u/gl/fragmentshader.hpp \
    4u/gl/framebuffer.hpp \
    4u/gl/program.hpp \
    4u/gl/shader.hpp \
    4u/gl/texture.hpp \
	4u/gl/vertexbuffer.hpp \
    4u/gl/vertexshader.hpp \
	4u/la/mat.hpp \
	4u/la/matn.hpp \
	4u/la/matnm.hpp \
	4u/la/vec.hpp \
	4u/la/vec2.hpp \
	4u/la/vec3.hpp \
	4u/la/vec4.hpp \
	4u/la/vecn.hpp \
    4u/random/contrand.hpp \
    4u/random/diskrand.hpp \
    4u/random/rand.hpp \
    4u/random/sphericrand.hpp \
    4u/thread/mutex.hpp \
    4u/thread/thread.hpp \
    4u/thread/threadlocalstorage.hpp \
    4u/util/const.hpp \
    4u/util/op.hpp \
    4u/window/event.hpp \
    4u/window/glwindow.hpp \
    4u/window/glxwindow.hpp \
    4u/window/sdlwindow.hpp \
	4u/window/window.hpp \
    program/advectprogram.hpp \
    program/diffusestepprogram.hpp \
    program/drawprogram.hpp \
    program/fillprogram.hpp \
    program/forceprogram.hpp \
    program/pressurestepprogram.hpp \
    program/subtractprogram.hpp \
    simulator.hpp \
    program/placeprogram.hpp \
    shape/screenshape.hpp \
    shape/shape.hpp \
    shape/quadshape.hpp \
    shaderset.hpp \
    doubleframebuffer.hpp \
    scene.hpp \
    shape/polygon.hpp

SOURCES += \
    main.cpp

OTHER_FILES += \
    shader/advect.frag \
    shader/diffuse_step.frag \
    shader/draw.frag \
    shader/fill.frag \
    shader/force.frag \
    shader/pressure_step.frag \
    shader/place.vert \
    shader/subtract.frag
