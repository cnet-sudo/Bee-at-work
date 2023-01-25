cmake_minimum_required(VERSION 3.21)
project(Bee_at_work VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_executable(Bee_at_work main.cpp GameMenu.cpp GameMenu.h AssetManager.cpp AssetManager.h 
Animator.cpp Animator.h Engine.cpp Engine.h HealthBarClass.cpp HealthBarClass.h GameSound.cpp GameSound.h
Player.cpp Player.h)

add_custom_command(TARGET Bee_at_work POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/sound
                        $<TARGET_FILE_DIR:Bee_at_work>/sound
                   VERBATIM)
add_custom_command(TARGET Bee_at_work POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/font
                        $<TARGET_FILE_DIR:Bee_at_work>/font
                   VERBATIM)
add_custom_command(TARGET Bee_at_work POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/image
                        $<TARGET_FILE_DIR:Bee_at_work>/image
                   VERBATIM)
				   
add_custom_command(
  TARGET Bee_at_work POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
    ${PROJECT_SOURCE_DIR}/openal32.dll
    $<TARGET_FILE_DIR:Bee_at_work>/openal32.dll)

target_link_libraries(Bee_at_work PRIVATE sfml-graphics sfml-system sfml-window sfml-audio )

target_compile_features(Bee_at_work PRIVATE cxx_std_20)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Bee_at_work POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Bee_at_work> $<TARGET_FILE_DIR:Bee_at_work> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Bee_at_work)

# Директория с СMakeLists.txt
# cmake -S . -B build
# cmake --build build --config Release
# cmake --build build --config Debug
# Для запуска проекта выбрать активный проект