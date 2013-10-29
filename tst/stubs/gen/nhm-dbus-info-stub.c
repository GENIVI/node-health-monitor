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
#include <gen/nhm-dbus-info.h>
#include <tst/stubs/gen/nhm-dbus-info-stub.h>

/*******************************************************************************
*
* Exported variables and constants
*
*******************************************************************************/

gint nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount = 0;
gint nhm_dbus_info_complete_read_statistics_stub_TotalFailures    = 0;
gint nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  = 0;
gint nhm_dbus_info_complete_request_node_restart_stub_ErrorStatus = 0;


/*******************************************************************************
*
* Interfaces. Exported functions.
*
*******************************************************************************/

/**
 * nhm_dbus_info_emit_app_health_status_stub:
 *
 * Stub for nhm_dbus_info_emit_app_health_status()
 */
void
nhm_dbus_info_emit_app_health_status_stub(NhmDbusInfo *object,
                                          const gchar *arg_AppName,
                                          gint         arg_AppStatus)
{

}

/**
 * nhm_dbus_info_complete_register_app_status_stub:
 *
 * Stub for nhm_dbus_info_complete_register_app_status()
 */
void
nhm_dbus_info_complete_register_app_status_stub(NhmDbusInfo           *object,
                                                GDBusMethodInvocation *invocation)
{

}

/**
 * nhm_dbus_info_complete_read_statistics_stub:
 *
 * Stub for nhm_dbus_info_complete_read_statistics()
 */
void
nhm_dbus_info_complete_read_statistics_stub(NhmDbusInfo           *object,
                                            GDBusMethodInvocation *invocation,
                                            guint                  CurrentFailCount,
                                            guint                  TotalFailures,
                                            guint                  TotalLifecycles,
                                            gint                   ErrorStatus)
{
  nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount = CurrentFailCount;
  nhm_dbus_info_complete_read_statistics_stub_TotalFailures    = TotalFailures;
  nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  = TotalLifecycles;
}

/**
 * nhm_dbus_info_complete_request_node_restart_stub:
 *
 * Stub for nhm_dbus_info_complete_request_node_restart()
 */
void
nhm_dbus_info_complete_request_node_restart_stub(NhmDbusInfo           *object,
                                                 GDBusMethodInvocation *invocation,
                                                 gint                   ErrorStatus)
{
  nhm_dbus_info_complete_request_node_restart_stub_ErrorStatus = ErrorStatus;
}

