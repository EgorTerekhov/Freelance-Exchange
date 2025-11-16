cmake_minimum_required(VERSION 3.10)
project(FreelanceExchange)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(freelance_exchange
  ./code/src/password.cpp
  ./code/src/main.cpp
  ./code/src/admin.cpp
  ./code/src/customer.cpp
  ./code/src/JsonClass.cpp
  ./code/src/database.cpp
  ./code/src/order.cpp
  ./code/src/performer.cpp
  ./code/src/review.cpp
  ./code/src/user.cpp
)

find_package(OpenSSL REQUIRED)

target_include_directories(freelance_exchange PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann
)

target_link_libraries(freelance_exchange OpenSSL::SSL OpenSSL::Crypto)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wconversion -Wsign-conversion")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wduplicated-branches -Wlogical-op")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference -Wuseless-cast -Wold-style-cast")
  
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fno-optimize-sibling-calls")
  
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -fsanitize=bounds-strict")
endif()