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
    4u/linalg/mat.hpp \
    4u/linalg/matn.hpp \
    4u/linalg/matnm.hpp \
    4u/linalg/vec.hpp \
    4u/linalg/vec2.hpp \
    4u/linalg/vec3.hpp \
    4u/linalg/vec4.hpp \
    4u/linalg/vecn.hpp \
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
    simulator.hpp

SOURCES += \
    main.cpp
