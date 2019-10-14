cd ../lib/
ln -s -f libjsonrpccpp-server.so.1.0.0 libjsonrpccpp-server.so.1
ln -s -f libjsonrpccpp-server.so.1 libjsonrpccpp-server.so
ln -s -f libjsonrpccpp-common.so.1.0.0 libjsonrpccpp-common.so.1
ln -s -f libjsonrpccpp-common.so.1 libjsonrpccpp-common.so

ln -s -f libhiredis.so libhiredis.so.0.13

ln -s -f libmicrohttpd.so.12.46.0 libmicrohttpd.so.12
ln -s -f libmicrohttpd.so.12 libmicrohttpd.so

ln -s -f libboost_system.so.1.66.0 libboost_system.so
ln -s -f libboost_thread.so.1.66.0 libboost_thread.so

ln -s -f libevent-2.0.so.5.1.9 libevent-2.0.so.5
ln -s -f libevent-2.0.so.5 libevent-2.0.so
ln -s -f libjson.so libjson.so.0
ln -s -f liblicense_server_sdk_private.so liblicense_server_sdk.so
ln -s -f liblog4cxx.so.10.0.0 liblog4cxx.so.10
ln -s -f liblog4cxx.so.10 liblog4cxx.so
ln -s -f libprotobuf.so.8.0.0 libprotobuf.so.8
ln -s -f libprotobuf.so.8 libprotobuf.so
ln -s -f libsoxr.so.0.1.0 libsoxr.so.0
ln -s -f libsoxr.so.0 libsoxr.so

SR_LIB_PATH=$(cd `dirname $0`; pwd)
echo "export LD_LIBRARY_PATH=$SR_LIB_PATH:\$LD_LIBRARY_PATH" >> ~/.bashrc

cd ..
make

#SR_PATH=$(cd `dirname $0`; pwd)
#echo "export HCICLOUD_HOME=$SR_PATH" >> ~/.bashrc

source ~/.bashrc

cd bin/
