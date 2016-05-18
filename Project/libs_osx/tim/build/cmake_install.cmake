# Install script for directory: /Users/Tim/Documents/Shiro-Bougyo/Project/wiiuse

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "docs")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/wiiuse" TYPE FILE FILES
    "/Users/Tim/Documents/Shiro-Bougyo/Project/wiiuse/CHANGELOG.mkd"
    "/Users/Tim/Documents/Shiro-Bougyo/Project/wiiuse/LICENSE"
    "/Users/Tim/Documents/Shiro-Bougyo/Project/wiiuse/README.mkd"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/wiiuse/example" TYPE FILE FILES "/Users/Tim/Documents/Shiro-Bougyo/Project/wiiuse/example/example.c")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/wiiuse/example-sdl" TYPE FILE FILES "/Users/Tim/Documents/Shiro-Bougyo/Project/wiiuse/example-sdl/sdl.c")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/Tim/Documents/Shiro-Bougyo/Project/libs_osx/tim/build/src/cmake_install.cmake")
  include("/Users/Tim/Documents/Shiro-Bougyo/Project/libs_osx/tim/build/example/cmake_install.cmake")
  include("/Users/Tim/Documents/Shiro-Bougyo/Project/libs_osx/tim/build/example-sdl/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/Tim/Documents/Shiro-Bougyo/Project/libs_osx/tim/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
