cmake_minimum_required(VERSION 3.15)
project(OCTAVIAN)

# Enable folder grouping in IDEs like Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add subdirectories for each project
add_subdirectory(Core)
add_subdirectory(Game)
add_subdirectory(Renderer)

