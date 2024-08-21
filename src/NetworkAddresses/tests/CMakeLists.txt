###############################################################################
###                                  TESTS                                  ###
###############################################################################
## Settings and steps to build the component tests.
###############################################################################

# Set the name of the component library.
set (COMPONENT_TESTS ${COMPONENT}_tests)

# Set the name of the component library.
set (COMPONENT_TESTS_LIB ${COMPONENT_TESTS}_lib)


###############################################################################
###                              TESTS LIBRARY                              ###
###############################################################################
## Library containing the test classes.
###############################################################################

# Create an library for tests related to the component.
add_library (
  ${COMPONENT_TESTS_LIB}
)

# Set the lib linker
set_target_properties (
  ${COMPONENT_TESTS_LIB}
    PROPERTIES
      LINKER_LANGUAGE CXX
)

# Include directories for the library.
target_include_directories (
  ${COMPONENT_TESTS_LIB}
    PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/include
)

# Gather source files for the component library.
file (
  GLOB SOURCES
    CONFIGURE_DEPENDS
      "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

# Add the collected source files to the library.
target_sources (
  ${COMPONENT_TESTS_LIB}
    PRIVATE
      ${SOURCES}
)

# Link the needed libraries.
target_link_libraries (
  ${COMPONENT_TESTS_LIB}
    ${COMPONENT_LIB}
    GTest::GTest
    GTest::Main
)


###############################################################################
###                            TESTS EXECUTABLES                            ###
###############################################################################
## Executables containing the tests.
###############################################################################

# Create an executable for tests related to the component.
add_executable (
  ${COMPONENT_TESTS}
)

# Gather source files for the component tests.
file (
  GLOB SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
)

# Add the collected source files to the tests executable.
target_sources (
  ${COMPONENT_TESTS}
    PRIVATE
      ${SOURCES}
)

# Link the necessary libraries for the tests.
target_link_libraries (
  ${COMPONENT_TESTS}
    ${COMPONENT_TESTS_LIB}
    GTest::GTest
    GTest::Main
)

# Register the tests with CTest.
add_test (
  ${COMPONENT_TESTS}
    ${COMPONENT_TESTS}
)