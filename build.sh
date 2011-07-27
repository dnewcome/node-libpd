g++ -fPIC -shared \
-o libpd.node \
-I./libpd/dist -I/usr/local/include/node node-libpd.cc \
-lv8 ./libpd/dist/libpd.so
