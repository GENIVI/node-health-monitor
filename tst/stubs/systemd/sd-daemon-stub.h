/* NHM - NodeHealthMonitor
 *
 * Definition of stubs for the sd daemon
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SD_DAEMON_STUB_H
#define SD_DAEMON_STUB_H

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

#include <gio/gio.h>
#include <systemd/sd-daemon.h> /* Include header of real sd daemon */

/*******************************************************************************
*
* Exported variables, constants and defines
*
*******************************************************************************/

extern gboolean sd_notify_stub_called;

/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

int sd_notify_stub(int unset_environment, const char *state);

#endif /* SD_DAEMON_STUB_H */
