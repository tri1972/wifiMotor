# drv8830ライブラリをビルド
add_library(motorServoFunctions lib_motorServo.cpp)

# インストール
install (TARGETS motorServoFunctions DESTINATION bin)
install (FILES lib_motorServo.h DESTINATION include)
