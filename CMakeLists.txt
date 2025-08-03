cmake_minimum_required(VERSION 3.18)
project(flowequations VERSION 1.0.0 LANGUAGES CXX CUDA)

# Options
option(BUILD_TESTING "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" OFF)
option(FLOWEQUATIONS_USE_SYSTEM_JSON "Use system-installed nlohmann_json" OFF)

# C++ and CUDA standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Enhanced devdat finding
message(STATUS "Looking for devdat dependency...")
if(DEFINED DEVDAT_DIR)
    message(STATUS "Using provided DEVDAT_DIR: ${DEVDAT_DIR}")
    list(APPEND CMAKE_PREFIX_PATH ${DEVDAT_DIR})
endif()

# Try to find the devdat header explicitly - this helps with CUDA compilation
find_path(DEVDAT_INCLUDE_DIR "devdat/header.hpp"
    PATHS
        ${CMAKE_PREFIX_PATH}
        ${DEVDAT_DIR}
        ${CMAKE_INSTALL_PREFIX}
    PATH_SUFFIXES
        include
)

if(DEVDAT_INCLUDE_DIR)
    message(STATUS "Found devdat headers at: ${DEVDAT_INCLUDE_DIR}")
else()
    message(WARNING "devdat headers not found directly, will rely on find_package")
endif()

# Find the devdat package
find_package(devdat REQUIRED)
message(STATUS "Found devdat package: ${devdat_FOUND}")

# Handle nlohmann_json dependency
if(FLOWEQUATIONS_USE_SYSTEM_JSON OR DEFINED USE_SYSTEM_JSON)
    if(DEFINED JSON_INCLUDE_DIR)
        message(STATUS "Using provided JSON_INCLUDE_DIR: ${JSON_INCLUDE_DIR}")
        add_library(flowequations_json_wrapper INTERFACE)
        target_include_directories(flowequations_json_wrapper INTERFACE 
            $<BUILD_INTERFACE:${JSON_INCLUDE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )
        set(JSON_TARGET flowequations_json_wrapper)
        set(EXPORT_JSON_TARGET TRUE)
    else()
        message(STATUS "Using system nlohmann_json package")
        find_package(nlohmann_json REQUIRED)
        set(JSON_TARGET nlohmann_json::nlohmann_json)
        set(EXPORT_JSON_TARGET FALSE)
    endif()
else()
    message(STATUS "Fetching nlohmann_json")
    include(FetchContent)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
    )
    FetchContent_MakeAvailable(nlohmann_json)
    set(JSON_TARGET nlohmann_json::nlohmann_json)
    set(EXPORT_JSON_TARGET FALSE)
    
    # Install the headers if we fetched them
    install(
        DIRECTORY ${nlohmann_json_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()

# Define the library
add_library(flowequations
    src/flow_equation.cu
    src/jacobian_equation.cu
    # Add other source files as needed
)

# Create an alias target
add_library(${PROJECT_NAME}::flowequations ALIAS flowequations)

# Set CUDA compile options - add explicit include paths for devdat for CUDA
target_compile_options(flowequations PRIVATE 
    $<$<COMPILE_LANGUAGE:CUDA>:
        --expt-extended-lambda
        --expt-relaxed-constexpr
        $<$<BOOL:${DEVDAT_INCLUDE_DIR}>:-I${DEVDAT_INCLUDE_DIR}>
    >
)

# Include directories - crucial for correct CUDA compilation
target_include_directories(flowequations
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        # Explicitly add devdat includes - both from found path and from package
        $<$<BOOL:${DEVDAT_INCLUDE_DIR}>:${DEVDAT_INCLUDE_DIR}>
        $<$<BOOL:${devdat_INCLUDE_DIRS}>:${devdat_INCLUDE_DIRS}>
)

# Link dependencies
target_link_libraries(flowequations
    PUBLIC
        ${JSON_TARGET}
        devdat::devdat
)

# Installation
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

# Install headers
install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install targets
if(EXPORT_JSON_TARGET)
    install(
        TARGETS flowequations flowequations_json_wrapper
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
else()
    install(
        TARGETS flowequations
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()

# Export targets
install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Create package config files
include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/flowequationsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install config files
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Build tests if enabled
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# Build examples if enabled
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()