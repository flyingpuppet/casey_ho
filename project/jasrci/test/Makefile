SRC_DIR=../src
TEST_SRC_DIR=./src
INCLUDE_DIR=../include
TEST_INCLUDE_DIR=./include
LIB_DIR=../lib
TEST_LIB_DIR=./lib
TEST_BIN_DIR=./bin

LIBTOOL_DIR=${SRC_DIR}/libtool
LIBASRRPCSERVER_DIR=${SRC_DIR}/libasrrpcserver
LIBRPCSERVER_DIR=${SRC_DIR}/librpcserver

TEST_MAIN_DIR=${TEST_SRC_DIR}/main
TEST_LIBTOOL_DIR=${TEST_SRC_DIR}/libtool
TEST_LIBASRRPCSERVER_DIR=${TEST_SRC_DIR}/libasrrpcserver
TEST_LIBRPCSERVER_DIR=${TEST_SRC_DIR}/librpcserver

DEFINES=-DBOOST_LOG_DYN_LINK

INCLUDE=-I${INCLUDE_DIR} \
	-I${TEST_INCLUDE_DIR} \
	-I${SRC_DIR} \
	-I${LIBTOOL_DIR}\
	-I${TEST_LIBTOOL_DIR}\
	-I${LIBRPCSERVER_DIR}\
	-I${TEST_LIBASRRPCSERVER_DIR}\
	-I${LIBRPCSERVER_DIR}\
	-I${TEST_LIBASRRPCSERVER_DIR}

LDFLAGS=-L${LIB_DIR} -L${TEST_LIB_DIR}

LIBS=	-lgtest\
	-lgmock\
	-ljsonrpccpp-server\
	-ljsonrpccpp-common\
	-ljsoncpp\
	-lmicrohttpd\
	-lboost_log_setup\
	-lboost_log\
	-lboost_date_time\
	-lboost_atomic\
	-lboost_chrono\
	-lboost_regex\
	-lboost_thread\
	-lboost_system\
	-lboost_filesystem\
	-lpthread

SRCS=	${wildcard  ${TEST_MAIN_DIR}/*.cpp} \
	${wildcard  ${LIBASRRPCSERVER_DIR}/*.cpp} \
	${wildcard  ${TEST_LIBASRRPCSERVER_DIR}/*.cpp} \
	${wildcard  ${LIBRPCSERVER_DIR}/*.cpp} \
	${wildcard  ${TEST_LIBRPCSERVER_DIR}/*.cpp} \
	${wildcard  ${LIBTOOL_DIR}/*.cpp}\
	${wildcard  ${TEST_LIBTOOL_DIR}/*.cpp}

OBJS=${patsubst %.cpp, %.o, ${SRCS}}

TARGET=${TEST_BIN_DIR}/test
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

clean:
	rm -f ${OBJS}
	rm -f *.o
	@echo "Clean object files done."
	rm -f *~
	@echo "Clean tempreator files done."
	rm -f ${TARGET}
	@echo "Clean target files done."
	@echo "Clean done."

