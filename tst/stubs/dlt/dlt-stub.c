/* NHM - NodeHealthMonitor
 *
 * Implementation of stubs for dlt
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

#include <dlt/dlt.h>                /* Header of real sd daemon */
#include <tst/stubs/dlt/dlt-stub.h> /* Header of stub sd daemon */

/*******************************************************************************
*
* Interfaces. Exported functions.
*
*******************************************************************************/

int
dlt_register_app_stub(const char *appid,
                      const char *description)
{
  return 0;
}

/**
 * dlt_check_library_version_stub:
 *
 * Stub for dlt_check_library_version()
 */
int
dlt_check_library_version_stub(const char *user_major_version,
                               const char *user_minor_version)
{
  return 0;
}

/**
 * dlt_register_context_stub:
 *
 * Stub for dlt_register_context()
 */
int
dlt_register_context_stub(DltContext *handle,
                          const char *contextid,
                          const char * description)
{
  return 0;
}

/**
 * dlt_unregister_context_stub:
 *
 * Stub for dlt_unregister_context()
 */
int
dlt_unregister_context_stub(DltContext *handle)
{
  return 0;
}

/**
 * dlt_unregister_app_stub:
 *
 * Stub for dlt_unregister_app()
 */
int
dlt_unregister_app_stub(void)
{
  return 0;
}

/**
 * dlt_user_log_write_start_stub:
 *
 * Stub for dlt_user_log_write_start()
 */
int
dlt_user_log_write_start_stub(DltContext     *handle,
                              DltContextData *log,
                              DltLogLevelType loglevel)
{
  return 0;
}

/**
 * dlt_user_log_write_finish_stub:
 *
 * Stub for dlt_user_log_write_finish()
 */
int
dlt_user_log_write_finish_stub(DltContextData *log)
{
  return 0;
}

/**
 * dlt_user_log_write_string_stub:
 *
 * Stub for dlt_user_log_write_string()
 */
int
dlt_user_log_write_string_stub(DltContextData *log,
                               const char     *text)
{
  return 0;
}

/**
 * dlt_user_log_write_int_stub:
 *
 * Stub for dlt_user_log_write_int()
 */
int
dlt_user_log_write_int_stub(DltContextData *log,
                            int             data)
{
  return 0;
}

/**
 * dlt_user_log_write_uint_stub:
 *
 * Stub for dlt_user_log_write_uint()
 */
int
dlt_user_log_write_uint_stub(DltContextData *log,
                             unsigned int    data)
{
  return 0;
}
