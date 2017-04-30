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
	${OBJECTDIR}/motorfisico/sourcefiles/ContactListener.o \
	${OBJECTDIR}/motorfisico/sourcefiles/Cuerpo.o \
	${OBJECTDIR}/motorfisico/sourcefiles/CuerpoCircular.o \
	${OBJECTDIR}/motorfisico/sourcefiles/Motorfisico.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/Animation.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/Fondo.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/InnerClock.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/Motorgrafico.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/SpriteAnimated.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/Temporizador.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/Texto.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/VisibleBody.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/musicPlayer.o \
	${OBJECTDIR}/motorgrafico/sourcefiles/resources.o \
	${OBJECTDIR}/sourcefiles/Bala.o \
	${OBJECTDIR}/sourcefiles/Console.o \
	${OBJECTDIR}/sourcefiles/Controlador.o \
	${OBJECTDIR}/sourcefiles/Entidad.o \
	${OBJECTDIR}/sourcefiles/Explosion.o \
	${OBJECTDIR}/sourcefiles/Mapa.o \
	${OBJECTDIR}/sourcefiles/Menu.o \
	${OBJECTDIR}/sourcefiles/Partida.o \
	${OBJECTDIR}/sourcefiles/Platform.o \
	${OBJECTDIR}/sourcefiles/Player.o \
	${OBJECTDIR}/sourcefiles/PlayerJoystick.o \
	${OBJECTDIR}/sourcefiles/PlayerKeyboard.o \
	${OBJECTDIR}/sourcefiles/Weapon.o \
	${OBJECTDIR}/sourcefiles/Weaponspawner.o \
	${OBJECTDIR}/tinyxml/sourcefiles/tinystr.o \
	${OBJECTDIR}/tinyxml/sourcefiles/tinyxml.o \
	${OBJECTDIR}/tinyxml/sourcefiles/tinyxmlerror.o \
	${OBJECTDIR}/tinyxml/sourcefiles/tinyxmlparser.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas: libBox2D.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas: /usr/lib/x86_64-linux-gnu/libsfml-window.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas: /usr/lib/x86_64-linux-gnu/libsfml-audio.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas: /usr/lib/x86_64-linux-gnu/libsfml-network.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas: /usr/lib/x86_64-linux-gnu/libsfml-system.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/motorfisico/sourcefiles/ContactListener.o: motorfisico/sourcefiles/ContactListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorfisico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorfisico/sourcefiles/ContactListener.o motorfisico/sourcefiles/ContactListener.cpp

${OBJECTDIR}/motorfisico/sourcefiles/Cuerpo.o: motorfisico/sourcefiles/Cuerpo.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorfisico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorfisico/sourcefiles/Cuerpo.o motorfisico/sourcefiles/Cuerpo.cpp

${OBJECTDIR}/motorfisico/sourcefiles/CuerpoCircular.o: motorfisico/sourcefiles/CuerpoCircular.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorfisico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorfisico/sourcefiles/CuerpoCircular.o motorfisico/sourcefiles/CuerpoCircular.cpp

${OBJECTDIR}/motorfisico/sourcefiles/Motorfisico.o: motorfisico/sourcefiles/Motorfisico.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorfisico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorfisico/sourcefiles/Motorfisico.o motorfisico/sourcefiles/Motorfisico.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/Animation.o: motorgrafico/sourcefiles/Animation.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/Animation.o motorgrafico/sourcefiles/Animation.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/Fondo.o: motorgrafico/sourcefiles/Fondo.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/Fondo.o motorgrafico/sourcefiles/Fondo.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/InnerClock.o: motorgrafico/sourcefiles/InnerClock.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/InnerClock.o motorgrafico/sourcefiles/InnerClock.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/Motorgrafico.o: motorgrafico/sourcefiles/Motorgrafico.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/Motorgrafico.o motorgrafico/sourcefiles/Motorgrafico.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/SpriteAnimated.o: motorgrafico/sourcefiles/SpriteAnimated.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/SpriteAnimated.o motorgrafico/sourcefiles/SpriteAnimated.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/Temporizador.o: motorgrafico/sourcefiles/Temporizador.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/Temporizador.o motorgrafico/sourcefiles/Temporizador.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/Texto.o: motorgrafico/sourcefiles/Texto.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/Texto.o motorgrafico/sourcefiles/Texto.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/VisibleBody.o: motorgrafico/sourcefiles/VisibleBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/VisibleBody.o motorgrafico/sourcefiles/VisibleBody.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/musicPlayer.o: motorgrafico/sourcefiles/musicPlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/musicPlayer.o motorgrafico/sourcefiles/musicPlayer.cpp

${OBJECTDIR}/motorgrafico/sourcefiles/resources.o: motorgrafico/sourcefiles/resources.cpp 
	${MKDIR} -p ${OBJECTDIR}/motorgrafico/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/motorgrafico/sourcefiles/resources.o motorgrafico/sourcefiles/resources.cpp

${OBJECTDIR}/sourcefiles/Bala.o: sourcefiles/Bala.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Bala.o sourcefiles/Bala.cpp

${OBJECTDIR}/sourcefiles/Console.o: sourcefiles/Console.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Console.o sourcefiles/Console.cpp

${OBJECTDIR}/sourcefiles/Controlador.o: sourcefiles/Controlador.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Controlador.o sourcefiles/Controlador.cpp

${OBJECTDIR}/sourcefiles/Entidad.o: sourcefiles/Entidad.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Entidad.o sourcefiles/Entidad.cpp

${OBJECTDIR}/sourcefiles/Explosion.o: sourcefiles/Explosion.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Explosion.o sourcefiles/Explosion.cpp

${OBJECTDIR}/sourcefiles/Mapa.o: sourcefiles/Mapa.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Mapa.o sourcefiles/Mapa.cpp

${OBJECTDIR}/sourcefiles/Menu.o: sourcefiles/Menu.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Menu.o sourcefiles/Menu.cpp

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

${OBJECTDIR}/sourcefiles/PlayerKeyboard.o: sourcefiles/PlayerKeyboard.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/PlayerKeyboard.o sourcefiles/PlayerKeyboard.cpp

${OBJECTDIR}/sourcefiles/Weapon.o: sourcefiles/Weapon.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Weapon.o sourcefiles/Weapon.cpp

${OBJECTDIR}/sourcefiles/Weaponspawner.o: sourcefiles/Weaponspawner.cpp 
	${MKDIR} -p ${OBJECTDIR}/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sourcefiles/Weaponspawner.o sourcefiles/Weaponspawner.cpp

${OBJECTDIR}/tinyxml/sourcefiles/tinystr.o: tinyxml/sourcefiles/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/tinyxml/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml/sourcefiles/tinystr.o tinyxml/sourcefiles/tinystr.cpp

${OBJECTDIR}/tinyxml/sourcefiles/tinyxml.o: tinyxml/sourcefiles/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/tinyxml/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml/sourcefiles/tinyxml.o tinyxml/sourcefiles/tinyxml.cpp

${OBJECTDIR}/tinyxml/sourcefiles/tinyxmlerror.o: tinyxml/sourcefiles/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/tinyxml/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml/sourcefiles/tinyxmlerror.o tinyxml/sourcefiles/tinyxmlerror.cpp

${OBJECTDIR}/tinyxml/sourcefiles/tinyxmlparser.o: tinyxml/sourcefiles/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/tinyxml/sourcefiles
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml/sourcefiles/tinyxmlparser.o tinyxml/sourcefiles/tinyxmlparser.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kotj_cargamapas

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
