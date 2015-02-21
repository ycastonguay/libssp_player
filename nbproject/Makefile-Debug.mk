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
	${OBJECTDIR}/player/ssp_convert.o \
	${OBJECTDIR}/player/ssp_device.o \
	${OBJECTDIR}/player/ssp_eqpreset.o \
	${OBJECTDIR}/player/ssp_log.o \
	${OBJECTDIR}/player/ssp_loop.o \
	${OBJECTDIR}/player/ssp_mixer.o \
	${OBJECTDIR}/player/ssp_player.o \
	${OBJECTDIR}/player/ssp_player_bpm.o \
	${OBJECTDIR}/player/ssp_player_callbacks.o \
	${OBJECTDIR}/player/ssp_player_data.o \
	${OBJECTDIR}/player/ssp_player_encoder.o \
	${OBJECTDIR}/player/ssp_player_eq.o \
	${OBJECTDIR}/player/ssp_player_loop.o \
	${OBJECTDIR}/player/ssp_player_playback.o \
	${OBJECTDIR}/player/ssp_player_playhead.o \
	${OBJECTDIR}/player/ssp_player_seeking.o \
	${OBJECTDIR}/player/ssp_player_stream.o \
	${OBJECTDIR}/player/ssp_playerhandles.o \
	${OBJECTDIR}/player/ssp_playhead.o \
	${OBJECTDIR}/player/ssp_playlist.o \
	${OBJECTDIR}/player/ssp_playlistitem.o \
	${OBJECTDIR}/player/ssp_public.o \
	${OBJECTDIR}/vector/vector.o


# C Compiler Flags
CFLAGS=-Lbass/win32 -Lbass/osx -Lbass/linux -Lbass/linux/x64 -lbass -lbassmix -lbass_fx -lbassenc -Wl,-rpath=.

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libssp_player.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libssp_player.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libssp_player.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -s -fPIC

${OBJECTDIR}/player/ssp_bass.o: player/ssp_bass.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_bass.o player/ssp_bass.c

${OBJECTDIR}/player/ssp_convert.o: player/ssp_convert.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_convert.o player/ssp_convert.c

${OBJECTDIR}/player/ssp_device.o: player/ssp_device.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_device.o player/ssp_device.c

${OBJECTDIR}/player/ssp_eqpreset.o: player/ssp_eqpreset.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_eqpreset.o player/ssp_eqpreset.c

${OBJECTDIR}/player/ssp_log.o: player/ssp_log.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_log.o player/ssp_log.c

${OBJECTDIR}/player/ssp_loop.o: player/ssp_loop.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_loop.o player/ssp_loop.c

${OBJECTDIR}/player/ssp_mixer.o: player/ssp_mixer.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_mixer.o player/ssp_mixer.c

${OBJECTDIR}/player/ssp_player.o: player/ssp_player.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player.o player/ssp_player.c

${OBJECTDIR}/player/ssp_player_bpm.o: player/ssp_player_bpm.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_bpm.o player/ssp_player_bpm.c

${OBJECTDIR}/player/ssp_player_callbacks.o: player/ssp_player_callbacks.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_callbacks.o player/ssp_player_callbacks.c

${OBJECTDIR}/player/ssp_player_data.o: player/ssp_player_data.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_data.o player/ssp_player_data.c

${OBJECTDIR}/player/ssp_player_encoder.o: player/ssp_player_encoder.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_encoder.o player/ssp_player_encoder.c

${OBJECTDIR}/player/ssp_player_eq.o: player/ssp_player_eq.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_eq.o player/ssp_player_eq.c

${OBJECTDIR}/player/ssp_player_loop.o: player/ssp_player_loop.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_loop.o player/ssp_player_loop.c

${OBJECTDIR}/player/ssp_player_playback.o: player/ssp_player_playback.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_playback.o player/ssp_player_playback.c

${OBJECTDIR}/player/ssp_player_playhead.o: player/ssp_player_playhead.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_playhead.o player/ssp_player_playhead.c

${OBJECTDIR}/player/ssp_player_seeking.o: player/ssp_player_seeking.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_seeking.o player/ssp_player_seeking.c

${OBJECTDIR}/player/ssp_player_stream.o: player/ssp_player_stream.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_player_stream.o player/ssp_player_stream.c

${OBJECTDIR}/player/ssp_playerhandles.o: player/ssp_playerhandles.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_playerhandles.o player/ssp_playerhandles.c

${OBJECTDIR}/player/ssp_playhead.o: player/ssp_playhead.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_playhead.o player/ssp_playhead.c

${OBJECTDIR}/player/ssp_playlist.o: player/ssp_playlist.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_playlist.o player/ssp_playlist.c

${OBJECTDIR}/player/ssp_playlistitem.o: player/ssp_playlistitem.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_playlistitem.o player/ssp_playlistitem.c

${OBJECTDIR}/player/ssp_public.o: player/ssp_public.c 
	${MKDIR} -p ${OBJECTDIR}/player
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player/ssp_public.o player/ssp_public.c

${OBJECTDIR}/vector/vector.o: vector/vector.c 
	${MKDIR} -p ${OBJECTDIR}/vector
	${RM} "$@.d"
	$(COMPILE.c) -g -s -DLINUX -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vector/vector.o vector/vector.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libssp_player.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
