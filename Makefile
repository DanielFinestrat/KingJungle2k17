# Name of the executable created
Target := KingOfTheJungle

BinPath 			:= ./
BuildPath 			:= ./obj

SOURCE_DIRS			:= $(shell find src -type d -not -path "src")
SourcePath			:= $(shell find src -name '*.cpp')

CXX					:= g++
CXXFLAGS 			:= -ffast-math -g -Wall -std=c++11
CPPFLAGS        	:= -I/usr/include -I./src -I./src/include
LDFLAGS				:= -L/usr/lib
LIBS 				:= -lsfml-audio -lsfml-system -lsfml-graphics -lsfml-window

EXECUTABLE 			:= $(BinPath)/$(Target)
SRC 	   			:= $(wildcard $(SourcePath)/*.cpp)					#no hace nada
OBJ					:= $(patsubst src/%.cpp,obj/%.o,$(SourcePath))

SOURCE_DIRS 		:= $(patsubst src/%,obj/%,$(SOURCE_DIRS))

ifeq ($(OS),Windows_NT)
ICO 				= ico/game_icon_res.rc
ICOOBJ				= $(patsubst ico/%.rc,obj/%.o,$(ICO))
endif

#MAKE OPTIONS
.PHONY: all clean

all: prepare ico compile 	
	$(info ----------------------------------------------)	
	$(info Compile OK)

prepare:
	$(info ==============================================)
	$(info Creating folder structure)
	$(info ==============================================)
	@mkdir -p $(BinPath)
	@mkdir -p $(SOURCE_DIRS)

ico:
    ifeq ($(OS),Windows_NT)
		$(info ==============================================)
		$(info Creating ico object)
		$(info Compiling-> $(ICOOBJ))
		$(info ==============================================)
		$(shell windres $(ICO) -o $(ICOOBJ))
    endif

obj/%.o: src/%.cpp
	$(info Compiling-> $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

compile: $(OBJ)
	$(info ----------------------------------------------)
	$(info Linking executable $(Target)...)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJ) -o $(EXECUTABLE) $(LDFLAGS) $(LIBS) $(ICOOBJ)

clean:
	$(info ==============================================)
	$(info Cleaning Objects and Binaries... )
	$(info ==============================================)
	@$(RM) $(OBJ)
	@$(RM) $(EXECUTABLE)
