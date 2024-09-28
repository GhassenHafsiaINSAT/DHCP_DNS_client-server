cmake_minimum_required(VERSION 3.10)

project(my_project VERSION 1.0
                           DESCRIPTION "This is a DHCP and DNS Server"
                           LANGUAGES CXX)


add_library(common STATIC ${CMAKE_SOURCE_DIR}/src/checkout_ip.c
                          ${CMAKE_SOURCE_DIR}/src/init_pool.c 
                          ${CMAKE_SOURCE_DIR}/src/int_to_ip.c 
                          ${CMAKE_SOURCE_DIR}/src/ip_to_int.c 
                          ${CMAKE_SOURCE_DIR}/src/readline.c 
                          ${CMAKE_SOURCE_DIR}/src/readn.c 
                          ${CMAKE_SOURCE_DIR}/src/release_ip.c 
                          ${CMAKE_SOURCE_DIR}/src/str_cli.c 
                          ${CMAKE_SOURCE_DIR}/src/str_echo.c 
                          ${CMAKE_SOURCE_DIR}/src/writen.c)

#include directory for header files 
target_include_directories(common PUBLIC ${CMAKE_SOURCE_DIR}/include/)


add_executable(client src/client.c)
add_executable(server src/server.c)

#link the common library to both executables 
target_link_libraries(client common)
target_link_libraries(server common)


