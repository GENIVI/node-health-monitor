/* NHM - NodeHealthMonitor
 *
 * Implementation of stubs for the nsm-dbus-lc-control
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

#include <gio/gio.h>
#include <gen/nsm-dbus-lc-control.h>
#include <tst/stubs/gen/nsm-dbus-lc-control-stub.h>

/*******************************************************************************
*
* Exported variables and constants
*
*******************************************************************************/

gboolean nsm_dbus_lc_control_proxy_new_sync_stub_set_error                     = FALSE;
gboolean nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error    = FALSE;
gboolean nsm_dbus_lc_control_call_request_node_restart_sync_stub_set_error     = FALSE;
gint     nsm_dbus_lc_control_call_request_node_restart_sync_stub_out_ErrorCode = 0;

/*******************************************************************************
*
* Interfaces. Exported functions.
*
*******************************************************************************/

/**
 * nsm_dbus_lc_control_proxy_new_sync_stub:
 *
 * Stub for nsm_dbus_lc_control_proxy_new_sync()
 */
NsmDbusLcControl*
nsm_dbus_lc_control_proxy_new_sync_stub(GDBusConnection *connection,
                                        GDBusProxyFlags  flags,
                                        const gchar     *name,
                                        const gchar     *object_path,
                                        GCancellable    *cancellable,
                                        GError         **error)
{
  NsmDbusLcControl* retval = NULL;

  if(nsm_dbus_lc_control_proxy_new_sync_stub_set_error == FALSE)
  {
    retval = g_object_new(NSM_DBUS_LC_TYPE_CONTROL_PROXY, NULL);
  }
  else
  {
    retval = NULL;
    g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_DISCONNECTED, NULL);
  }

  return retval;
}

/**
 * nsm_dbus_lc_control_call_set_app_health_status_sync_stub:
 *
 * Stub for nsm_dbus_lc_control_call_set_app_health_status_sync()
 */
gboolean
nsm_dbus_lc_control_call_set_app_health_status_sync_stub(NsmDbusLcControl *proxy,
                                                         const gchar      *arg_AppName,
                                                         gboolean          arg_AppRunning,
                                                         gint             *out_ErrorCode,
                                                         GCancellable     *cancellable,
                                                         GError          **error)
{
  gboolean retval = FALSE;

  if(nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error == FALSE)
  {
    retval = TRUE;
  }
  else
  {
    retval = FALSE;
    g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_DISCONNECTED, NULL);
  }

  return retval;
}

/**
 * nsm_dbus_lc_control_call_request_node_restart_sync_stub:
 *
 * Stub for nsm_dbus_lc_control_call_request_node_restart_sync()
 */
gboolean
nsm_dbus_lc_control_call_request_node_restart_sync_stub(NsmDbusLcControl *proxy,
                                                        gint              arg_RestartReason,
                                                        guint             arg_RestartType,
                                                        gint             *out_ErrorCode,
                                                        GCancellable     *cancellable,
                                                        GError          **error)
{
  gboolean retval = FALSE;

  if(nsm_dbus_lc_control_call_request_node_restart_sync_stub_set_error == FALSE)
  {
    *out_ErrorCode = nsm_dbus_lc_control_call_request_node_restart_sync_stub_out_ErrorCode;
  }
  else
  {
    retval = FALSE;
    g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_DISCONNECTED, NULL);
  }

  return retval;
}
