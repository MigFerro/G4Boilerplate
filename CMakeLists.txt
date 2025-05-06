#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.16...3.27)
project(project-name)

# for lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# See the documentation for a guide on how to enable/disable specific components
#
find_package(Geant4 REQUIRED ui_all vis_all)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB macros "macros/*.mac")

#----------------------------------------------------------------------------
# Add the executable, use our local headers, and link it to the Geant4 libraries
#
add_executable(sim sim.cc ${sources} ${headers})
target_include_directories(sim PUBLIC include)
target_link_libraries(sim PUBLIC ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory
#

file(COPY ${macros} DESTINATION ${PROJECT_BINARY_DIR}/macros)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/out)

add_custom_target(clean-root COMMAND ${CMAKE_COMMAND} -E remove ./out/*.root)
