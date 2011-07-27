g++ -fPIC -shared \
-o libpd.node \
-I./libpd/dist -I/usr/local/include/node mod.cc \
-lv8 ./libpd/dist/libpd.so
