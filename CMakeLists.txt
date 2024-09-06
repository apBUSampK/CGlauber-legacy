cmake_minimum_required(VERSION 3.22)
project(CGlauber VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(COLA REQUIRED)
find_package(ROOT REQUIRED)

include(CMakePackageConfigHelpers)

set(CMAKE_INSTALL_PREFIX ${COLA_DIR})
set(COLA_MODULE_NAME CGlauber)

# Add library target
set(srcs src/CGlauberFactory.cc src/CGlauberGenerator.cc src/TGlauNucleon.cc src/TGlauNucleus.cc src/TGlauberMC.cc)
add_library(CGlauber SHARED ${srcs})

target_include_directories(CGlauber PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${COLA_MODULE_NAME}>)

target_link_libraries(CGlauber PUBLIC COLA ROOT::RIO ROOT::MathMore ${ROOT_LIBRARIES})

set_target_properties(CGlauber PROPERTIES PUBLIC_HEADER include/CGlauber.hh)

# Add installation path for library to find .dat files:
add_compile_definitions(DATA_INSTALL="${CMAKE_INSTALL_PREFIX}/data/${COLA_MODULE_NAME}/")

# Configure config files
configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/data/CGlauberConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/CGlauberConfig.cmake"
        INSTALL_DESTINATION lib/cmake/${COLA_MODULE_NAME}
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/CGlauberConfigVersion.cmake
        COMPATIBILITY AnyNewerVersion)

# Install library
install(TARGETS CGlauber
        EXPORT CGlauberExport
        LIBRARY DESTINATION lib/${COLA_MODULE_NAME}
        PUBLIC_HEADER DESTINATION include/${COLA_MODULE_NAME}
        INCLUDES DESTINATION include/${COLA_MODULE_NAME})

# Install includes
install(DIRECTORY include/
        DESTINATION include/${COLA_MODULE_NAME})

# Install export file and config files
install(EXPORT CGlauberExport
        DESTINATION lib/cmake/${COLA_MODULE_NAME})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/CGlauberConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/CGlauberConfigVersion.cmake"
        DESTINATION lib/cmake/${COLA_MODULE_NAME})

#install .dat files for proper TGlauber generation
install(FILES ${PROJECT_SOURCE_DIR}/data/ca40_alv.dat
        ${PROJECT_SOURCE_DIR}/data/carbon_plaintext.dat
        ${PROJECT_SOURCE_DIR}/data/h3_plaintext.dat
        ${PROJECT_SOURCE_DIR}/data/he3_plaintext.dat
        ${PROJECT_SOURCE_DIR}/data/he4_plaintext.dat
        ${PROJECT_SOURCE_DIR}/data/o16_alv.dat
        ${PROJECT_SOURCE_DIR}/data/oxygen_plaintext.dat
        DESTINATION data/${COLA_MODULE_NAME})