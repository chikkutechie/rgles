
lib_PROGRAMS = librgl.a librgui.a

bin_PROGRAMS = guitest \
               colors \
               depthtest \
               lighting \
               texturing \
               primitives \
               transformations \


librgl_a_HEADERS = ../src/rglinterface.h \
            ../src/rglinterfaceimplV_0_1.h \
            ../src/rglutils.h
			
librgl_a_SOURCES = \
             ../src/egl/regl.cpp \
             ../src/gles/rgl.cpp \
             ../src/gles/rglinterfaceimplV_0_1.cpp \
             ../src/gles/rglmatrix.cpp
			 
librgl_a_OBJS = \
             regl.o \
             rgl.o \
             rgles1ximpl.o \
             rglmatrix.o

librgui_a_SOURCES = \
			 ../src/gui/rapp.cpp \
			 ../src/gui/rwin.cpp \
			 ../src/gui/rglwin.cpp
			 
librgui_a_OBJS = \
			 rtime.o \
			 rapp.o \
			 rwin.o \
			 rglwin.o

guitest_SOURCES = ../examples/guitest.cpp
colors_SOURCES = ../examples/colors.cpp
depthtest_SOURCES = ../examples/depthtest.cpp
lighting_SOURCES = ../examples/lighting.cpp
texturing_SOURCES = ../examples/texturing.cpp
primitives_SOURCES = ../examples/primitives.cpp
transformations_SOURCES = ../examples/transformations.cpp

INCLUDES = -I../src -I../inc -I../src/gui -I../src/gles
LIBS = librgui.a librgl.a -lGL -lGLU -lX11

CXXFLAGS = -g3 -Wall -DGL_GLEXT_PROTOTYPES

all: $(lib_PROGRAMS) $(bin_PROGRAMS) 

librgl.a : $(librgl_a_OBJS)
	ar -cvq $@ $(librgl_a_OBJS)
	
librgui.a : $(librgui_a_OBJS)
	ar -cvq $@ $(librgui_a_OBJS)
	
primitives : $(primitives_SOURCES) $(lib_PROGRAMS)
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDES) $(LIBS)

transformations : $(transformations_SOURCES) $(lib_PROGRAMS)
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDES) $(LIBS)

regl.o : ../src/egl/regl.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<

rgl.o : ../src/gles/rgl.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<

rgles1ximpl.o : ../src/gles/rgles1ximpl.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<

rglmatrix.o : ../src/gles/rglmatrix.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<

rtime.o : ../src/gui/rtime.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<
	
	
rapp.o : ../src/gui/rapp.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<
	
rwin.o : ../src/gui/rwin.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<
	
rglwin.o : ../src/gui/rglwin.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<
	
guitest :	$(guitest_SOURCES) $(lib_PROGRAMS) $(lib_PROGRAMS)
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDES) $(LIBS)

colors: $(colors_SOURCES) $(lib_PROGRAMS)
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDES) $(LIBS)

depthtest: $(depthtest_SOURCES) $(lib_PROGRAMS)
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDES) $(LIBS)

lighting: $(lighting_SOURCES)  $(lib_PROGRAMS)
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDES) $(LIBS)

texturing: $(texturing_SOURCES)  $(lib_PROGRAMS)
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDES) $(LIBS)

clean:
	rm -rf $(bin_PROGRAMS) $(lib_PROGRAMS) *.o

