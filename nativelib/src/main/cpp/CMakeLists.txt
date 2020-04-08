
cmake_minimum_required(VERSION 3.4.1)

#set(var 123)
#message(WARNING "var ")

add_library(  
             test-lib
             SHARED
             test.cpp )

find_library(
              log-lib
              log )


target_link_libraries(
                        test-lib
                       ${log-lib} )