TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lSDL2main -lSDL2 -lGLEW -lGL

HEADERS += \
    window/window.h \
    window/glwindow.h \
    renderer/tiling.h \
    util/mat.hpp \
    tracer/tracer.h \
    renderer/renderer.h \
    util/color.hpp \
    util/vec2.hpp \
    util/vecn.hpp \
    util/vec3.hpp \
    util/vec4.hpp \
    util/vec.hpp \
    util/matnxm.hpp \
    tracer/material.h \
    tracer/object.h \
    tracer/scene.h \
    tracer/ray.h \
    tracer/beam.h \
    tracer/spectator.h \
    tracer/object/object.h \
    tracer/object/sphere.h \
    util/linalg/mat.hpp \
    util/linalg/matn.hpp \
    util/linalg/matnxm.hpp \
    util/linalg/vec.hpp \
    util/linalg/vec2.hpp \
    util/linalg/vec3.hpp \
    util/linalg/vec4.hpp \
    util/linalg/vecn.hpp \
    tracer/beam/beam.h \
    tracer/beam/beamset.h \
    tracer/beam/beamdistrib.h \
    tracer/beam/beamreflected.h \
    util/random.h \
    util/linalg.hpp

SOURCES += \
    window/window.cpp \
    window/glwindow.cpp \
    main.cpp \
    renderer/tiling.cpp \
    renderer/renderer.cpp \
    util/distrib/contdistrib.cpp \
    util/random.cpp

OTHER_FILES += \
    todo.txt
