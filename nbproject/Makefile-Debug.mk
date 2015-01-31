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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/player/ssp_bass.o \
	${OBJECTDIR}/player/ssp_convertaudio.o \
	${OBJECTDIR}/player/ssp_device.o \
	${OBJECTDIR}/player/ssp_eqpreset.o \
	${OBJECTDIR}/player/ssp_loop.o \
	${OBJECTDIR}/player/ssp_marker.o \
	${OBJECTDIR}/player/ssp_mixer.o \
	${OBJECTDIR}/player/ssp_player.o \
	${OBJECTDIR}/player/ssp_player_playback.o \
	${OBJECTDIR}/player/ssp_player_seeking.o \
	${OBJECTDIR}/player/ssp_playerchannels.o \
	${OBJECTDIR}/player/ssp_playerplugins.o \
	${OBJECTDIR}/player/ssp_playhead.o \
	${OBJECTDIR}/player/ssp_playlist.o \
	${OBJECTDIR}/player/ssp_public.o \
	${OBJECTDIR}/vector/vector.o


# C Compiler Flags
CFLAGS=-Lbass/win32 -Lbass/osx -Lbass/linux -Lbass/linux/x64 -lbass -lbassmix -lbass_fx

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibssp_player.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibssp_player.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibssp_player.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/player/ssp_bass.o: player/ssp_bass.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_bass.o player/ssp_bass.c

${OBJECTDIR}/player/ssp_convertaudio.o: player/ssp_convertaudio.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_convertaudio.o player/ssp_convertaudio.c

${OBJECTDIR}/player/ssp_device.o: player/ssp_device.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_device.o player/ssp_device.c

${OBJECTDIR}/player/ssp_eqpreset.o: player/ssp_eqpreset.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_eqpreset.o player/ssp_eqpreset.c

${OBJECTDIR}/player/ssp_loop.o: player/ssp_loop.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_loop.o player/ssp_loop.c

${OBJECTDIR}/player/ssp_marker.o: player/ssp_marker.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_marker.o player/ssp_marker.c

${OBJECTDIR}/player/ssp_mixer.o: player/ssp_mixer.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_mixer.o player/ssp_mixer.c

${OBJECTDIR}/player/ssp_player.o: player/ssp_player.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player.o player/ssp_player.c

${OBJECTDIR}/player/ssp_player_playback.o: player/ssp_player_playback.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_playback.o player/ssp_player_playback.c

${OBJECTDIR}/player/ssp_player_seeking.o: player/ssp_player_seeking.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_seeking.o player/ssp_player_seeking.c

${OBJECTDIR}/player/ssp_playerchannels.o: player/ssp_playerchannels.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_playerchannels.o player/ssp_playerchannels.c

${OBJECTDIR}/player/ssp_playerplugins.o: player/ssp_playerplugins.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_playerplugins.o player/ssp_playerplugins.c

${OBJECTDIR}/player/ssp_playhead.o: player/ssp_playhead.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_playhead.o player/ssp_playhead.c

${OBJECTDIR}/player/ssp_playlist.o: player/ssp_playlist.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_playlist.o player/ssp_playlist.c

${OBJECTDIR}/player/ssp_public.o: player/ssp_public.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_public.o player/ssp_public.c

${OBJECTDIR}/vector/vector.o: vector/vector.c 
	${MKDIR} -p ${OBJECTDIR}/vector
	${RM} "$@.d"
	$(COMPILE.c) -g -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vector/vector.o vector/vector.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibssp_player.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
