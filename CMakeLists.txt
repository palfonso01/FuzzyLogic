#############################################################################
#
# Description:
# Main CMakeList.txt of the project
#
##############################################################################
project(cFuzzyLogic)

# The project classes prefix.
set(PROJECT_INCLUDE_PREFIX "FL")

#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.4)

#-----------------------------------------------------------------------------
# Project version number. An even minor number corresponds to releases.
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(PROJECT_VERSION_FULL "${PROJECT_VERSION}.${PROJECT_VERSION_PATCH}")      

# where are user-specific cmake modules
set(PROJECT_CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_CMAKE_MODULE_PATH})

# Gathering libs
SET(EXTERN_LIBS "")
SET(EXTERN_INCS "")
SET(USERF_DEFS "")

# The internal library name we want to create
string(TOLOWER ${PROJECT_NAME} PROJECT_LIBRARY_NAME)

# Get the OS
SET(OS ${CMAKE_SYSTEM_NAME})

# Request c++11 support
SET(CMAKE_CXX_STANDARD 11)

#--------------------------------------------------------------------
# Option management
#--------------------------------------------------------------------
# Choose static or shared libraries.
option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)." ON)
# Build examples as an option.
option(BUILD_EXAMPLES "Build examples." ON)

#--------------------------------------------------------------------
# By default set release configuration
#--------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE String "Choose the type of build, options are: None Debug Release" FORCE)
endif()

#-----------------------------------------------------------------------------
# The library to build.
set(PROJECT_LIBRARY ${PROJECT_LIBRARY_NAME})

# The location of project headers.
set(PROJECT_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include)

# The location of the project documentation
set(PROJECT_DOC_DIR "${PROJECT_BINARY_DIR}/doc")

# The location in which to install Example libraries.
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# The location in which to install MP binaries.
set(BINARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


#---------------------------------------------------------------------
# Platform dependent 
#----------------------------------------------------------------------
IF(WIN32 AND NOT CYGWIN)
  SET(USERF_DEFS "${USERF_DEFS} -DWIN32")
  SET(USERF_DEFS "${USERF_DEFS} -DGX") # To support exceptions
  CHECK_LIBRARY_EXISTS("winmm"  getch "" HAVE_LIBWINMM) # for timeGetTime()
  IF(HAVE_LIBWINMM)
    SET(EXTERN_LIBS ${EXTERN_LIBS} "winmm")
  ENDIF(HAVE_LIBWINMM)
ENDIF(WIN32 AND NOT CYGWIN)
IF(UNIX)
  SET(USERF_DEFS "${USERF_DEFS} -DUNIX")
  IF(APPLE)
    # We will not use rpath support.  Tell CMake to skip it.
    SET(CMAKE_SKIP_RPATH 1 CACHE INTERNAL "Whether to build with rpath." FORCE)
    SET(USERF_DEFS "${USERF_DEFS} -DAPPLE")
  ENDIF(APPLE)
ENDIF(UNIX)


#----------------------------------------------------------------------
# Third party libraries
#----------------------------------------------------------------------
IF(BUILD_EXAMPLES)
    # QT
    find_package (Qt5Gui REQUIRED)
    if(Qt5Gui_FOUND)
    SET(EXTERN_INCS ${Qt5Gui_INCLUDE_DIRS} ${EXTERN_INCS})
    SET(EXTERN_LIBS ${Qt5Gui_LIBRARIES} ${EXTERN_LIBS})
    endif()
    find_package (Qt5PrintSupport REQUIRED)
    if(Qt5PrintSupport_FOUND)
    SET(EXTERN_INCS ${Qt5PrintSupport_INCLUDE_DIRS} ${EXTERN_INCS})
    SET(EXTERN_LIBS ${Qt5PrintSupport_LIBRARIES} ${EXTERN_LIBS})
    endif()
ENDIF()

FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
	message("OPENMP FOUND")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
#----------------------------------------------------------------------
# Add intern include dir
#----------------------------------------------------------------------
include_directories(${PROJECT_INCLUDE_DIR} ${EXTERN_INCS})
#----------------------------------------------------------------------
# Add library path
#----------------------------------------------------------------------
link_directories(${LIBRARY_OUTPUT_PATH})
#----------------------------------------------------------------------
# add "doc" target for doxygen documentation building
#----------------------------------------------------------------------
find_package(Doxygen)
if (DOXYGEN_FOUND)
  if(DOXYGEN_DOT_EXECUTABLE)
    set(PROJECT_HAVE_DOT "yes")      
  else()
    set(PROJECT_HAVE_DOT "no")  
  endif()
  ## we need latex for doxygen because of the formulas
  find_package(LATEX)
  if    (NOT LATEX_COMPILER)
    message(STATUS "latex command LATEX_COMPILER not found but usually required. You will probably get warnings and user interaction on doxy run.")
  endif ()
  if    (NOT MAKEINDEX_COMPILER)
    message(STATUS "makeindex command MAKEINDEX_COMPILER not found but usually required.")
  endif ()
  if    (NOT DVIPS_CONVERTER)
    message(STATUS "dvips command DVIPS_CONVERTER not found but usually required.")
  endif ()
   
  configure_file(${PROJECT_SOURCE_DIR}/doc/config-doxygen.cmake
    ${PROJECT_DOC_DIR}/config-doxygen
    @ONLY )

  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${PROJECT_DOC_DIR}/config-doxygen)
endif()

#----------------------------------------------------------------------
# Generate the package dependent file include/${PROJECT_LIBRARY_NAME}/BMAConfig.h
#----------------------------------------------------------------------
configure_file(${PROJECT_SOURCE_DIR}/include/FLConfig.h.cmake 
  "${PROJECT_INCLUDE_DIR}/${PROJECT_INCLUDE_PREFIX}/FLConfig.h"
)

#----------------------------------------------------------------------
# Add definitions
#----------------------------------------------------------------------
ADD_DEFINITIONS(${USERF_DEFS})

#----------------------------------------------------------------------
# Propagation in sub dirs
#----------------------------------------------------------------------
SET(RESOURCES ${PROJECT_SOURCE_DIR}/example/Resources)
subdirs(src)

if(BUILD_EXAMPLES)
  subdirs(example/Example_velocity_controller)
endif()


