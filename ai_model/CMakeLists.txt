cmake_minimum_required(VERSION 3.10)

project(demo)
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/package")
#set(PACKVERSION 2.0.0.1)
######################################################################
#全局编译标志
######################################################################


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -g")

######################################################################
#全局链接和包含
######################################################################

link_directories(${PROJECT_SOURCE_DIR}/ai_model/)
find_package(Boost REQUIRED COMPONENTS filesystem log system)

######################################################################
#全局编译输出指定
######################################################################

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${BUILD_TYPE})

find_package(Boost COMPONENTS log system REQUIRED)

add_executable(demo demo.cpp)

target_include_directories(demo PRIVATE
        ${PROJECT_SOURCE_DIR}/ai_model
#        PRIVATE ${_gRPC_PROTO_GENS_DIR})
)
target_link_libraries(demo
                ${CMAKE_SOURCE_DIR}/libeval_core.so
		# ${CMAKE_SOURCE_DIR}/-ldl
		${CMAKE_SOURCE_DIR}/libMNN.so
        ${Boost_LIBRARIES})

target_include_directories(demo
        PRIVATE ${PROJECT_SOURCE_DIR}
        PRIVATE ${PROJECT_SOURCE_DIR})

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ DESTINATION bin)
install(DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ DESTINATION lib)
install(FILES ai_model/libeval_core.so DESTINATION lib)
install(FILES ai_model/libMNN.so DESTINATION lib)
install(DIRECTORY ai_model/models/online_v1.12.0.cn.native/ DESTINATION ./bin/res/cn/px-1.0)
install(DIRECTORY ai_model/models/online_v1.12.0.cn.native/ DESTINATION ./bin/res/en/px-1.0)

