# メインライブラリを追加
add_library(daemonizeFunctions daemonize.cpp)

# インストール
install (TARGETS daemonizeFunctions DESTINATION bin)
install (FILES daemonize.h DESTINATION include)
