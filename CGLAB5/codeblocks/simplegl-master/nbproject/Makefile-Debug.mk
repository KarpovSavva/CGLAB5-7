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
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/State.o \
	${OBJECTDIR}/states/BackgroundSelector.o \
	${OBJECTDIR}/tools/MoveTool.o \
	${OBJECTDIR}/objects/Sphere.o \
	${OBJECTDIR}/Point.o \
	${OBJECTDIR}/Tool.o \
	${OBJECTDIR}/objects/Snowman.o \
	${OBJECTDIR}/_ext/1587885376/math.o \
	${OBJECTDIR}/Viewport.o \
	${OBJECTDIR}/Engine.o \
	${OBJECTDIR}/tools/RotationTool.o \
	${OBJECTDIR}/Color.o \
	${OBJECTDIR}/_ext/1587885376/Camera.o \
	${OBJECTDIR}/objects/Triangle.o \
	${OBJECTDIR}/Object.o \
	${OBJECTDIR}/states/TriangleSelector.o \
	${OBJECTDIR}/vendor/ModelLoader.o \
	${OBJECTDIR}/objects/Model.o \
	${OBJECTDIR}/objects/Teapot.o \
	${OBJECTDIR}/objects/Cone.o \
	${OBJECTDIR}/StateMachine.o \
	${OBJECTDIR}/objects/Plane.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsimplegl.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsimplegl.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -framework OpenGL -framework GLUT -dynamiclib -install_name libsimplegl.${CND_DLIB_EXT} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsimplegl.${CND_DLIB_EXT} -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/State.o: State.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/State.o State.cpp

${OBJECTDIR}/states/BackgroundSelector.o: states/BackgroundSelector.cpp 
	${MKDIR} -p ${OBJECTDIR}/states
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/states/BackgroundSelector.o states/BackgroundSelector.cpp

${OBJECTDIR}/tools/MoveTool.o: tools/MoveTool.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/tools/MoveTool.o tools/MoveTool.cpp

${OBJECTDIR}/objects/Sphere.o: objects/Sphere.cpp 
	${MKDIR} -p ${OBJECTDIR}/objects
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/objects/Sphere.o objects/Sphere.cpp

${OBJECTDIR}/Point.o: Point.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Point.o Point.cpp

${OBJECTDIR}/Tool.o: Tool.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Tool.o Tool.cpp

${OBJECTDIR}/objects/Snowman.o: objects/Snowman.cpp 
	${MKDIR} -p ${OBJECTDIR}/objects
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/objects/Snowman.o objects/Snowman.cpp

${OBJECTDIR}/_ext/1587885376/math.o: /Users/hector0193/Proyectos/idi/Bloc3/simplegl/math.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1587885376
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1587885376/math.o /Users/hector0193/Proyectos/idi/Bloc3/simplegl/math.cpp

${OBJECTDIR}/Viewport.o: Viewport.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Viewport.o Viewport.cpp

${OBJECTDIR}/Engine.o: Engine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Engine.o Engine.cpp

${OBJECTDIR}/tools/RotationTool.o: tools/RotationTool.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/tools/RotationTool.o tools/RotationTool.cpp

${OBJECTDIR}/Color.o: Color.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Color.o Color.cpp

${OBJECTDIR}/_ext/1587885376/Camera.o: /Users/hector0193/Proyectos/idi/Bloc3/simplegl/Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1587885376
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1587885376/Camera.o /Users/hector0193/Proyectos/idi/Bloc3/simplegl/Camera.cpp

${OBJECTDIR}/objects/Triangle.o: objects/Triangle.cpp 
	${MKDIR} -p ${OBJECTDIR}/objects
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/objects/Triangle.o objects/Triangle.cpp

${OBJECTDIR}/Object.o: Object.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Object.o Object.cpp

${OBJECTDIR}/states/TriangleSelector.o: states/TriangleSelector.cpp 
	${MKDIR} -p ${OBJECTDIR}/states
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/states/TriangleSelector.o states/TriangleSelector.cpp

${OBJECTDIR}/vendor/ModelLoader.o: vendor/ModelLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/vendor
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/vendor/ModelLoader.o vendor/ModelLoader.cpp

${OBJECTDIR}/objects/Model.o: objects/Model.cpp 
	${MKDIR} -p ${OBJECTDIR}/objects
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/objects/Model.o objects/Model.cpp

${OBJECTDIR}/objects/Teapot.o: objects/Teapot.cpp 
	${MKDIR} -p ${OBJECTDIR}/objects
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/objects/Teapot.o objects/Teapot.cpp

${OBJECTDIR}/objects/Cone.o: objects/Cone.cpp 
	${MKDIR} -p ${OBJECTDIR}/objects
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/objects/Cone.o objects/Cone.cpp

${OBJECTDIR}/StateMachine.o: StateMachine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/StateMachine.o StateMachine.cpp

${OBJECTDIR}/objects/Plane.o: objects/Plane.cpp 
	${MKDIR} -p ${OBJECTDIR}/objects
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/objects/Plane.o objects/Plane.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsimplegl.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
