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

/******************************************************************************
*
* Header includes
*
******************************************************************************/

#include <gio/gio.h>         /* Use gtypes      */
#include <src/nhm-systemd.h> /* Original header */

/******************************************************************************
*
* Interfaces. Exported functions. See Header for detailed description.
*
******************************************************************************/


/**
 * nhm_systemd_connect_stub:
 *
 * Stub for nhm_systemd_connect()
 */
gboolean
nhm_systemd_connect_stub(NhmSystemdAppStatusCb app_status_cb)
{
  return TRUE;
}

/**
 * nhm_systemd_disconnect_stub:
 *
 * Stub for nhm_systemd_disconnect()
 */
void
nhm_systemd_disconnect_stub(void)
{

}
