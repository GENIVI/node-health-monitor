/* NHM - NodeHealthMonitor
 *
 * Definition of stubs for nsm-dbus-lc-consumer
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef NSM_DBUS_LC_CONSUMER_STUB_H
#define NSM_DBUS_LC_CONSUMER_STUB_H

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

#include <gio/gio.h>
#include <gen/nsm-dbus-lc-consumer.h> /* Header of real nsm-dbus-lc-consumer */

/*******************************************************************************
*
* Exported variables, constants and defines
*
*******************************************************************************/

extern gboolean nsm_dbus_lc_consumer_proxy_new_sync_stub_set_error;
extern gint nsm_dbus_lc_consumer_complete_lifecycle_request_stub_ErrorCode;

/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

NsmDbusLcConsumer* nsm_dbus_lc_consumer_proxy_new_sync_stub(GDBusConnection      *connection,
                                                            GDBusProxyFlags       flags,
                                                            const gchar          *name,
                                                            const gchar          *object_path,
                                                            GCancellable         *cancellable,
                                                            GError              **error);


void nsm_dbus_lc_consumer_complete_lifecycle_request_stub  (NsmDbusLcConsumer     *object,
                                                            GDBusMethodInvocation *invocation,
                                                            gint                   ErrorCode);

#endif /* NSM_DBUS_LC_CONSUMER_STUB_H */

