cmake_minimum_required(VERSION 3.18)

# set the project name
project(Rhythm_Tool)

# set path to findSFML.cmake file
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

# find SFML components
find_package(SFML 2.4 COMPONENTS graphics window system audio REQUIRED)

# list .cpp files
set(SOURCES)

# add sub directories
add_subdirectory(Base)
add_subdirectory(BPMScene)

# EXAMPLE: CMakeList.txt in sub directory
# set(SOURCES
# ${SOURCES}
# ${Game_SOURCE_DIR}/FolderName/FileName.cpp
# PARENT_SCOPE
# )

# add the executable
add_executable(Rhythm_Tool ${SOURCES})

# link sub directories
target_link_directories(Rhythm_Tool PUBLIC "${Game_SOURCE_DIR}/Base")
target_link_directories(Rhythm_Tool PUBLIC "${Game_SOURCE_DIR}/BPMScene")

# link SFML libraries
target_link_libraries(Rhythm_Tool sfml-graphics sfml-window sfml-system sfml-audio)