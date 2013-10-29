/* NHM - NodeHealthMonitor
 *
 * Implementation of stubs for the nsm-dbus-lc-consumer
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
#include <gen/nsm-dbus-lc-consumer.h>
#include <tst/stubs/gen/nsm-dbus-lc-consumer-stub.h>

/*******************************************************************************
*
* Exported variables and constants
*
*******************************************************************************/

gboolean nsm_dbus_lc_consumer_proxy_new_sync_stub_set_error         = FALSE;
gint nsm_dbus_lc_consumer_complete_lifecycle_request_stub_ErrorCode = 0;

/*******************************************************************************
*
* Interfaces. Exported functions.
*
*******************************************************************************/

/**
 * nsm_dbus_lc_consumer_proxy_new_sync_stub:
 *
 * Stub for nsm_dbus_lc_consumer_proxy_new_sync()
 */
NsmDbusLcConsumer*
nsm_dbus_lc_consumer_proxy_new_sync_stub(GDBusConnection  *connection,
                                         GDBusProxyFlags   flags,
                                         const gchar      *name,
                                         const gchar      *object_path,
                                         GCancellable     *cancellable,
                                         GError          **error)
{
  NsmDbusLcConsumer *retval = NULL;

  if(nsm_dbus_lc_consumer_proxy_new_sync_stub_set_error == FALSE)
  {
    retval = g_object_new(NSM_DBUS_LC_TYPE_CONSUMER_PROXY, NULL);
  }
  else
  {
    retval = NULL;
    g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_DISCONNECTED, NULL);
  }

  return retval;
}

/**
 * nsm_dbus_lc_consumer_complete_lifecycle_request_stub:
 *
 * Stub for nsm_dbus_lc_consumer_complete_lifecycle_request()
 */
void
nsm_dbus_lc_consumer_complete_lifecycle_request_stub(NsmDbusLcConsumer     *object,
                                                     GDBusMethodInvocation *invocation,
                                                     gint                   ErrorCode)
{
  nsm_dbus_lc_consumer_complete_lifecycle_request_stub_ErrorCode = ErrorCode;
}
