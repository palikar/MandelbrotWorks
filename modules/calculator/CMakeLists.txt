cmake_minimum_required(VERSION 3.4)


project(Calucalor_Module VERSION 0.0.0 LANGUAGES CXX)


#for adding an executable
add_executable(calculator src/main.cpp src/mandelbrot_works.cpp)
#for addding an library
#add_library(lib SHARED|STATIC)


target_include_directories(calculator PUBLIC include)
#target_sources(exe|lib PUBLIC|PRIVATE ./src)

find_package( OpenCV REQUIRED )
target_link_libraries( calculator PUBLIC ${OpenCV_LIBS} )
include_directories( ${OpenCV_INCLUDE_DIRS} )
message(${OpenCV_LIBS})

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

install(TARGETS calculator DESTINATION bin)


#target_link_libraries(exe|lib PUBLIC|PRIVATE other_target)

#target_compile_definitions(exe|lib DEF)
#target_compile_options(exe|lib OPT)
#target_compile_features(exe|lig FEAT)


target_compile_options(calculator 
		#PRIVATE "-O3" 
		PRIVATE "-std=c++14"
		)

#target_compile_options(exe )
