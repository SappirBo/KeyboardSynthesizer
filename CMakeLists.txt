cmake_minimum_required(VERSION 3.12)
project(KeyboardSynthesizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find pkg-config
find_package(PkgConfig REQUIRED)

# Find PortAudio using pkg-config
pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)

# Verify that PortAudio was found
if(NOT PORTAUDIO_FOUND)
    message(FATAL_ERROR "PortAudio not found. Please install it using 'sudo apt-get install portaudio19-dev'.")
endif()

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PORTAUDIO_INCLUDE_DIRS}
)

# Source and header files
set(SOURCES
    main.cpp
    src/oscillator.cpp
    src/audio_player.cpp
    src/input_handler.cpp
    src/synthesizer.cpp
)

set(HEADERS
    include/oscillator.hpp
    include/wave_types.hpp
    include/audio_player.hpp
    include/input_handler.hpp
    include/pa_data.hpp
    include/audio_settings.hpp
    include/synth_engine.hpp
    include/synthesizer.hpp
    include/synth_state.hpp
    include/base_loop.hpp
    include/play_loop.hpp
)

# Add executable target
add_executable(KeyboardSynthesizer_exe ${SOURCES} ${HEADERS})

# Link PortAudio libraries
target_link_libraries(KeyboardSynthesizer_exe
    PRIVATE
        ${PORTAUDIO_LIBRARIES}
)

# Optionally, add any necessary compile flags
target_compile_options(KeyboardSynthesizer_exe
    PRIVATE
        ${PORTAUDIO_CFLAGS_OTHER}
)
