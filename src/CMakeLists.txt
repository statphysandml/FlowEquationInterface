add_library(flowequations flowequations.cpp)
target_include_directories(flowequations PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
