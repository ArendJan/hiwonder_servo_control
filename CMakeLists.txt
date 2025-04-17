cmake_minimum_required(VERSION 3.10) 

project(HiWonder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_executable(${PROJECT_NAME} main.cpp HW.cpp)
add_executable(set_id set_id.cpp HW.cpp)
add_executable(set_angle set_angle.cpp HW.cpp)

add_executable(get_id get_id.cpp HW.cpp)
add_executable(discover_ids discover_ids.cpp HW.cpp)
add_executable(get_angle get_angle.cpp HW.cpp)
add_executable(set_volt set_volt.cpp HW.cpp)
add_executable(set_range set_range.cpp HW.cpp)
add_executable(set_mirte_master_arm set_mirte_master_arm.cpp HW.cpp)