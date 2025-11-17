# Install script for directory: /home/NN/openai-mpc/src/openai-mpc/liboai/liboai

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/liboai.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/liboai.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/components" TYPE FILE FILES
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/audio.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/azure.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/chat.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/completions.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/responses.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/edits.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/embeddings.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/files.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/fine_tunes.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/images.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/models.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/components/moderations.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/core" TYPE FILE FILES
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/core/authorization.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/core/exception.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/core/netimpl.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/core/network.h"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/include/core/response.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/oai/oaiTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/oai/oaiTargets.cmake"
         "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/CMakeFiles/Export/175a4203fe1414b244c4e02288d7dbc4/oaiTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/oai/oaiTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/oai/oaiTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/oai" TYPE FILE FILES "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/CMakeFiles/Export/175a4203fe1414b244c4e02288d7dbc4/oaiTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/oai" TYPE FILE FILES "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/CMakeFiles/Export/175a4203fe1414b244c4e02288d7dbc4/oaiTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/oai" TYPE FILE FILES
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/oaiConfig.cmake"
    "/home/NN/openai-mpc/src/openai-mpc/liboai/liboai/oaiConfigVersion.cmake"
    )
endif()

