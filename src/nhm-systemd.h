#ifndef NHM_SYSTEMD
#define NHM_SYSTEMD

/* NHM - NodeHealthMonitor
 *
 * Functions to observe system health with systemd
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

#include <gio/gio.h>               /* Use gtypes                 */
#include "inc/NodeHealthMonitor.h" /* Use NHM app status defines */


/*******************************************************************************
*
* Exported variables, constants and defines
*
*******************************************************************************/

typedef void (*NhmSystemdAppStatusCb)(const gchar *name, NhmAppStatus_e status);


/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

gboolean nhm_systemd_connect   (NhmSystemdAppStatusCb app_status_cb);
void     nhm_systemd_disconnect(void);


#endif /* NHM_SYSTEMD */
