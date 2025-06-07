cmake_minimum_required(VERSION 3.20)

project(application LANGUAGES C CXX)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.h" "src/*.c" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_options(${PROJECT_NAME} PRIVATE -sALLOW_MEMORY_GROWTH -sFETCH)
target_link_libraries(${PROJECT_NAME} PRIVATE -lembind)

include(FetchContent)

set(LV_BUILD_CONF_DIR "src" CACHE PATH "The directory containing lv_conf.h")

FetchContent_Declare(
  lvgl
  GIT_REPOSITORY https://github.com/lvgl/lvgl.git
  GIT_TAG tags/v9.3.0
)
FetchContent_MakeAvailable(lvgl)

target_link_libraries(${PROJECT_NAME} PRIVATE lvgl::lvgl lvgl::thorvg)