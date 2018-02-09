#############################################################################
#
# Description:
# CMakeList to build an executable
#
# Author:
# Pedro Patlan
#
##############################################################################

# SOURCE variable corresponds to the list of all the sources to build binaries.
# The generate binary comes by removing the .cpp extension to
# the source name.
#
# If you want to add/remove a source, modify here
set (DEMO_SRCS
  main.cpp
)

add_executable(velocity_controller ${DEMO_SRCS})
target_link_libraries(velocity_controller ${PROJECT_LIBRARY} ${EXTERN_LIBS})
  
