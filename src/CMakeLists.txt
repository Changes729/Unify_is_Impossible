# Include .h ###################################################################
set( UiI_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/src/.
  ${CMAKE_SOURCE_DIR}/src/module
  ${CMAKE_SOURCE_DIR}/src/module/utils
  ${CMAKE_SOURCE_DIR}/src/module/types
  ${CMAKE_SOURCE_DIR}/src/module/types/NDEF
  ${CMAKE_SOURCE_DIR}/src/module/events
  ${CMAKE_SOURCE_DIR}/src/module/resource
  ${CMAKE_SOURCE_DIR}/src/module/resource/audio
  ${CMAKE_SOURCE_DIR}/src/module/resource/font
  ${CMAKE_SOURCE_DIR}/src/module/resource/video
  ${CMAKE_SOURCE_DIR}/src/module/resource/view
  ${CMAKE_SOURCE_DIR}/src/module/signal
  ${CMAKE_SOURCE_DIR}/src/module/task
  ${CMAKE_SOURCE_DIR}/src/module/template
  ${CMAKE_SOURCE_DIR}/src/module/driver/linux-common
  ${CMAKE_SOURCE_DIR}/src/module/driver
  ${CMAKE_SOURCE_DIR}/src/view
  ${CMAKE_SOURCE_DIR}/src/controller
  ${CMAKE_SOURCE_DIR}/src/controller/nfc
  ${CMAKE_CURRENT_BINARY_DIR}
)
include_directories(${UiI_INCLUDE_DIR})

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

# include .c/.cpp ##############################################################
file(GLOB EMBED_C
  "module/driver/linux-common/*.c"
  "module/driver/linux-common/*.cpp"
)

file(GLOB RENDER_C
  "module/driver/render/*.c"
  "module/driver/render/*.cpp"
  "module/driver/*.c"
  "module/driver/*.cpp"
)

file(GLOB MODULE_C
  "module/*.c"
  "module/*.cpp"
  "module/types/*.c"
  "module/types/*.cpp"
  "module/utils/*.c"
  "module/utils/*.cpp"
  "module/events/*.c"
  "module/events/*.cpp"
  "module/resource/*.c"
  "module/resource/*.cpp"
  "module/resource/audio/*.c"
  "module/resource/audio/*.cpp"
  "module/resource/font/*.c"
  "module/resource/font/*.cpp"
  "module/resource/video/*.c"
  "module/resource/video/*.cpp"
  "module/resource/view/*.c"
  "module/resource/view/*.cpp"
  "module/task/*.c"
  "module/task/*.cpp"
  "module/signal/*.c"
  "module/signal/*.cpp"
)
file(GLOB CONTROLLER_C "controller/*.c" "controller/*.cpp")
file(GLOB VIEW_C
  "view/*.c"
  "view/*.cpp"
  "view/widget/*.c"
  "view/widget/*.cpp"
  "view/layout/*.c"
  "view/layout/*.cpp"
  "view/style/*.c"
  "view/style/*.cpp"
)

add_library(UiI ${VIEW_C} ${CONTROLLER_C} ${MODULE_C} ${RENDER_C})
target_include_directories(UiI SYSTEM INTERFACE ${UiI_INCLUDE_DIR})
target_link_libraries(UiI ${LIBSDL} ${LIBAV} curl)