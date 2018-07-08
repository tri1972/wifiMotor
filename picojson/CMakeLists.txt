# picojsonライブラリをビルド
add_library(picoFunctions jsonReader.cpp)

# インストール
install (TARGETS picoFunctions DESTINATION bin)
install (FILES picojson.h DESTINATION include)

