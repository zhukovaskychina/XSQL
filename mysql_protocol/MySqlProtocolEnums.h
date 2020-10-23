//
// Created by zhukovasky on 2020/9/17.
//

#ifndef MUDUO_SERVER_MYSQLPROTOCOLENUMS_H
#define MUDUO_SERVER_MYSQLPROTOCOLENUMS_H

#include <common/Common.h>
enum MySQLProtocolEnums {

    /**
* none, this is an internal thread state
*/
    COM_SLEEP = 0,

    /**
     * mysql_close
     */
     COM_QUIT = 1,

    /**
     * mysql_select_db
     */
     COM_INIT_DB = 2,

    /**
     * mysql_real_query
     */
     COM_QUERY = 3,

    /**
     * mysql_list_fields
     */
     COM_FIELD_LIST = 4,

    /**
     * mysql_create_db (deprecated)
     */
     COM_CREATE_DB = 5,

    /**
     * mysql_drop_db (deprecated)
     */
     COM_DROP_DB = 6,

    /**
     * mysql_refresh
     */
     COM_REFRESH = 7,

    /**
     * mysql_shutdown
     */
     COM_SHUTDOWN = 8,

    /**
     * mysql_stat
     */
     COM_STATISTICS = 9,

    /**
     * mysql_list_processes
     */
     COM_PROCESS_INFO = 10,

    /**
     * none, this is an internal thread state
     */
     COM_CONNECT = 11,

    /**
     * mysql_kill
     */
     COM_PROCESS_KILL = 12,

    /**
     * mysql_dump_debug_info
     */
     COM_DEBUG = 13,

    /**
     * mysql_ping
     */
     COM_PING = 14,

    /**
     * none, this is an internal thread state
     */
     COM_TIME = 15,

    /**
     * none, this is an internal thread state
     */
     COM_DELAYED_INSERT = 16,

    /**
     * mysql_change_user
     */
     COM_CHANGE_USER = 17,

    /**
     * used by slave server mysqlbinlog
     */
     COM_BINLOG_DUMP = 18,

    /**
     * used by slave server to getDecoder master table
     */
     COM_TABLE_DUMP = 19,

    /**
     * used by slave to log connection to master
     */
     COM_CONNECT_OUT = 20,

    /**
     * used by slave to register to master
     */
     COM_REGISTER_SLAVE = 21,

    /**
     * mysql_stmt_prepare
     */
     COM_STMT_PREPARE = 22,

    /**
     * mysql_stmt_execute
     */
     COM_STMT_EXECUTE = 23,

    /**
     * mysql_stmt_send_long_data
     */
     COM_STMT_SEND_LONG_DATA = 24,

    /**
     * mysql_stmt_close
     */
     COM_STMT_CLOSE = 25,

    /**
     * mysql_stmt_reset
     */
     COM_STMT_RESET = 26,

    /**
     * mysql_set_server_option
     */
     COM_SET_OPTION = 27,

    /**
     * mysql_stmt_fetch
     */
     COM_STMT_FETCH = 28,

    /**
     * cobar heartbeat
     */
     COM_HEARTBEAT = 64,

     SERVER_MORE_RESULTS_EXISTS=8

};


#endif //MUDUO_SERVER_MYSQLPROTOCOLENUMS_H
