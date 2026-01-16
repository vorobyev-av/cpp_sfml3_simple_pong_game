cmake_minimum_required(VERSION 3.12)
project(simple_pong_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/SFML-3.0.2/lib/cmake/SFML")
set(SFML_ROOT "C:/SFML-3.0.2")

find_package(SFML 3 COMPONENTS Audio Graphics Main Network System Window REQUIRED)

add_executable(run src/main.cpp src/Bat.cpp src/Ball.cpp src/Bat.h src/Ball.h) 
target_link_libraries(run PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio 
    SFML::Network
)

if(WIN32)
    add_custom_command(TARGET run POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-audio-3.dll"
            $<TARGET_FILE_DIR:run>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-graphics-3.dll"
            $<TARGET_FILE_DIR:run>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-network-3.dll"
            $<TARGET_FILE_DIR:run>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-system-3.dll"
            $<TARGET_FILE_DIR:run>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-window-3.dll"
            $<TARGET_FILE_DIR:run>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-audio-d-3.dll"
            $<TARGET_FILE_DIR:run>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-graphics-d-3.dll"
            $<TARGET_FILE_DIR:run>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-network-d-3.dll"
            $<TARGET_FILE_DIR:run>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-system-d-3.dll"
            $<TARGET_FILE_DIR:run>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_ROOT}/bin/sfml-window-d-3.dll"
            $<TARGET_FILE_DIR:run>
        COMMENT "Copying SFML DLLs to build directory"
    )
endif()