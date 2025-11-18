# CMakeList.txt : CMake project for BomberMan, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# prevent installing to system directories.
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

# Declare the project
project ("ElefantBlasterClient" LANGUAGES C CXX)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/dist/${BUILD_CONFIGURATION_NAME}/${PROJECT_NAME}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/dist/${BUILD_CONFIGURATION_NAME}/${PROJECT_NAME}")

if ((APPLE AND NOT CMAKE_SYSTEM_NAME MATCHES "Darwin") OR EMSCRIPTEN)
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")    # Disable shared builds on platforms where it does not make sense to use them
    set(SDL_SHARED OFF)
else()
    set(SDL_SHARED ON)
endif()

if(MSVC)
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
        add_definitions(/MP)                # parallelize each target, unless Ninja is the generator
    endif()
endif()

# Set the name of the executable
set(EXECUTABLE_NAME ${PROJECT_NAME})

# Create an executable or a shared library based on the platform and add our sources to it
if (ANDROID)
    # The SDL java code is hardcoded to load libmain.so on android, so we need to change EXECUTABLE_NAME
    set(EXECUTABLE_NAME main)
    add_library(${EXECUTABLE_NAME} SHARED)
else()
    add_executable(${EXECUTABLE_NAME})
endif()

target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB_RECURSE PROTO_FILES "${CMAKE_CURRENT_LIST_DIR}/src/network/protocols/*")

# Add your sources to the target
target_sources (${EXECUTABLE_NAME}
PRIVATE
    src/entrypoint/entrypoint.cpp
    src/states/sdl_state.h
    src/states/sdl_state.cpp
    src/core/asset_manager.h
    src/core/asset_manager.cpp
    src/effects/timer.h
    src/effects/animation.h
    src/entities/map_tile.h
    src/entities/spoil.h
    src/map/map_manager.h
    src/map/map_manager.cpp
    src/states/game_state.h
    src/states/game_state.cpp
    src/entities/player.h
    src/effects/movement.h
    src/effects/movement.cpp
    src/map/map_updater.h
    src/network/net_client.h
    src/network/net_client.cpp
    src/network/protocol_def.h
    ${PROTO_FILES}
)

# What is iosLaunchScreen.storyboard? This file describes what Apple's mobile platforms
# should show the user while the application is starting up. If you don't include one,
# then you get placed in a compatibility mode that does not allow HighDPI.
# This file is referenced inside Info.plist.in, where it is marked as the launch screen file.
# It is also ignored on non-Apple platforms.

# To get an app icon on Apple platforms, add it to your executable.
# Afterward, the image file in Info.plist.in.
if(APPLE)
    target_sources("${EXECUTABLE_NAME}" PRIVATE "resources/logo.png")
endif()

# Set C++ version
target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_20)

# on Web targets, we need CMake to generate a HTML webpage.
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

include(FetchContent)

# glm (C++ mathematics library for graphics software)
FetchContent_Declare(
    glm
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/glm
)
FetchContent_MakeAvailable(glm)

# nlohmann_json (JSON for Modern C++)
FetchContent_Declare(
    nlohmann_json
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/json
)
FetchContent_MakeAvailable(nlohmann_json)

# abseil-cpp (Abseil C++ Common Libraries)
FetchContent_Declare(
    absl
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/abseil-cpp
)
FetchContent_MakeAvailable(absl)

# Protocol Buffers (protobuf)
set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(protobuf_WITH_ZLIB OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_PROTOC_BINARIES OFF CACHE BOOL "" FORCE)
set(protobuf_INSTALL OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(protobuf_MSVC_STATIC_RUNTIME ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    protobuf
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/protobuf
)
FetchContent_MakeAvailable(protobuf)

# Configure SDL by calling its CMake file.
# we use EXCLUDE_FROM_ALL so that its install targets and configs don't
# pollute upwards into our configuration.
FetchContent_Declare(
    sdl
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/SDL
)
FetchContent_MakeAvailable(sdl)

# If you don't want SDL_ttf, then remove this section.
set(SDLTTF_VENDORED ON) # tell SDL_ttf to build its own dependencies
FetchContent_Declare(
    sdl_ttf
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/SDL_ttf
)
FetchContent_MakeAvailable(sdl_ttf)

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

# SDL_net (used for networking)
set(SDLNET_VENDORED ON)
FetchContent_Declare(
    sdl_net
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/SDL_net
)
FetchContent_MakeAvailable(sdl_net)

# Link SDL to our executable. This also makes its include directory available to us.
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    glm::glm-header-only
    nlohmann_json::nlohmann_json
    protobuf::libprotobuf
    $<$<NOT:$<BOOL:${EMSCRIPTEN}>>:websocketpp::websocketpp>
#   SDL3_ttf::SDL3_ttf      # remove if you are not using SDL_ttf
    SDL3_mixer::SDL3_mixer  # remove if you are not using SDL_mixer
    SDL3_image::SDL3_image  # remove if you are not using SDL_image
#   SDL3_net::SDL3_net      # remove if you are not using SDL_net
    SDL3::SDL3              # If using satelite libraries, SDL must be the last item in the list.
)

# SDL_Image bug: https://github.com/libsdl-org/SDL_image/issues/506
if (APPLE AND NOT BUILD_SHARED_LIBS)
    find_library(IO_LIB ImageIO REQUIRED)
    find_library(CS_LIB CoreServices REQUIRED)
    find_library(CT_LIB CoreText REQUIRED)
    find_library(CG_LIB CoreGraphics REQUIRED)
    find_library(CF_LIB CoreFoundation REQUIRED)
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${CF_LIB} ${CT_LIB} ${IO_LIB} ${CS_LIB} ${CG_LIB})
endif()

