cmake_minimum_required(VERSION 2.8)

# Give a name to the project.
project(mymodule)

# You need this to find the qiBuild CMake framework
find_package(qibuild)

option(COMMUNICATION_IS_REMOTE
    "module is compiled as a remote module (ON or OFF)"
    OFF)

# Create a list of source files
set(_srcs
    src/communication.cpp
    src/main.cpp
    src/server.cpp
    )

  if(COMMUNICATION_IS_REMOTE)
    add_definitions( " -DCOMMUNICATION_IS_REMOTE ")
  qi_create_bin(mymodule ${_srcs})
 else()
  qi_create_lib(mymodule SHARED ${_srcs} SUBFOLDER naoqi)
endif()

# Tell CMake that mymodule depends on ALCOMMON and ALPROXIES.
# This will set the libraries to link mymodule with,
# the include paths, and so on
qi_use_lib(mymodule ALCOMMON ALPROXIES BOOST)
