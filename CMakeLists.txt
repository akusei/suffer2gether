cmake_minimum_required(VERSION 4.3.3)

set(PROJECT_NAME "suffer2gether")

file(READ "version.txt" version_data)

string(REGEX MATCH "VERSION_MAJOR ([0-9]+)" _ "${version_data}")
set(VERSION_MAJOR "${CMAKE_MATCH_1}")

string(REGEX MATCH "VERSION_MINOR ([0-9]+)" _ "${version_data}")
set(VERSION_MINOR "${CMAKE_MATCH_1}")

string(REGEX MATCH "VERSION_PATCH ([0-9]+)" _ "${version_data}")
set(VERSION_PATCH "${CMAKE_MATCH_1}")


project(
  ${PROJECT_NAME}
  VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"
)


if(WIN32)
    configure_file(
        "src/apps/windows/res/version.rc.in"
        "${CMAKE_BINARY_DIR}/generated/version.rc"
        @ONLY
    )

    configure_file(
        "src/apps/windows/res/cli.rc.in"
        "${CMAKE_BINARY_DIR}/generated/cli.rc"
        @ONLY
    )

    configure_file(
        "src/apps/windows/res/suffer2gether.rc.in"
        "${CMAKE_BINARY_DIR}/generated/suffer2gether.rc"
        @ONLY
    )

    add_library(ufmod_lib STATIC IMPORTED)

    set_target_properties(
        ufmod_lib
        PROPERTIES IMPORTED_LOCATION
          "${CMAKE_SOURCE_DIR}/extern/ufmod.lib"
    )

    add_executable(${PROJECT_NAME} WIN32)
    set_target_properties(
      ${PROJECT_NAME}
      PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
        USE_MFC TRUE
        CXX_STANDARD 26
    )

    set_property(
      TARGET ${PROJECT_NAME}
      PROPERTY 
        USE_MFC TRUE
    )

    target_link_libraries(
      ${PROJECT_NAME}
      PRIVATE
        ufmod_lib
        winmm
    )

    target_include_directories(
      ${PROJECT_NAME}
      PRIVATE
        "extern"
        "src/core"
        "src/platform/windows"
        "src/apps/windows"
    )

    target_sources(
      ${PROJECT_NAME}
      PRIVATE
        "src/apps/windows/CApp.cpp"
        "src/apps/windows/CCustomButton.cpp"
        "src/apps/windows/CMainWindow.cpp"
        "src/apps/windows/CScreen.cpp"
        "src/platform/windows/GameLocator.cpp"
        "src/core/CPatcher.cpp"
        "${CMAKE_BINARY_DIR}/generated/suffer2gether.rc"
        "${CMAKE_BINARY_DIR}/generated/version.rc"
      )

    add_executable(${PROJECT_NAME}-cli)
    set_target_properties(
      ${PROJECT_NAME}-cli
      PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
        USE_MFC FALSE
        CXX_STANDARD 26
    )

    target_include_directories(
        ${PROJECT_NAME}-cli
        PRIVATE
          "src/core"
          "src/platform/windows"
          "src/apps/windows"
          "src/apps/cli"
    )

    target_link_options(${PROJECT_NAME}-cli PRIVATE -static)

    target_sources(
        ${PROJECT_NAME}-cli
        PRIVATE
          "src/apps/cli/main.cpp"
          "src/core/CPatcher.cpp"
          "src/platform/windows/GameLocator.cpp"
          "${CMAKE_BINARY_DIR}/generated/version.rc"
          "${CMAKE_BINARY_DIR}/generated/cli.rc"
    )
elseif(UNIX)
    add_executable(${PROJECT_NAME})

    target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
          "src/core"
          "src/platform/linux"
          "src/apps/cli"
    )

    target_sources(
        ${PROJECT_NAME}
        PRIVATE
          "src/apps/cli/main.cpp"
          "src/core/CPatcher.cpp"
          "src/platform/linux/GameLocator.cpp"
    )
endif()