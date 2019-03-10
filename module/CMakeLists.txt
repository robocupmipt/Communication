cmake_minimum_required(VERSION 2.8)

# try to disable boost warnings


SET(QIBUILD_COMPILE_FLAGS "-isystem")

add_definitions(${QIBUILD_COMPILE_FLAGS})


# target_compile_options(all PRIVATE -isystem)


# Give a name to the project.
project(Communication)

# You need this to find the qiBuild CMake framework
find_package(qibuild)

# Create an option to make is possible compiling the module
# as a remote executable, or as a local shared library
option(COMMUNICATION_IS_REMOTE
  "module is compiled as a remote module (ON or OFF)"
  ON)

# Create a list of source files
set(_srcs
    Communication.cpp
    Communication.h
    main.cpp)

if(COMMUNICATION_IS_REMOTE)
  add_definitions( " -DCOMMUNICATION_IS_REMOTE ")

  # Create an executable
  qi_create_bin(Communication ${_srcs})
else()
  # Create a plugin, that is a shared library, and make
  # sure it is built in lib/naoqi, so that the naoqi executable
  # can find it later
  qi_create_lib(Communication SHARED ${_srcs} SUBFOLDER naoqi)
endif()

# Tell CMake that mymodule depends on ALCOMMON and ALPROXIES.
# This will set the libraries to link mymodule with,
# the include paths, and so on
set (CMAKE_CXX_FLAGS "-isystem")
qi_use_lib(Communication ALCOMMON ALPROXIES BOOST )
