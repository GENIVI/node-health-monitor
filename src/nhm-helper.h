#ifndef NHM_HELPER_H
#define NHM_HELPER_H

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

#include <dlt/dlt.h>       /* DLT traces */
#include <glib-2.0/glib.h> /* Use GTypes */


/*******************************************************************************
*
* Exported variables
*
*******************************************************************************/

/* Export a global trace context that can be used everywhere in NHM */
DLT_IMPORT_CONTEXT(nhm_helper_trace_ctx);


/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

gboolean nhm_helper_str_in_strv(const gchar *str,
                                gchar       *strv[]);

/* Parse systemd service values, added by HMC */
gboolean nhm_helper_str_in_GVariant(const gchar* str,
								GVariant* var);

#endif /* NHM_HELPER_H */
