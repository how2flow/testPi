cmake_minimum_required(VERSION 3.4.1)
project(ioctrls)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# === custom vars === #
set(LINKS wiringPi wiringPiDev m pthread rt crypt)
set(PI_PATH /usr/local/include)
set(UTILS src/test.c src/utils/thread.c)

# === custom functions === #
function(regist arg)
  set(SRCS src/ioctl/${arg}.c ${UTILS})
  add_executable(${arg} ${SRCS})
  target_compile_options(${arg} PUBLIC -g -Wall)
  target_include_directories(${arg} PUBLIC ${CMAKE_SOURCE_DIR}/include)
  target_link_libraries(${arg} ${LINKS})
  install(TARGETS ${arg} DESTINATION ./bin)
endfunction()

# === global === #
# add_compile_options()
include_directories(${WIRINGPI_INCLUDE_DIRS} ${PI_PATH})
# link_directories()
# link_libraries()

# === regist programs === #
regist(i2c)
regist(gpio)
regist(uart)
regist(spi)
