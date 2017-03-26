#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/sourcefiles/Animation.o \
	${OBJECTDIR}/sourcefiles/Bala.o \
	${OBJECTDIR}/sourcefiles/ContactListener.o \
	${OBJECTDIR}/sourcefiles/Entidad.o \
	${OBJECTDIR}/sourcefiles/Partida.o \
	${OBJECTDIR}/sourcefiles/Platform.o \
	${OBJECTDIR}/sourcefiles/Player.o \
	${OBJECTDIR}/sourcefiles/PlayerJoystick.o \
	${OBJECTDIR}/sourcefiles/SpriteAnimated.o \
	${OBJECTDIR}/sourcefiles/Weapon.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu libBox2D.a /usr/lib/x86_64-linux-gnu/libsfml-window.so /usr/lib/x86_64-linux-gnu/libsfml-audio.so /usr/lib/x86_64-linux-gnu/libsfml-graphics.so /usr/lib/x86_64-linux-gnu/libsfml-network.so /usr/lib/x86_64-linux-gnu/libsfml-system.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida: libBox2D.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida: /usr/lib/x86_64-linux-gnu/libsfml-window.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida: /usr/lib/x86_64-linux-gnu/libsfml-audio.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida: /usr/lib/x86_64-linux-gnu/libsfml-network.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida: /usr/lib/x86_64-linux-gnu/libsfml-system.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/sourcefiles/Animation.o: sourcefiles/Animation.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Animation.o sourcefiles/Animation.cpp

${OBJECTDIR}/sourcefiles/Bala.o: sourcefiles/Bala.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Bala.o sourcefiles/Bala.cpp

${OBJECTDIR}/sourcefiles/ContactListener.o: sourcefiles/ContactListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/ContactListener.o sourcefiles/ContactListener.cpp

${OBJECTDIR}/sourcefiles/Entidad.o: sourcefiles/Entidad.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Entidad.o sourcefiles/Entidad.cpp

${OBJECTDIR}/sourcefiles/Partida.o: sourcefiles/Partida.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Partida.o sourcefiles/Partida.cpp

${OBJECTDIR}/sourcefiles/Platform.o: sourcefiles/Platform.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Platform.o sourcefiles/Platform.cpp

${OBJECTDIR}/sourcefiles/Player.o: sourcefiles/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Player.o sourcefiles/Player.cpp

${OBJECTDIR}/sourcefiles/PlayerJoystick.o: sourcefiles/PlayerJoystick.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/PlayerJoystick.o sourcefiles/PlayerJoystick.cpp

${OBJECTDIR}/sourcefiles/SpriteAnimated.o: sourcefiles/SpriteAnimated.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/SpriteAnimated.o sourcefiles/SpriteAnimated.cpp

${OBJECTDIR}/sourcefiles/Weapon.o: sourcefiles/Weapon.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Weapon.o sourcefiles/Weapon.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/partida

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
