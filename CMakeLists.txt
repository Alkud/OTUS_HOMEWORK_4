#CmakeList.txt for OTUS Homework #2

#Check CMake version
cmake_minimum_required(VERSION 3.2)

#Set project name, set PROJECT_VERSION_MINOR value equal to TRAVIS_BUILD NUMBER
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set (VERSION_PATCH $ENV{TRAVIS_BUILD_NUMBER})
else ()
  set (VERSION_PATCH 1)
endif()

project(print_ip VERSION 0.0.${VERSION_PATCH})

set (BOOST_MIN_VERSION "1.54.0")

#Find Boost UTF component, get BOOST_LIBRARIES and BOOST_INCLUDE_DIR values
find_package(Boost COMPONENTS unit_test_framework REQUIRED)


#Set library target
add_library(is_suitable_container INTERFACE)
target_sources(is_suitable_container INTERFACE ${PROJECT_SOURCE_DIR}/is_suitable_container.h)
target_include_directories(is_suitable_container INTERFACE ${PROJECT_SOURCE_DIR})

add_library(spdlog INTERFACE)
target_sources(spdlog INTERFACE /usr/include/spdlog/spdlog.h)
target_include_directories(spdlog INTERFACE /usr/include/spdlog)

add_library(process process.cpp)

#Set executable target
set(HEADERS ${PROJECT_SOURCE_DIR}/is_suitable_container.h)
add_executable(print_ip print_ip.cpp ${HEADERS})


#Set test target_link_libraries
add_executable(otus_hw_4_test otus_hw_4_test.cpp)

#Enable tests
enable_testing()
add_test(
NAME test_hw_4
COMMAND otus_hw_4_test)

#Set properties and compile options for executable target
set_target_properties(print_ip
  PROPERTIES CXX_STANDARD 14
             CXX_STANDARD_REQUIRED ON
             COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

#Set properties for test target
set_target_properties(otus_hw_4_test PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

#Link
target_link_libraries(print_ip process)
target_link_libraries(process INTERFACE is_suitable_container)
target_link_libraries(otus_hw_4_test
  ${Boost_LIBRARIES}
  process
)

install(TARGETS print_ip RUNTIME DESTINATION bin)

message("${PROJECT_NAME} build ${PROJECT_VERSION}")

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexandr_kudinov@mail.ru)

include(CPack)
