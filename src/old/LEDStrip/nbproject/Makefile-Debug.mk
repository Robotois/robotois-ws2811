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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/d2a6917d/dma.o \
	${OBJECTDIR}/_ext/d2a6917d/mailbox.o \
	${OBJECTDIR}/_ext/d2a6917d/pcm.o \
	${OBJECTDIR}/_ext/d2a6917d/pwm.o \
	${OBJECTDIR}/_ext/d2a6917d/rpihw.o \
	${OBJECTDIR}/_ext/d2a6917d/ws2811.o \
	${OBJECTDIR}/LEDStrip.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ws2811

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ws2811: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ws2811 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/d2a6917d/dma.o: ../libs/dma.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d2a6917d
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2a6917d/dma.o ../libs/dma.c

${OBJECTDIR}/_ext/d2a6917d/mailbox.o: ../libs/mailbox.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d2a6917d
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2a6917d/mailbox.o ../libs/mailbox.c

${OBJECTDIR}/_ext/d2a6917d/pcm.o: ../libs/pcm.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d2a6917d
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2a6917d/pcm.o ../libs/pcm.c

${OBJECTDIR}/_ext/d2a6917d/pwm.o: ../libs/pwm.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d2a6917d
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2a6917d/pwm.o ../libs/pwm.c

${OBJECTDIR}/_ext/d2a6917d/rpihw.o: ../libs/rpihw.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d2a6917d
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2a6917d/rpihw.o ../libs/rpihw.c

${OBJECTDIR}/_ext/d2a6917d/ws2811.o: ../libs/ws2811.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d2a6917d
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2a6917d/ws2811.o ../libs/ws2811.c

${OBJECTDIR}/LEDStrip.o: LEDStrip.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LEDStrip.o LEDStrip.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
