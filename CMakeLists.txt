# CMakeList.txt : CMake project for ElefantBlasterClient.
# Include source and define project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros.cmake")

# prevent installing to system directories.
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

# Declare the project
project ("ElefantBlasterClient" LANGUAGES C CXX)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/dist/${BUILD_CONFIGURATION_NAME}/${PROJECT_NAME}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/dist/${BUILD_CONFIGURATION_NAME}/${PROJECT_NAME}")

# Set the name of the executable
set(EXECUTABLE_NAME ${PROJECT_NAME})
# Create the executable target
add_executable(${EXECUTABLE_NAME})

# Include the source directory for header files
target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add your headers to the target
file(GLOB_RECURSE HEADER_FILES
    "${CMAKE_CURRENT_LIST_DIR}/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/*.hh"
    "${CMAKE_CURRENT_LIST_DIR}/*.hpp"
)
target_sources(${EXECUTABLE_NAME} PRIVATE ${HEADER_FILES})

# Add your sources to the target
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/*.cc"
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
)
target_sources(${EXECUTABLE_NAME} PRIVATE ${SOURCE_FILES})

# Set the runtime library to be dynamic on MSVC builds
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

include(FetchContent)

# glm (C++ mathematics library for graphics software)
FetchContent_Declare(
    glm
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/glm
)
FetchContent_MakeAvailable(glm)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE glm::glm-header-only)

# nlohmann_json (JSON for Modern C++)
FetchContent_Declare(
    nlohmann_json
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/json
)
FetchContent_MakeAvailable(nlohmann_json)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Configure SDL by calling its CMake file.
# we use EXCLUDE_FROM_ALL so that its install targets and configs don't
# pollute upwards into our configuration.
FetchContent_Declare(
    sdl
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/SDL
)
FetchContent_MakeAvailable(sdl)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3::SDL3)

# SDL_mixer (used for playing audio)
set(SDLMIXER_MIDI_NATIVE OFF)     # disable formats we don't use to make the build faster and smaller. Also some of these don't work on all platforms so you'll need to do some experimentation.
set(SDLMIXER_GME OFF)
set(SDLMIXER_WAVPACK OFF)
set(SDLMIXER_MOD OFF)
set(SDLMIXER_MOD_XMP OFF)
set(SDLMIXER_OPUS OFF)
set(SDLMIXER_MP3_MPG123 OFF)
set(SDLMIXER_VORBIS_VORBISFILE OFF)
set(SDLMIXER_FLAC_LIBFLAC OFF)
set(SDLMIXER_VENDORED ON)   # tell SDL_mixer to build its own dependencies
FetchContent_Declare(
    sdl_mixer
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/SDL_mixer
)
FetchContent_MakeAvailable(sdl_mixer)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3_mixer::SDL3_mixer)

# SDL_image (used for loading various image formats)
set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)    # disable formats we don't use to make the build faster and smaller.
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_WEBP OFF)
FetchContent_Declare(
    sdl_image
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/SDL_image
)
FetchContent_MakeAvailable(sdl_image)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3_image::SDL3_image)

# SDL_Image bug: https://github.com/libsdl-org/SDL_image/issues/506
if (APPLE AND NOT BUILD_SHARED_LIBS)
    find_library(IO_LIB ImageIO REQUIRED)
    find_library(CS_LIB CoreServices REQUIRED)
    find_library(CT_LIB CoreText REQUIRED)
    find_library(CG_LIB CoreGraphics REQUIRED)
    find_library(CF_LIB CoreFoundation REQUIRED)
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${CF_LIB} ${CT_LIB} ${IO_LIB} ${CS_LIB} ${CG_LIB})
endif()

# This section handles copying required files to the output directory after a build.

add_custom_command(
    TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets
)

if(WIN32) # These commands are only necessary on Windows for DLLs.
    add_custom_command(
        TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
        VERBATIM
    )
    add_custom_command(
        TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3_image::SDL3_image> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
        VERBATIM
    )
    add_custom_command(
        TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3_mixer::SDL3_mixer> $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
        VERBATIM
    )
endif()

# ====================================================================
# INSTALLATION RULES
# Defines what to copy when the INSTALL target is built.
# ====================================================================

# 1. Install the main executable file (ElefantBlasterClient.exe)
install(TARGETS ${EXECUTABLE_NAME}
    RUNTIME DESTINATION ${EXECUTABLE_NAME}  # Executables go into the 'bin' folder
)

# 2. Install required runtime DLLs
if(WIN32)
    install(FILES $<TARGET_FILE:SDL3::SDL3>
        DESTINATION ${EXECUTABLE_NAME}
        COMPONENT Runtime
    )
    install(FILES $<TARGET_FILE:SDL3_image::SDL3_image>
        DESTINATION ${EXECUTABLE_NAME}
        COMPONENT Runtime
    )
    install(FILES $<TARGET_FILE:SDL3_mixer::SDL3_mixer>
        DESTINATION ${EXECUTABLE_NAME}
        COMPONENT Runtime
    )
endif()

# 3. Install the resources directory
set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
if(EXISTS ${RESOURCE_DIR})
    install(DIRECTORY ${RESOURCE_DIR}
        DESTINATION ${EXECUTABLE_NAME}  # Install the 'resources' folder into the root of the install directory
    )
endif()
