CXXFLAGS = -Wall -fPIC -g
LFLAGS = 
OBJECTS = mesher.o oar.o primitive.o assigner.o meshmerizer.o primmesher.o colladifier.o main.o 
LIBS = -lcollada15dom -lboost_filesystem-mt -lboost_system-mt
INCLUDES = -I/opt/local/include/ 
LIBDIRS = -L/opt/local/lib

default:	all

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $^ $(LIBDIRS) -o oarcoll $(LIBS)

main.o : src/meshmerizer.h src/primmesher.h src/colladifier.h src/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^

colladifier.o : src/colladifier.cpp src/colladifier.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^

assigner.o : lib/assigner.cpp
	$(CXX) $(CXXFLAGS) -c $^

primitive.o : lib/assigner.h src/utils.h src/prim_enum.h src/primitive.cpp
	$(CXX) $(CXXFLAGS) -c $^

mesher.o : src/mesher.cpp
	$(CXX) $(CXXFLAGS) -c $^

oar.o : src/oar.cpp
	$(CXX) $(CXXFLAGS) -c $^

primmesher.o : src/primmesher.cpp
	$(CXX) $(CXXFLAGS) -c $^

meshmerizer.o : src/meshmerizer.cpp src/primmesher.h
	$(CXX) $(CXXFLAGS) -c $^
	
clean:
	rm -f oarcoll main.o $(OBJECTS) *~ src/*.gch