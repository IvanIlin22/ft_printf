cmake_minimum_required(VERSION 3.16)
project(pritnf)

set(CMAKE_CXX_STANDARD 14)

add_executable(pritnf main.cpp ft_printf.h parce_modifier.cpp print_decimal.cpp print_octal.cpp "print string.cpp" print_char.cpp)