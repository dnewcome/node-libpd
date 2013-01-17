# note that node native modules must be named according to a 
# .node file extension
g++ -fPIC -shared \
-o libpd.node \
-I./libpd/dist -I/usr/local/include/node node-libpd.cc \
-lv8 ./libpd/dist/libpd.dylib
