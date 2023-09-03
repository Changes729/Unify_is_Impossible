set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test)

set(SPIKE_DIR ../shared)

message("INCLUDE:" ${UNIFY_IS_IMPOSSIBLE_INCLUDE})
include_directories(${UNIFY_IS_IMPOSSIBLE_INCLUDE})

include_directories(.)
include_directories(${SPIKE_DIR})
include_directories(${SPIKE_DIR}/shared/lib)

file(GLOB UI_EXAMPLE_C "./ui-example/*.c" "./ui-example/*.cpp")
file(GLOB EXAMPLES_C "./example/*.c" "./example/*.cpp")

foreach(EXAMPLE_FILE ${EXAMPLES_C})
	get_filename_component(EXAMPLE ${EXAMPLE_FILE} NAME_WE)
	set (SOURCE_FILES ${EXAMPLE_FILE})
	add_executable(${EXAMPLE} "test-entry.cpp" ${SOURCE_FILES})
  target_link_libraries(${EXAMPLE} gtest)
endforeach(EXAMPLE_FILE)

# find library #################################################################
include_directories(${GPIOD_INCLUDE_DIRS})
link_directories(${GPIOD_LIBRARY_DIRS})

find_package(SDL2)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories(${SDL2IMAGE_INCLUDE_DIRS})
link_directories(${SDL2IMAGE_LIBRARY_DIRS})

find_package(SDL2_ttf)
include_directories(${SDL2_TTF_INCLUDE_DIRS})
link_directories(${SDL2_TTF_LIBRARY_DIRS})

set(LIBSDL
  SDL2
  SDL2_image
  SDL2_ttf
  SDL2_mixer
)

set(LIBAV
    avdevice
    avfilter
    avformat
    avcodec
    swresample
    swscale
    avutil
)

foreach(EXAMPLE_FILE ${UI_EXAMPLE_C})
	get_filename_component(EXAMPLE ${EXAMPLE_FILE} NAME_WE)
	set (SOURCE_FILES ${EXAMPLE_FILE})
	add_executable(${EXAMPLE} ${SOURCE_FILES})
  target_link_libraries(${EXAMPLE} UiI ${LIBSDL} ${LIBAV})
endforeach(EXAMPLE_FILE)