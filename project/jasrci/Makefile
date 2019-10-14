SRC_DIR=./src
INCLUDE_DIR=./include
LIB_DIR=./lib
BIN_DIR=./bin

MAIN_DIR=${SRC_DIR}/main
LIBJASRRPCSERVER_DIR=${SRC_DIR}/libjasrrpcserver
LIBRPCSERVER_DIR=${SRC_DIR}/librpcserver
LIBTOOL_DIR=${SRC_DIR}/libtool

DEFINES=

INCLUDE=-I${INCLUDE_DIR} \
	-I${SRC_DIR} \
	-I${LIBJASRRPCSERVER_DIR}\
	-I${LIBRPCSERVER_DIR}\
	-I${LIBTOOL_DIR}

LDFLAGS=-L${LIB_DIR}

LIBS=	-ljASR_SDK\
	-lcommon\
	-llog4cxx\
	-lcurl\
	-ljson\
	-ljsonrpccpp-server\
	-ljsonrpccpp-common\
	-lhiredis\
	-ljsoncpp\
	-lmicrohttpd\
	-lboost_system\
	-lboost_thread\
	-lpthread

SRCS=	${wildcard  ${MAIN_DIR}/*.cpp} \
	${wildcard  ${LIBJASRRPCSERVER_DIR}/*.cpp} \
	${wildcard  ${LIBRPCSERVER_DIR}/*.cpp} \
	${wildcard  ${LIBTOOL_DIR}/*.cpp}

OBJS=${patsubst %.cpp, %.o, ${SRCS}}

DESTDIR=/usr/local

TARGET=${BIN_DIR}/jasrci
CXX=g++
CXXFLAGS=-g -Wall -O3 -Wno-unknown-pragmas -Wno-unused-local-typedefs $(DEFINES) ${INCLUDE} -std=c++11

${TARGET}: ${OBJS}
	rm -f $@
	${CXX} ${OBJS} ${LDFLAGS} ${LIBS} -o $@
	rm -f ${OBJS}
	@echo "Compile done."

$(OBJS):%.o:%.cpp
	@echo "Compiling $< ==> $@"
	${CXX} ${CXXFLAGS} -c $< -o $@

install:
	mkdir -p ${DESTDIR}/bin
	install -m 755 ${TARGET} ${DESTDIR}/bin
	@echo "Install to ${DESTDIR}/bin."

clean:
	rm -f ${OBJS}
	rm -f *.o
	@echo "Clean object files done."
	rm -f *~
	@echo "Clean tempreator files done."
	rm -f ${TARGET}
	@echo "Clean target files done."
	@echo "Clean done."

