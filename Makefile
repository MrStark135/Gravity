### project related vars
INCLUDEDIRS		=./include ./SFML/include
SOURCEDIR		=./src
OBJECTDIR		=./.obj
DEPENDENCYDIR	=./.dep

CPPFILES =$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS	 =$(patsubst $(SOURCEDIR)/%.cpp,$(OBJECTDIR)/%.o,$(CPPFILES))
DEPFILES =$(patsubst $(SOURCEDIR)/%.cpp,$(DEPENDENCYDIR)/%.d,$(CPPFILES))

LIBPATH = -L"./SFML/lib"
LIBS = -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics -lopenal32
LDFLAGS = #-lgcc

PROGNAME =main

### compiler and linker related vars
CC = g++
# -g generated debugging info
# -Wall all compiler warnings
# O2 recommended optimization level
# -MP -MD are used for detecting changes in header files
CFLAGS = -g -Wall -O2
# -MMD
# -MF tells the compiler where to store the generated .d files
# $* matches % from the rule
DEPFLAGS = -MMD -MF $(DEPENDENCYDIR)/$*.d

# -o specifies the name of the executable
all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGNAME) $(LIBPATH) $(LIBS) $(LDFLAGS)

# -c only compiles the given files, doesn't link them
# $@ is the target, $^ contains all the prerequisites, $< contains only the first prerequisite
./$(OBJECTDIR)/%.o: ./$(SOURCEDIR)/%.cpp ./$(DEPENDENCYDIR)/%.d | $(DEPENDENCYDIR) $(OBJECTDIR)
	$(CC) $(CFLAGS) $(foreach inc, $(INCLUDEDIRS), -I$(inc)) $(DEPFLAGS) -c ./$< -o ./$@

# if any of the header files changes, the cpp files including them should be rebuilt
# compiler generates dependency information in .d files.
./$(DEPENDENCYDIR)/%.d:
	
include $(DEPFILES)

# if these directories do not exist, create them.
$(OBJECTDIR):
	mkdir $(OBJECTDIR)
$(DEPENDENCYDIR):
	mkdir $(DEPENDENCYDIR)

clean:
	-rm -rf $(OBJECTDIR)
	-rm -rf $(DEPENDENCYDIR)
	-rm -rf $(PROGNAME)