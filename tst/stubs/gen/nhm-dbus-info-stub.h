/* NHM - NodeHealthMonitor
 *
 * Definition of stubs for nhm-dbus-info
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef NHM_DBUS_INFO_STUB_H
#define NHM_DBUS_INFO_STUB_H

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

#include <gio/gio.h>
#include <gen/nhm-dbus-info.h> /* Header of real nsm-dbus-info */

/*******************************************************************************
*
* Exported variables, constants and defines
*
*******************************************************************************/

extern gint nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount;
extern gint nhm_dbus_info_complete_read_statistics_stub_TotalFailures;
extern gint nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles;
extern gint nhm_dbus_info_complete_request_node_restart_stub_ErrorStatus;

/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

void nhm_dbus_info_emit_app_health_status_stub       (NhmDbusInfo           *object,
                                                      const gchar           *arg_AppName,
                                                      gint                   arg_AppStatus);

void nhm_dbus_info_complete_register_app_status_stub (NhmDbusInfo           *object,
                                                      GDBusMethodInvocation *invocation);

void nhm_dbus_info_complete_read_statistics_stub     (NhmDbusInfo           *object,
                                                      GDBusMethodInvocation *invocation,
                                                      guint                  CurrentFailCount,
                                                      guint                  TotalFailures,
                                                      guint                  TotalLifecycles,
                                                      gint                   ErrorStatus);


void nhm_dbus_info_complete_request_node_restart_stub(NhmDbusInfo           *object,
                                                      GDBusMethodInvocation *invocation,
                                                      gint                   ErrorStatus);

#endif /* NHM_DBUS_INFO_STUB_H */
