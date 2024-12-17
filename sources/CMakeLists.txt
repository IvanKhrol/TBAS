set(PROJECT_NAME TBAS)

if (${OS_TYPE} STREQUAL "UNKNOWN")
  message(FATAL_ERROR "Unknown type of OS")
else()
  if (${OS_TYPE} STREQUAL "WINDOWS")
    add_compile_options(
      "/O2"
      "/MD"
    )
  endif()

  if (${OS_TYPE} STREQUAL "LINUX")
    add_compile_options(
      "-Wall"
      "-Wextra"
      "-O2"
    )
  endif()
endif()

add_compile_definitions(VERSION_STR=\"${PROJECT_VERSION}\")
add_compile_definitions(APP_NAME=\"${PROJECT_NAME}\")
add_compile_definitions(PROJECT_ROOT_DIR=\"${PROJECT_ROOT_DIR}\")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT_DIR}/build)

set(RESOURCES
#   ${PROJECT_ROOT_DIR}/resources/texture.qrc
)

set(UI_HEADERS
  ${PROJECT_ROOT_DIR}/sources/${PROJECT_NAME}MainWindow/${PROJECT_NAME}MainWindow.ui
)

set(HEADERS
  ${PROJECT_ROOT_DIR}/sources/${PROJECT_NAME}MainWindow/${PROJECT_NAME}MainWindow.hpp

  ${PROJECT_ROOT_DIR}/sources/externals/ErrorMessageBox.hpp
)

set (SOURCES
  ${PROJECT_ROOT_DIR}/sources/${PROJECT_NAME}Main.cpp
  ${PROJECT_ROOT_DIR}/sources/${PROJECT_NAME}MainWindow/${PROJECT_NAME}MainWindow.cpp
)

message("Qt version is: " ${QT_VERSION})
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(${PROJECT_NAME} 
    MANUAL_FINALIZATION
    ${RESOURCES}
    ${SOURCES} 
    ${HEADERS} 
    ${UI_HEADERS}
  )
  if(${QT_VERSION_MINOR} GREATER_EQUAL 7)
    add_compile_definitions(QT_DEPRECATED_FEATURE_CHECK)
  endif()
else()
  add_executable(${PROJECT_NAME} 
    ${RESOURCES}
    ${SOURCES} 
    ${HEADERS} 
    ${UI_HEADERS}
  )
endif()

include_directories(
    ${PROJECT_ROOT_DIR}/sources/
    ${PROJECT_ROOT_DIR}/include/
)
if (${OS_TYPE} STREQUAL  "WINDOWS") 
  set (LIB
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Widgets 
    Qt${QT_VERSION_MAJOR}::Gui

    d3d11.lib
    d3d12.lib
    dxgi.lib
    dxguid.lib
    ucrt.lib
    msvcrt.lib

    user32.lib
    gdi32.lib
    shell32.lib
    ole32.lib
    uuid.lib
    advapi32.lib
    ws2_32.lib
    dwmapi.lib
    version.lib
    winmm.lib
    imm32.lib
  )
  target_link_options(${PROJECT_NAME} PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
else()
  set(LIB 
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Widgets 
    Qt${QT_VERSION_MAJOR}::Gui)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC  
  ${LIB}
)

