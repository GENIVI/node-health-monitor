/* NHM - NodeHealthMonitor
 *
 * Implementation of stubs for the nsm-dbus-consumer
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
#include <gen/nsm-dbus-consumer.h>
#include <tst/stubs/gen/nsm-dbus-consumer-stub.h>

/*******************************************************************************
*
* Exported variables and constants
*
*******************************************************************************/

gboolean nsm_dbus_consumer_proxy_new_sync_stub_set_error                         = FALSE;
gboolean nsm_dbus_consumer_call_register_shutdown_client_sync_stub_set_error     = FALSE;
gint     nsm_dbus_consumer_call_register_shutdown_client_sync_stub_out_ErrorCode = 0;


/*******************************************************************************
*
* Interfaces. Exported functions.
*
*******************************************************************************/

/**
 * nsm_dbus_consumer_proxy_new_sync_stub:
 *
 * Stub for nsm_dbus_consumer_proxy_new_sync()
 */
NsmDbusConsumer*
nsm_dbus_consumer_proxy_new_sync_stub(GDBusConnection  *connection,
                                      GDBusProxyFlags   flags,
                                      const gchar      *name,
                                      const gchar      *object_path,
                                      GCancellable     *cancellable,
                                      GError          **error)
{
  NsmDbusConsumer *retval = NULL;

  if(nsm_dbus_consumer_proxy_new_sync_stub_set_error == FALSE)
  {
    retval = g_object_new(NSM_DBUS_TYPE_CONSUMER_PROXY, NULL);
  }
  else
  {
    retval = NULL;
    g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_DISCONNECTED, NULL);
  }

  return retval;
}

/**
 * nsm_dbus_consumer_call_register_shutdown_client_sync_stub:
 *
 * Stub for nsm_dbus_consumer_call_register_shutdown_client_sync()
 */
gboolean
nsm_dbus_consumer_call_register_shutdown_client_sync_stub(NsmDbusConsumer  *proxy,
                                                          const gchar      *arg_BusName,
                                                          const gchar      *arg_ObjName,
                                                          guint             arg_ShutdownMode,
                                                          guint             arg_TimeoutMs,
                                                          gint             *out_ErrorCode,
                                                          GCancellable     *cancellable,
                                                          GError          **error)
{
  gboolean retval = TRUE;

  if(nsm_dbus_consumer_call_register_shutdown_client_sync_stub_set_error == FALSE)
  {
    retval = TRUE;
    *out_ErrorCode = nsm_dbus_consumer_call_register_shutdown_client_sync_stub_out_ErrorCode;
  }
  else
  {
    retval = FALSE;
    g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_DISCONNECTED, NULL);
  }

  return retval;
}
