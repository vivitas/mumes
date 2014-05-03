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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/open_exr_io.o \
	${OBJECTDIR}/ScopeClock.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/common_filter.o \
	${OBJECTDIR}/file_system_operations.o \
	${OBJECTDIR}/cpu_filter.o


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
LDLIBSOPTIONS=-lIlmImf -lHalf -lIex -lImath -lIlmThread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk /home/filip/dev/mumes/out

/home/filip/dev/mumes/out: ${OBJECTFILES}
	${MKDIR} -p /home/filip/dev/mumes
	${LINK.cc} -o /home/filip/dev/mumes/out ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/open_exr_io.o: open_exr_io.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include -I/usr/include/OpenEXR -MMD -MP -MF $@.d -o ${OBJECTDIR}/open_exr_io.o open_exr_io.cpp

${OBJECTDIR}/ScopeClock.o: ScopeClock.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include -I/usr/include/OpenEXR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ScopeClock.o ScopeClock.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include -I/usr/include/OpenEXR -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/common_filter.o: common_filter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include -I/usr/include/OpenEXR -MMD -MP -MF $@.d -o ${OBJECTDIR}/common_filter.o common_filter.cpp

${OBJECTDIR}/file_system_operations.o: file_system_operations.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include -I/usr/include/OpenEXR -MMD -MP -MF $@.d -o ${OBJECTDIR}/file_system_operations.o file_system_operations.cpp

${OBJECTDIR}/cpu_filter.o: cpu_filter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include -I/usr/include/OpenEXR -MMD -MP -MF $@.d -o ${OBJECTDIR}/cpu_filter.o cpu_filter.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} /home/filip/dev/mumes/out

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
