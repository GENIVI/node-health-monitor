#ifndef NHM_SYSTEMD_STUB_H
#define NHM_SYSTEMD_STUB_H

/* NHM - NodeHealthMonitor
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
#include <src/nhm-systemd.h>       /* Original header            */

/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

gboolean nhm_systemd_connect_stub   (NhmSystemdAppStatusCb app_status_cb);
void     nhm_systemd_disconnect_stub(void);

#endif /* NHM_SYSTEMD_STUB_H */
