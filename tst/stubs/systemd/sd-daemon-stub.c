/* NHM - NodeHealthMonitor
 *
 * Implementation of stubs for the sd daemon
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
#include <systemd/sd-daemon.h>                /* Header of real sd daemon */
#include <tst/stubs/systemd/sd-daemon-stub.h> /* Header of stub sd daemon */

/*******************************************************************************
*
* Exported variables and constants
*
*******************************************************************************/

gboolean sd_notify_stub_called = FALSE;

/*******************************************************************************
*
* Interfaces. Exported functions.
*
*******************************************************************************/

/**
 * sd_notify_stub:
 *
 * Stub for sd_notify()
 */
int
sd_notify_stub(int         unset_environment,
               const char *state)
{
  sd_notify_stub_called = TRUE;

  return 0;
}
