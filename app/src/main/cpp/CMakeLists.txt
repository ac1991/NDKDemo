
cmake_minimum_required(VERSION 3.4.1)

#set(var 123)
#message(WARNING "var ")

add_library(  
             native-lib
             SHARED
             native-lib.cpp )

#将native-lib关联到第三方头文件，private作为分隔符，第三个参数是第三方头文件的路径
target_include_directories(native-lib
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/main/cpp/include)

#导入第三方库
#第一个参数为第三方库名称
#第二个参数为指明库为动态库
#第三个参数指明导入到库
add_library(test-lib SHARED IMPORTED)
#第一个参数为库名称
#第二个参数指明配置导入第三方so库路径
#第三个参数表示具体第三方库的路径
set_target_properties(test-lib
        PROPERTIES IMPORTED_LOCATION
        F:/project/NDKDemo/app/libs/${ANDROID_ABI}/libtest-lib.so)

find_library(
              log-lib
              log )


#第一个参数为当前库名称，后面是可变长的参数都是指明导入库或者依赖库的库名
target_link_libraries(
                       native-lib

                        test-lib

                       ${log-lib} )