TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter -Wreorder

unix {
    LIBS += -lSDL2main -lSDL2 -lGLEW -lGL
}

win32 {
    INCLUDEPATH += C:\GLEW-MinGW\include C:\SDL2-2.0.3\i686-w64-mingw32\include
    LIBS += -lmingw32 -LC:\SDL2-2.0.3\i686-w64-mingw32\lib -lsdl2main -lsdl2 -LC:\GLEW-MinGW\lib -lglew32 -lopengl32
}

HEADERS += \
    render/tiling.h \
    4u/exception/exception.hpp \
    4u/exception/filenotfoundexception.hpp \
    4u/gl/fragmentshader.hpp \
    4u/gl/framebuffer.hpp \
    4u/gl/program.hpp \
    4u/gl/shader.hpp \
    4u/gl/texture.hpp \
    4u/gl/veretxbuffer.hpp \
    4u/gl/vertexshader.hpp \
    4u/la/mat.hpp \
    4u/la/matn.hpp \
    4u/la/matnm.hpp \
    4u/la/vec.hpp \
    4u/la/vec2.hpp \
    4u/la/vec3.hpp \
    4u/la/vec4.hpp \
    4u/la/vecn.hpp \
    4u/thread/mutex.hpp \
    4u/thread/thread.hpp \
    4u/util/const.hpp \
    4u/util/op.hpp \
    4u/window/glwindow.hpp \
    4u/window/window.hpp \
    4u/exception/glexception.hpp \
    render/render.h \
    4u/distrib/spheredistrib.hpp \
    4u/rand/rand.hpp \
    4u/rand/contrand.hpp \
    4u/rand/sphericrand.hpp \
    4u/window/event.hpp \
    4u/window/glwindow.hpp \
    4u/window/sdlwindow.hpp \
    4u/window/window.hpp \
    4u/window/glxwindow.hpp \
    tracer/object.h \
    tracer/spectator.h \
    tracer/tracer.h \
    tracer/scene.h \
    tracer/ray.h \
    tracer/traceparams.h \
    object/sphere.h

SOURCES += \
    main.cpp \
    render/tiling.cpp \
    render/render.cpp

OTHER_FILES += \
    TODO.md
