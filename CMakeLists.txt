cmake_minimum_required(VERSION 3.10)

# Project name
project(JaggedLangProject)

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/JaggedDLL)

# Add the source files for the DLL
set(DLL_SOURCES
    ${PROJECT_SOURCE_DIR}/JaggedDLL/classes/ErrHandler.cpp
    ${PROJECT_SOURCE_DIR}/JaggedDLL/classes/tokenizer.cpp
)

# Add the DLL target
add_library(JaggedDLL SHARED ${DLL_SOURCES})

# Define the macro for the DLL build
target_compile_definitions(JaggedDLL PRIVATE BUILD_DLL)

# Add the source files for the executable
set(EXE_SOURCES
    ${PROJECT_SOURCE_DIR}/JaggedLang/main.cpp
)

# Add the executable target
add_executable(JaggedExe ${EXE_SOURCES})

# Link the executable with the DLL
target_link_libraries(JaggedExe PRIVATE JaggedDLL)
