/* NHM - NodeHealthMonitor
 *
 * Definition of stubs for nsm-dbus-consumer
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef NSM_DBUS_CONSUMER_STUB_H
#define NSM_DBUS_CONSUMER_STUB_H

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

#include <gio/gio.h>
#include <gen/nsm-dbus-consumer.h> /* Header of real nsm-dbus-consumer */

/*******************************************************************************
*
* Exported variables, constants and defines
*
*******************************************************************************/

extern gboolean nsm_dbus_consumer_proxy_new_sync_stub_set_error;
extern gboolean nsm_dbus_consumer_call_register_shutdown_client_sync_stub_set_error;
extern gint     nsm_dbus_consumer_call_register_shutdown_client_sync_stub_out_ErrorCode;

/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

NsmDbusConsumer* nsm_dbus_consumer_proxy_new_sync_stub            (GDBusConnection  *connection,
                                                                   GDBusProxyFlags   flags,
                                                                   const gchar      *name,
                                                                   const gchar      *object_path,
                                                                   GCancellable     *cancellable,
                                                                   GError          **error);

gboolean nsm_dbus_consumer_call_register_shutdown_client_sync_stub(NsmDbusConsumer  *proxy,
                                                                   const gchar      *arg_BusName,
                                                                   const gchar      *arg_ObjName,
                                                                   guint             arg_ShutdownMode,
                                                                   guint             arg_TimeoutMs,
                                                                   gint             *out_ErrorCode,
                                                                   GCancellable     *cancellable,
                                                                   GError          **error);

#endif /* NSM_DBUS_CONSUMER_STUB_H */
