cmake_minimum_required(VERSION 3.15)
project(XSQL)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "release-install-cpp11")
endif()
message(${CMAKE_BUILD_TYPE})
message(MUDUO_PATH)
if (NOT MUDUO_PATH)
    set(MUDUO_PATH "/home/$ENV{USER}/wk/build/release-install-cpp11")
endif ()
message("开始发现")
message(${MUDUO_PATH})
set(CXX_FLAGS
        -g
        # -DVALGRIND
        # -DMUDUO_STD_STRING
        -Wall
        -Wextra
        # -m32
        #-Werror
        -Wconversion
        -Wno-unused-parameter
         -Wold-style-cast
        -Woverloaded-virtual
        -Wpointer-arith
        #-Wshadow
        -Wwrite-strings
        -march=native
        # -MMD
         -std=c++0x
        -rdynamic
        )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1001 -DNDEBUG")
message(${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

find_path(Muduo_INCLUDE_DIR muduo "${MUDUO_PATH}/include")
find_path(Muduo_LIBRARY_DIR libmuduo_net.a "${MUDUO_PATH}/lib")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${Muduo_LIBRARY_DIR})
message(STATUS ${Muduo_INCLUDE_DIR})
message(STATUS ${Muduo_LIBRARY_DIR})

include_directories(${Muduo_INCLUDE_DIR})
find_library(muduo_base muduo_base)
find_library(muduo_net muduo_net)
message(STATUS ${muduo_base})
message(STATUS ${muduo_net})

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(BOOST_ROOT "/usr/include/boost")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

include_directories(
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2/src/
        ${PROJECT_SOURCE_DIR}/engine/sqlparser/
)
set(src_dir
        ${PROJECT_SOURCE_DIR}/engine/sqlparser/MySQLParserVisitor.cpp
        ${PROJECT_SOURCE_DIR}/engine/sqlparser/MySQLParserListener.cpp
        ${PROJECT_SOURCE_DIR}/engine/sqlparser/MySQLParser.cpp
        ${PROJECT_SOURCE_DIR}/engine/sqlparser/MySQLParserBaseVisitor.cpp
        ${PROJECT_SOURCE_DIR}/engine/sqlparser/MySQLParserBaseListener.cpp
        ${PROJECT_SOURCE_DIR}/engine/sqlparser/MySQLLexer.cpp
        common/Exceptions.h engine/mysqlparser/listener/dml/SetListener.cpp engine/mysqlparser/listener/dml/SetListener.h)

find_package(Boost
        COMPONENTS
        serialization
        system
        filesystem
        program_options
        regex
        )
add_executable(XSQL ${src_dir} main.cpp
        utils/StringUtils.h utils/FileUtils.h common/Common.h
        mysql_protocol/MySqlPacket.h
        mysql_protocol/MySqlProtocolEnums.h
        mysql_protocol/MySqlPacketDecode.h
        utils/BufferUtils.h
        utils/ByteUtils.h
        mysql_protocol/packet/BinaryPacket.cpp
        mysql_protocol/packet/BinaryPacket.h
        mysql_protocol/packet/OkPacket.cpp
        mysql_protocol/packet/OkPacket.h
        mysql_protocol/packet/MySqlMessage.cpp
        mysql_protocol/packet/MySqlMessage.h
        engine/block_handle.cc
        engine/block_handle.h
        engine/block_info.cc
        engine/block_info.h
        engine/buffer_manager.cc
        engine/buffer_manager.h
        engine/catalog_manager.cc
        engine/catalog_manager.h
        engine/commons.h
        engine/exceptions.h
        engine/file_handle.cc
        engine/file_handle.h
        engine/file_info.cc
        engine/file_info.h
        engine/index_manager.cc
        engine/index_manager.h
        engine/interpreter.cc
        engine/interpreter.h
        engine/minidb_api.cc
        engine/minidb_api.h
        engine/record_manager.cc
        engine/record_manager.h
        engine/sql_statement.cc
        engine/sql_statement.h
        mysql_protocol/packet/HandshakePacket.cpp
        mysql_protocol/packet/HandshakePacket.h utils/RandomUtils.h utils/CharsetUtils.h mysql_protocol/Capabilities.h
        mysql_protocol/packet/AuthPacket.cpp mysql_protocol/packet/AuthPacket.h server/XdbServer.cpp server/XdbServer.h
        engine/session/SessionConnection.cpp
        engine/session/SessionConnection.h
        engine/handler/SqlQueryHandler.cpp engine/handler/SqlQueryHandler.h
        engine/mysqlparser/listener/ddl/SelectStatementListener.h
        engine/mysqlparser/listener/ddl/SelectStatementListener.cpp
        engine/mysqlparser/listener/ddl/InsertTableStatmentListener.h
        engine/mysqlparser/listener/ddl/InsertTableStatmentListener.cpp
        engine/interpret/SqlInterpret.cpp
        engine/interpret/SqlInterpret.h
        engine/mysqlparser/parser/MySqlStatement.cpp
        engine/mysqlparser/parser/MySqlStatement.h
        engine/mysqlparser/listener/dml/CreateDataBaseListener.cpp
        engine/mysqlparser/listener/dml/CreateDataBaseListener.h
        utils/ParseUtils.h
        engine/mysqlparser/listener/SqlErrorListener.cpp
        engine/mysqlparser/listener/SqlErrorListener.h
        engine/mysqlparser/listener/dml/CreateTableListener.cpp
        engine/mysqlparser/listener/dml/CreateTableListener.h
        engine/core/XApi.cpp
        engine/core/XApi.h engine/mysqlparser/listener/dml/UseListener.cpp engine/mysqlparser/listener/dml/UseListener.h mysql_protocol/packet/ErrorPacket.cpp mysql_protocol/packet/ErrorPacket.h mysql_protocol/packet/CommandPacket.cpp mysql_protocol/packet/CommandPacket.h mysql_protocol/packet/EofPacket.cpp mysql_protocol/packet/EofPacket.h mysql_protocol/packet/FieldPacket.cpp mysql_protocol/packet/FieldPacket.h mysql_protocol/packet/RowDataPacket.cpp mysql_protocol/packet/RowDataPacket.h mysql_protocol/packet/ResultSetHeaderPacket.cpp mysql_protocol/packet/ResultSetHeaderPacket.h mysql_protocol/response/OkResponse.cpp mysql_protocol/response/OkResponse.h mysql_protocol/response/ErrorResponse.h mysql_protocol/response/SelectDatabaseResponse.h utils/PacketUtils.cpp utils/PacketUtils.h engine/mysqlparser/listener/CheckSqlStatementListener.cpp engine/mysqlparser/listener/CheckSqlStatementListener.h engine/mysqlparser/listener/ddl/ShowDatabaseListener.cpp engine/mysqlparser/listener/ddl/ShowDatabaseListener.h mysql_protocol/response/ShowDatabaseResponse.h mysql_protocol/response/ShowTableResponse.h mysql_protocol/response/ShowDescribeTableResponse.h)
file(GLOB antlr4-cpp-src
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2/src/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2/src/atn/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2/src/dfa/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2/src/misc/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2/src/support/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2/src/tree/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2/src/tree/pattern/*.cpp
        ${PROJECT_SOURCE_DIR}/libs/antlr4-cpp-runtime-4.7.2/src/tree/xpath/*.cpp
        )
add_library (antlr4-cpp-runtime ${antlr4-cpp-src})

link_directories(... ${Boost_LIBRARY_DIRS})
target_link_libraries(XSQL ${muduo_net})
target_link_libraries(XSQL ${muduo_base})
target_link_libraries(XSQL pthread rt ${Boost_LIBRARIES})
#target_link_libraries(XSQL z m ${PROJECT_SOURCE_DIR}/libs/libs/libantlr4-runtime.a)
target_link_libraries(XSQL antlr4-cpp-runtime)