cmake_minimum_required(VERSION 3.4.1)
project(ioctrls)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

# === custom vars === #
set(PI_PATH /usr/local/include)

# === global === #
# add_compile_options()
include_directories(${WIRINGPI_INCLUDE_DIRS} ${PI_PATH})
# link_directories()
# link_libraries()

# === target === #
# gpio
add_executable(gpio src/pins.c src/test.c)
target_compile_options(gpio PUBLIC -g -Wall)
target_include_directories(gpio PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(gpio wiringPi wiringPiDev m pthread rt crypt)

# spi
add_executable(spi src/spi.c src/test.c)
target_compile_options(spi PUBLIC -g -Wall)
target_include_directories(spi PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(spi wiringPi wiringPiDev m pthread rt crypt)

# === install === #
install(TARGETS gpio DESTINATION ./)
install(TARGETS spi DESTINATION ./)
