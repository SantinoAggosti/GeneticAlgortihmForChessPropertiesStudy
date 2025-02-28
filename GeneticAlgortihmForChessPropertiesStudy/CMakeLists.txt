# CMakeList.txt : CMake project for GeneticAlgortihmForChessPropertiesStudy, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GeneticAlgortihmForChessPropertiesStudy   "main.cpp" "position.cpp" "position.h" "operations.cpp" "operations.h" "thc.cpp" "statistics.h" "statistics.cpp" "plottingTools.cpp" "plottingTools.h")
add_subdirectory(matplotplusplus)
target_link_libraries(GeneticAlgortihmForChessPropertiesStudy PUBLIC matplot)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GeneticAlgortihmForChessPropertiesStudy PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
