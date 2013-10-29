/* NHM - NodeHealthMonitor
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 */

/*
 * This header file is only used for the unit test. It:
 *   - Includes headers with stubbed function definitions
 *   - Redefines the name of real functions to the stub names
 *   - Includes the main, which will be patched to use the stubs
 *   - Undefine stubs, to allow usage of the real functions for the tests
 */

#ifndef NHM_TEST_MAIN_H
#define NHM_MAIN_TEST_H

/* Include stub header files */
#include <tst/stubs/gen/nhm-dbus-info-stub.h>
#include <tst/stubs/gen/nsm-dbus-consumer-stub.h>
#include <tst/stubs/gen/nsm-dbus-lc-control-stub.h>
#include <tst/stubs/gen/nsm-dbus-lc-consumer-stub.h>
#include <tst/stubs/gio/gio-stub.h>
#include <tst/stubs/dlt/dlt-stub.h>
#include <tst/stubs/nhm/nhm-systemd-stub.h>
#include <tst/stubs/systemd/sd-daemon-stub.h>
#include <tst/stubs/persistence/persistence_client_library_key-stub.h>

/* Redefine some functions to stubs */
#define nhm_systemd_connect \
        nhm_systemd_connect_stub

#define nhm_systemd_disconnect \
        nhm_systemd_disconnect_stub

#define dlt_register_app \
        dlt_register_app_stub

#define dlt_check_library_version \
        dlt_check_library_version_stub

#define dlt_register_context \
        dlt_register_context_stub

#define dlt_unregister_context \
        dlt_unregister_context_stub

#define dlt_unregister_app \
        dlt_unregister_app_stub

#define dlt_user_log_write_start \
        dlt_user_log_write_start_stub

#define dlt_user_log_write_finish \
        dlt_user_log_write_finish_stub

#define dlt_user_log_write_string \
        dlt_user_log_write_string_stub

#define dlt_user_log_write_int \
        dlt_user_log_write_int_stub

#define dlt_user_log_write_uint \
        dlt_user_log_write_uint_stub

#define nhm_dbus_info_emit_app_health_status \
        nhm_dbus_info_emit_app_health_status_stub

#define nhm_dbus_info_complete_register_app_status \
        nhm_dbus_info_complete_register_app_status_stub

#define nhm_dbus_info_complete_read_statistics \
        nhm_dbus_info_complete_read_statistics_stub

#define nhm_dbus_info_complete_request_node_restart \
        nhm_dbus_info_complete_request_node_restart_stub

#define nsm_dbus_consumer_proxy_new_sync \
        nsm_dbus_consumer_proxy_new_sync_stub

#define nsm_dbus_consumer_call_register_shutdown_client_sync \
        nsm_dbus_consumer_call_register_shutdown_client_sync_stub

#define nsm_dbus_lc_consumer_proxy_new_sync \
        nsm_dbus_lc_consumer_proxy_new_sync_stub

#define nsm_dbus_lc_consumer_complete_lifecycle_request \
        nsm_dbus_lc_consumer_complete_lifecycle_request_stub

#define nsm_dbus_lc_control_proxy_new_sync \
        nsm_dbus_lc_control_proxy_new_sync_stub

#define nsm_dbus_lc_control_call_set_app_health_status_sync \
        nsm_dbus_lc_control_call_set_app_health_status_sync_stub

#define nsm_dbus_lc_control_call_request_node_restart_sync \
        nsm_dbus_lc_control_call_request_node_restart_sync_stub

#define g_file_test \
        g_file_test_stub

#define g_file_read_link \
        g_file_read_link_stub

#define g_dir_open \
        g_dir_open_stub

#define g_dir_read_name \
        g_dir_read_name_stub

#define g_dir_close \
        g_dir_close_stub

#define g_main_loop_run \
        g_main_loop_run_stub

#define g_main_loop_quit \
        g_main_loop_quit_stub

#define g_bus_get_sync \
        g_bus_get_sync_stub

#define g_dbus_connection_get_unique_name \
        g_dbus_connection_get_unique_name_stub

#define g_bus_own_name \
        g_bus_own_name_stub

#define g_dbus_interface_skeleton_export \
        g_dbus_interface_skeleton_export_stub

#define g_dbus_connection_new_for_address_sync \
        g_dbus_connection_new_for_address_sync_stub

#define g_dbus_connection_call_sync \
        g_dbus_connection_call_sync_stub

#define g_dbus_connection_signal_subscribe \
        g_dbus_connection_signal_subscribe_stub

#define g_dbus_connection_signal_unsubscribe \
        g_dbus_connection_signal_unsubscribe_stub

#define g_dbus_connection_call_sync \
        g_dbus_connection_call_sync_stub

#define g_timeout_add_seconds \
        g_timeout_add_seconds_stub

#define g_signal_connect_data \
        g_signal_connect_data_stub

#define g_spawn_sync \
        g_spawn_sync_stub

#define sd_notify \
        sd_notify_stub

#define pclKeyWriteData \
        pclKeyWriteData_stub

#define pclKeyReadData \
        pclKeyReadData_stub

#define pclInitLibrary \
        pclInitLibrary_stub

#define pclDeinitLibrary \
        pclDeinitLibrary_stub

/* Redefine main() to use test frames main() */
#define main \
        nhm_main

/* Include the main file. */
#include <src/nhm-main.c>

/* Undefine main to be able to have a main in the test frame */
#undef main

/* Undefine previous redefinitions */
#undef nhm_systemd_connect
#undef nhm_systemd_disconnect
#undef dlt_check_library_version
#undef dlt_register_context
#undef dlt_unregister_context
#undef dlt_unregister_app
#undef dlt_user_log_write_start
#undef dlt_user_log_write_finish
#undef dlt_user_log_write_string
#undef dlt_user_log_write_int
#undef dlt_user_log_write_uint
#undef nhm_dbus_info_emit_app_health_status
#undef nhm_dbus_info_complete_register_app_status
#undef nhm_dbus_info_complete_read_statistics
#undef nhm_dbus_info_complete_request_node_restart
#undef nsm_dbus_consumer_proxy_new_sync
#undef nsm_dbus_consumer_call_register_shutdown_client_sync
#undef nsm_dbus_lc_consumer_proxy_new_sync
#undef nsm_dbus_lc_consumer_complete_lifecycle_request
#undef nsm_dbus_lc_control_proxy_new_sync
#undef nsm_dbus_lc_control_call_set_app_health_status_sync
#undef nsm_dbus_lc_control_call_request_node_restart_sync
#undef g_file_test
#undef g_file_read_link
#undef g_dir_open
#undef g_dir_read_name
#undef g_dir_close
#undef g_main_loop_run
#undef g_main_loop_quit
#undef g_bus_get_sync
#undef g_dbus_connection_get_unique_name
#undef g_bus_own_name
#undef g_dbus_interface_skeleton_export
#undef g_dbus_connection_new_for_address_sync
#undef g_dbus_connection_call_sync
#undef g_dbus_connection_signal_subscribe
#undef g_dbus_connection_signal_unsubscribe
#undef g_dbus_connection_call_sync
#undef g_timeout_add_seconds
#undef g_signal_connect_data
#undef g_spawn_sync
#undef sd_notify
#undef pclKeyWriteData
#undef pclKeyReadData
#undef pclInitLibrary
#undef pclDeinitLibrary


#endif /* NHM_MAIN_TEST_H */
