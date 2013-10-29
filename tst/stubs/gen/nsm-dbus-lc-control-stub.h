/* NHM - NodeHealthMonitor
 *
 * Definition of stubs for nsm-dbus-lc-control
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef NSM_DBUS_LC_CONTROL_STUB_H
#define NSM_DBUS_LC_CONTROL_STUB_H

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

#include <gio/gio.h>
#include <gen/nsm-dbus-lc-control.h> /* Header of real nsm-dbus-lc-control */

/*******************************************************************************
*
* Exported variables, constants and defines
*
*******************************************************************************/

extern gboolean nsm_dbus_lc_control_proxy_new_sync_stub_set_error;
extern gboolean nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error;
extern gboolean nsm_dbus_lc_control_call_request_node_restart_sync_stub_set_error;
extern gint     nsm_dbus_lc_control_call_request_node_restart_sync_stub_out_ErrorCode;

/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

NsmDbusLcControl* nsm_dbus_lc_control_proxy_new_sync_stub                 (GDBusConnection  *connection,
                                                                           GDBusProxyFlags   flags,
                                                                           const gchar      *name,
                                                                           const gchar      *object_path,
                                                                           GCancellable     *cancellable,
                                                                           GError          **error);



gboolean          nsm_dbus_lc_control_call_set_app_health_status_sync_stub(NsmDbusLcControl *proxy,
                                                                           const gchar      *arg_AppName,
                                                                           gboolean          arg_AppRunning,
                                                                           gint             *out_ErrorCode,
                                                                           GCancellable     *cancellable,
                                                                           GError          **error);


gboolean          nsm_dbus_lc_control_call_request_node_restart_sync_stub (NsmDbusLcControl  *proxy,
                                                                           gint               arg_RestartReason,
                                                                           guint              arg_RestartType,
                                                                           gint              *out_ErrorCode,
                                                                           GCancellable      *cancellable,
                                                                           GError           **error);


#endif /* NSM_DBUS_LC_CONTROL_STUB_H */
