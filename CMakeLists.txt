cmake_minimum_required(VERSION 3.16)
project(PostmanSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

include_directories(src/public)
file(GLOB_RECURSE SOURCES "src/private/*.cpp")

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# TODO: Unit tests

# Copy font to output directory
if(EXISTS ${CMAKE_SOURCE_DIR}/Arimo-Regular.ttf)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/Arimo-Regular.ttf
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/Arimo-Regular.ttf
        COMMENT "Copying font file to output directory"
    )
endif()

# For Windows, copy SFML DLLs
if(WIN32 AND TARGET sfml-graphics)
    get_target_property(SFML_GRAPHICS_LOCATION_RELEASE sfml-graphics IMPORTED_LOCATION_RELEASE)

    if(SFML_GRAPHICS_LOCATION_RELEASE)
        get_filename_component(SFML_DIR ${SFML_GRAPHICS_LOCATION_RELEASE} DIRECTORY)

        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<IF:$<CONFIG:Debug>,${SFML_DIR}/sfml-graphics-d-2.dll,${SFML_DIR}/sfml-graphics-2.dll>"
                "$<IF:$<CONFIG:Debug>,${SFML_DIR}/sfml-window-d-2.dll,${SFML_DIR}/sfml-window-2.dll>"
                "$<IF:$<CONFIG:Debug>,${SFML_DIR}/sfml-system-d-2.dll,${SFML_DIR}/sfml-system-2.dll>"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
endif()

message(STATUS "${PROJECT_NAME} | C++${CMAKE_CXX_STANDARD}")