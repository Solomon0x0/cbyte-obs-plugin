cmake_minimum_required(VERSION 3.28...3.30)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)

project("cbyte-obs-plugin" VERSION 0.0.1)

option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" ON)
option(ENABLE_QT "Use Qt functionality" ON)

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "Limited configs" FORCE)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Default type" FORCE)
    endif()
endif()

include(compilerconfig)
include(defaults)
include(helpers)

add_library(${CMAKE_PROJECT_NAME} MODULE)

find_package(libobs REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs)

if(ENABLE_FRONTEND_API)
  find_package(obs-frontend-api REQUIRED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::obs-frontend-api)
endif()

if(ENABLE_QT)
  find_package(Qt6 COMPONENTS Widgets Core REQUIRED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
  
  target_compile_options(
    ${CMAKE_PROJECT_NAME}
    PRIVATE $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header -Wno-comma>
  )
  set_target_properties(
    ${CMAKE_PROJECT_NAME}
    PROPERTIES AUTOMOC ON AUTOUIC ON AUTORCC ON
  )
endif()

target_sources(${CMAKE_PROJECT_NAME} PRIVATE 
    src/plugin-main.cpp
    src/Plugin.cpp
    src/Plugin.hpp
)

set_target_properties_plugin(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "cbyte-obs-plugin")

if(MSVC)
    set(OBS_ROOT "C:/Program Files/obs-studio")
    set(OBS_BIN_DIR "${OBS_ROOT}/bin/64bit")
    set(OBS_EXE "${OBS_BIN_DIR}/obs64.exe")
    
    set(TARGET_PLUGIN_DIR "${OBS_ROOT}/obs-plugins/64bit")
    set(TARGET_DATA_DIR "${OBS_ROOT}/data/obs-plugins/${CMAKE_PROJECT_NAME}")

    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_COMMAND "${OBS_EXE}"
        VS_DEBUGGER_COMMAND_ARGUMENTS "--verbose --multi"
        VS_DEBUGGER_WORKING_DIRECTORY "${OBS_BIN_DIR}"
        VS_DEBUGGER_ENVIRONMENT "PATH=${OBS_BIN_DIR};%PATH%"
    )

    set(FILE_ACTION "$<$<CONFIG:RelWithDebInfo>:copy_if_different>$<$<NOT:$<CONFIG:RelWithDebInfo>>:echo>")
    
    set(DIR_ACTION "$<$<CONFIG:RelWithDebInfo>:copy_directory>$<$<NOT:$<CONFIG:RelWithDebInfo>>:echo>")

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E ${FILE_ACTION}
            "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>"
            "${TARGET_PLUGIN_DIR}/$<TARGET_FILE_NAME:${CMAKE_PROJECT_NAME}>"
        
        COMMAND ${CMAKE_COMMAND} -E ${FILE_ACTION}
            "$<TARGET_PDB_FILE:${CMAKE_PROJECT_NAME}>"
            "${TARGET_PLUGIN_DIR}/$<TARGET_PDB_FILE_NAME:${CMAKE_PROJECT_NAME}>"

        COMMAND ${CMAKE_COMMAND} -E ${DIR_ACTION}
            "${CMAKE_CURRENT_SOURCE_DIR}/data"
            "${TARGET_DATA_DIR}"

        COMMENT "Smart Deploy: DLLs to bin, Data to data/obs-plugins..."
        VERBATIM
    )
endif()