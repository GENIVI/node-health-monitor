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
 * This header file is used for the NHM systemd unit test. It:
 *   - Includes headers with stubbed function definitions
 *   - Redefines the name of real functions to the stub names
 *   - Includes the test file, which will be patched to use the stubs
 *   - Undefine stubs, to allow usage of the real functions for the tests
 */

#ifndef NHM_TEST_SYSTEMD_H
#define NHM_TEST_SYSTEMD_H

/* Include stub header files */
#include <tst/stubs/gio/gio-stub.h>
#include <tst/stubs/dlt/dlt-stub.h>


/* Redefine some functions to stubs */
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

#define g_bus_get_sync \
        g_bus_get_sync_stub

#define g_dbus_connection_call_sync \
        g_dbus_connection_call_sync_stub

#define g_dbus_connection_signal_subscribe \
        g_dbus_connection_signal_subscribe_stub

#define g_dbus_connection_signal_unsubscribe \
        g_dbus_connection_signal_unsubscribe_stub

/* Include the main file. */
#include <src/nhm-systemd.c>

/* Undefine previous redefinitions */
#undef dlt_check_library_version
#undef dlt_register_context
#undef dlt_unregister_context
#undef dlt_unregister_app
#undef dlt_user_log_write_start
#undef dlt_user_log_write_finish
#undef dlt_user_log_write_string
#undef dlt_user_log_write_int
#undef dlt_user_log_write_uint

#undef g_bus_get_sync
#undef g_dbus_connection_call_sync
#undef g_dbus_connection_signal_subscribe
#undef g_dbus_connection_signal_unsubscribe

#endif /* NHM_TEST_SYSTEMD_H */
