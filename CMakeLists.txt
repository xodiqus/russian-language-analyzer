cmake_minimum_required(VERSION 3.0)

project ("russian-language-analyzer" VERSION 0.0.1 
                                     LANGUAGES CXX)

set(FILES   "src/foo.cpp" "include/foo.hpp"
            ""            ""
            )

set(TESTS   "test/foo.cpp"
            ""
            )

add_executable(${PROJECT_NAME} "src/main.cpp" ${FILES})

target_include_directories(${PROJECT_NAME} PRIVATE "include")

set(BOOST_ROOT "C:/Boost")
set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable("${PROJECT_NAME}_test" "test/module.hpp" "test/main.cpp" ${FILES} ${TESTS})
 
target_link_libraries("${PROJECT_NAME}_test" Boost::unit_test_framework)
target_include_directories("${PROJECT_NAME}_test" PRIVATE "include/" ${Boost_INCLUDEDIR})

set_target_properties(${PROJECT_NAME} "${PROJECT_NAME}_test" PROPERTIES
                        CXX_STANDARD 17
                        CXX_STANDARD_REQUIRED ON)