g++ -fPIC -shared \
-o cpphello.node \
-I./libpd/dist -I/usr/local/include/node mod.cc \
-lv8 ./libpd/dist/libpd.so
