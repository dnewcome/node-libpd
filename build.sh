g++ -fPIC -shared \
-o libpd.node \
-I./libpd/dist -I/usr/include/nodejs node-libpd.cc \
-lv8 ./libpd/dist/libpd.so
