###############################################################################
###                      INTEGRATE EXTERNAL LIBRARIES                       ###
###############################################################################
## Integrate GTest for unit testing.
###############################################################################

include (FetchContent)

FetchContent_Declare (
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)

# Download and configure Google Test as part of the build
find_package (GTest QUIET)  # Quiet to avoid errors if not found
if (NOT GTest_FOUND)
    FetchContent_MakeAvailable(googletest)
    add_library(GTest::GTest ALIAS gtest)
    add_library(GTest::Main ALIAS gtest_main)
endif()



###############################################################################
###                               COMPONENTS                                ###
###############################################################################
## Include project components and subdirectories.
###############################################################################

# Get a list of subdirectories in the current directory
set (
  COMPONENTS_SET
    NetworkAddresses
    NetworkSockets
)

# Iterate over each subdirectory
foreach (COMPONENT ${COMPONENTS_SET})
  # Set the name of the component library.
  set (COMPONENT_LIB ${COMPONENT}_lib)
  # Enter into the component
  add_subdirectory (${COMPONENT})
  # Link the new lib to the executable
  target_link_libraries (
    ${PROJECT_NAME}
      ${COMPONENT_LIB}
  )
endforeach()