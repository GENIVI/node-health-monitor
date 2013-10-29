/* NHM - NodeHealthMonitor
 *
 * Definition of stubs for dlt
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DLT_STUB_H
#define DLT_STUB_H

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

#include <dlt/dlt.h> /* Include header of real dlt */

/*******************************************************************************
*
* Exported variables, constants and defines
*
*******************************************************************************/

int dlt_register_app_stub         (const char      *appid,
                                   const char      *description);
int dlt_check_library_version_stub(const char      *user_major_version,
                                   const char      *user_minor_version);
int dlt_register_context_stub     (DltContext      *handle,
                                   const char      *contextid,
                                   const char      *description);
int dlt_unregister_context_stub   (DltContext      *handle);
int dlt_unregister_app_stub       (void);
int dlt_user_log_write_start_stub (DltContext      *handle,
                                   DltContextData  *log,
                                   DltLogLevelType  loglevel);
int dlt_user_log_write_finish_stub(DltContextData  *log);
int dlt_user_log_write_string_stub(DltContextData  *log,
                                   const char      *text);
int dlt_user_log_write_int_stub   (DltContextData  *log,
                                   int              data);
int dlt_user_log_write_uint_stub  (DltContextData  *log,
                                   unsigned int     data);

#endif /* DLT_STUB_H */
