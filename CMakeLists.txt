cmake_minimum_required(VERSION 4.3.3)

set(PROJECT_NAME "suffer2gether")
project(${PROJECT_NAME})


if(WIN32)
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
        "src/apps/windows/res/suffer2gether.rc"
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
          "src/apps/windows/res/cli.rc"
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