# ===================================================================
# ASSET & RESOURCE HANDLING – FULLY AUTOMATIC FOR YOUR BOMBERMAN PROJECT
# Supports: Windows | Linux | macOS | iOS | Android | Web (Emscripten)
# Automatically copies:
#   - assets/      → all game data (audio, graphics, levels, etc.)
#   - resources/   → logo.png, iosLaunchScreen.storyboard, Info.plist.in
# ===================================================================

set(DIST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Game data folder
set(ASSETS_DIR "${CMAKE_CURRENT_LIST_DIR}/assets")
# Bundle resources (Apple-specific: icons, splash, plist, etc.)
set(RESOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}/resources")

# 1. Recursively collect all files in assets/
file(GLOB_RECURSE ASSET_FILES "${ASSETS_DIR}/*")
list(FILTER ASSET_FILES EXCLUDE REGEX "[\\/]\\.git[\\/]|\\.gitkeep$|\\.DS_Store$|~$|\\.tmp$|\\.bak$")

# 2. Collect all files in resources/
file(GLOB RESOURCE_FILES "${RESOURCES_DIR}/*")
list(FILTER RESOURCE_FILES EXCLUDE REGEX "\\.gitkeep$|\\.DS_Store$|~$")

# Debug output
list(LENGTH ASSET_FILES ASSET_COUNT)
list(LENGTH RESOURCE_FILES RES_COUNT)
message(STATUS "[Assets] Found ${ASSET_COUNT} game asset(s) in '${ASSETS_DIR}'")
message(STATUS "[Resources] Found ${RES_COUNT} bundle resource(s) in '${RESOURCES_DIR}'")

# ===================================================================
# APPLE (macOS + iOS): Embed everything into the .app bundle under Resources/
# ===================================================================
if(APPLE)
    macro(add_to_bundle input_file base_dir)
        file(RELATIVE_PATH rel_path "${base_dir}" "${input_file}")
        get_filename_component(rel_dir "${rel_path}" DIRECTORY)
        target_sources(${EXECUTABLE_NAME} PRIVATE "${input_file}")
        set_property(SOURCE "${input_file}" PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${rel_dir}")
    endmacro()

    foreach(file ${ASSET_FILES})
        add_to_bundle("${file}" "${ASSETS_DIR}")
    endforeach()
    foreach(file ${RESOURCE_FILES})
        add_to_bundle("${file}" "${RESOURCES_DIR}")
    endforeach()

# ===================================================================
# EMSCRIPTEN (Web): Preload both assets/ and resources/ with correct paths
# ===================================================================
elseif(EMSCRIPTEN)
    foreach(file ${ASSET_FILES})
        file(RELATIVE_PATH rel "${ASSETS_DIR}" "${file}")
        list(APPEND EM_PRELOAD "--preload-file \"${file}@/assets/${rel}\"")
    endforeach()
    string(REPLACE ";" " " EM_PRELOAD_STR "${EM_PRELOAD}")
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${EM_PRELOAD_STR})

# ===================================================================
# ANDROID + DESKTOP (Windows/Linux): Copy both trees next to the executable
# ===================================================================
else()
    if(ANDROID)
        if(NOT MOBILE_ASSETS_DIR)
            message(FATAL_ERROR "Building for Android, but MOBILE_ASSETS_DIR is not set")
        endif()
        file(MAKE_DIRECTORY "${MOBILE_ASSETS_DIR}")
    endif()

    macro(copy_tree file_list base_dir prefix)
        foreach(file ${file_list})
            file(RELATIVE_PATH rel "${base_dir}" "${file}")
            get_filename_component(rel_dir "${rel}" DIRECTORY)
            if(ANDROID)
                set(dest "${MOBILE_ASSETS_DIR}/${prefix}/${rel}")
            else()
                set(dest "${DIST_DIR}/${prefix}/${rel}")
            endif()
            get_filename_component(dest_dir "${dest}" DIRECTORY)
            add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "${dest_dir}"
            )
            add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${file}" "${dest}"
                COMMENT "Copying ${prefix}: ${rel}"
            )
        endforeach()
    endmacro()

    # Copy game assets
    copy_tree("${ASSET_FILES}" "${ASSETS_DIR}" "assets")
    if(APPLE)
        # Copy bundle resources (logo, storyboard, etc.)
        copy_tree("${RESOURCE_FILES}" "${RESOURCES_DIR}" "resources")
    endif()
endif()

# ===================================================================
# APPLE BUNDLE SETTINGS – Auto-include logo.png, storyboard, Info.plist
# ===================================================================
if(APPLE)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST "${RESOURCES_DIR}/Info.plist.in"
        XCODE_GENERATE_SCHEME TRUE
        XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER "com.elefantblasterclient.vn"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.elefantblasterclient.vn"
        XCODE_ATTRIBUTE_CURRENTYEAR "2025"
        RESOURCE "${RESOURCE_FILES}"
    )
endif()

# Visual Studio: set as startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${EXECUTABLE_NAME}")

# ===================================================================
# macOS: Create draggable .app with proper dependency fixup
# ===================================================================
if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    install(TARGETS ${EXECUTABLE_NAME}
        BUNDLE DESTINATION ./install COMPONENT Runtime
        RUNTIME DESTINATION ./install/bin COMPONENT Runtime
    )
    install(CODE "
        include(BundleUtilities)
        fixup_bundle(\"$<TARGET_BUNDLE_DIR:${EXECUTABLE_NAME}>\" \"\" \"${CMAKE_BINARY_DIR}\")
    ")
    set(CPACK_GENERATOR "DragNDrop")
    include(CPack)
endif()
