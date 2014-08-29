TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -O3

unix {
    LIBS += -lSDL2main -lSDL2 -lGLEW -lGL
}

win32 {
    INCLUDEPATH += $MINGW_PATH\include $SDL_PATH\i686-w64-mingw32\include $GLEW_PATH\include
    LIBS += -lmingw32 -L$SDL_PATH\i686-w64-mingw32\lib -lsdl2main -lsdl2 -L$GLEW_PATH\lib -lglew32 -lopengl32
}

OTHER_FILES += \
    TODO.markdown

SOURCES += \
    main.cpp

HEADERS += \
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
    4u/rand/contrand.hpp \
    4u/rand/diskrand.hpp \
    4u/rand/rand.hpp \
    4u/rand/sphericrand.hpp \
    4u/thread/mutex.hpp \
    4u/thread/thread.hpp \
    4u/util/const.hpp \
    4u/util/op.hpp \
    4u/window/event.hpp \
    4u/window/glwindow.hpp \
    4u/window/glxwindow.hpp \
    4u/window/sdlwindow.hpp \
    4u/window/window.hpp \
    common/modifier.h \
    common/result.h \
    common/viewer.h \
    common/worker.h \
    common/task.h \
    director/director.h \
    director/globalbuffer.h \
    director/result/surfaceresult.h \
    viewer/localbuffer.h \
    viewer/localviewer.h \
    worker/disributor.h \
    worker/localworker.h \
    render/algorithm/pathtracing.h \
    render/algorithm/photontracing.h \
    render/container/surface.h \
    render/container/photonmap.h \
    render/spectator.h \
    render/scene.h \
    render/ray.h \
    render/material.h \
    render/color.h \
    director/task/pathtracingtask.h \
    render/spectator/planespectator.h \
    render/object/sphere.h \
    render/object.h \
    render/params.h \
    4u/thread/threadlocalstorage.hpp \
    render/emitter.h \
    render/path.h \
    render/material/absorbingmaterial.h \
    render/material/diffusematerial.h \
    render/material/specularmaterial.h \
    render/object/plane.h \
    render/object/polygon.h \
    render/material/glowingmaterial.h \
    render/material/emittingmaterial.h \
    render/attractor.h \
    render/material/hybridmaterial.h \
    render/object/materialobject.h \
    render/material/anisotropicdiffusematerial.h \
    render/material/transparentmaterial.h \
    render/object/distanceobject.h \
    director/result/photonmapresult.h \
    render/object/juliaset.h \
    render/object/functional.h \
    render/spectator/pointspectator.h \
    render/object/mandelbrotset.h
