cmake_minimum_required (VERSION 3.20)

project (ascll_graphic)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE "src/run_config.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp) 
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${CURSES_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${CURSES_CFLAGS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})

add_subdirectory("src/render")
add_subdirectory("src/scene")
add_subdirectory("src/linear_field_operations")
install(TARGETS ${PROJECT_NAME})