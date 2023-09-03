# Include .h ###################################################################
include_directories(.)
include_directories(module)
include_directories(module/utils)
include_directories(module/types)
include_directories(module/types/NDEF)
include_directories(module/events)
include_directories(module/resource)
include_directories(module/resource/audio)
include_directories(module/resource/font)
include_directories(module/resource/video)
include_directories(module/resource/view)
include_directories(module/signal)
include_directories(module/task)
include_directories(module/template)
include_directories(module/driver/linux-common)
include_directories(module/driver)
include_directories(view)
include_directories(controller)
include_directories(controller/nfc)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mfrc522/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mfrc522/interface)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mfrc522/example)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mfrc522/test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mfrc522/src/*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mifare_classic/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mifare_classic/interface)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mifare_classic/example)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mifare_classic/test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mifare_classic/src/*.h)

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

file(GLOB NDEF_C "module/types/NDEF/*.c" "module/types/NDEF/*.cpp")
file(GLOB NDEF_HELPER_C "controller/nfc/*.c" "controller/nfc/*.cpp")

file(GLOB MFRC522_C
  ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mfrc522/src/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mfrc522/example/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mfrc522/test/*.c
)

file(GLOB MIFARE_C
  ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mifare_classic/src/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mifare_classic/example/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mifare_classic/test/*.c
)

file(GLOB MAIN_C
  "main.cpp"
  "punch_curl.cpp"
  "punch_view.cpp"
)

if(APPLE)
  add_executable(${CMAKE_PROJECT_NAME} ${MAIN_C} ${VIEW_C} ${CONTROLLER_C} ${MODULE_C} ${RENDER_C})
  target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE)
  target_link_libraries(${CMAKE_PROJECT_NAME}  ${LIBSDL} ${LIBAV} curl)
else()
  add_executable(${CMAKE_PROJECT_NAME} ${MAIN_C} ${VIEW_C} ${CONTROLLER_C} ${MODULE_C} ${RENDER_C}
    ${EMBED_C} ${MIFARE_C} ${MFRC522_C} ${NDEF_C} ${NDEF_HELPER_C})
  target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE USE_DRIVER_MFRC522 NO_DEBUG)
  target_link_libraries(${CMAKE_PROJECT_NAME}  pthread gpiod ${LIBSDL} ${LIBAV} curl)
endif()

# install library #################################################################
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../punch_config.conf DESTINATION bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../script/upgrade.sh DESTINATION bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../resource/service/punch.service DESTINATION bin)