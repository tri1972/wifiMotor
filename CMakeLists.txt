# CMakeのバージョンを設定
cmake_minimum_required(VERSION 2.8.11)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wno-psabi)

macro(compileAsC99)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_C_FLAGS "--std=c99 -g ${CMAKE_C_FLAGS}")
      set (CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")
    endif()
  else()
    set (CMAKE_C_STANDARD 99)
    set (CMAKE_CXX_STANDARD 11)
  endif()
endmacro(compileAsC99)
compileAsC99()

# プロジェクト名と使用する言語を設定
project(wifiMotor)

# インクルードファイルの探索パスにバイナリツリーを追加
include_directories("${PROJECT_BINARY_DIR}")
#プロジェクトディレクトリのファイルを追加
set(wifiMotor_c_files
  ./wifiMotor.cpp
  )
set(wifiMotor_h_files
  ./wifiMotor.h
  )

# 実行ファイルを作成
add_executable(wifiMotor ${wifiMotor_c_files} ${wifiMotor_h_files})


# サブディレクトリを登録
include_directories ("${PROJECT_SOURCE_DIR}/picojson")
add_subdirectory(picojson)
set (EXTRA_LIBS ${EXTRA_LIBS} picoFunctions)

include_directories ("${PROJECT_SOURCE_DIR}/drv8830")
add_subdirectory(drv8830)
set (EXTRA_LIBS ${EXTRA_LIBS} drv8830Functions)

include_directories ("${PROJECT_SOURCE_DIR}/daemonize")
add_subdirectory (daemonize)
set (EXTRA_LIBS ${EXTRA_LIBS} daemonizeFunctions)

include_directories ("${PROJECT_SOURCE_DIR}/motorServo")
add_subdirectory(motorServo)
set (EXTRA_LIBS ${EXTRA_LIBS} motorServoFunctions)

target_link_libraries(wifiMotor
  wiringPi
  wiringPiDev
  ${EXTRA_LIBS}
)
#### インストールターゲットを追加
# CMAKE_INSTALL_PREFIX (default=/usr/local)以下に install される
install (TARGETS wifiMotor DESTINATION bin)
install (FILES "${PROJECT_SOURCE_DIR}/wifiMotor.h"
  DESTINATION include)
install (FILES "${PROJECT_SOURCE_DIR}/daemonize/daemonize.h"
  DESTINATION include)
install (FILES "${PROJECT_SOURCE_DIR}/drv8830/lib_drv8830.h"
  DESTINATION include)
install (FILES "${PROJECT_SOURCE_DIR}/picojson/picojson.h"
  DESTINATION include)
install (FILES "${PROJECT_SOURCE_DIR}/wifiMotor.service"
  DESTINATION /etc/systemd/system/)
install (FILES "${PROJECT_SOURCE_DIR}/motorServo/lib_motorServo.h"
  DESTINATION include)
