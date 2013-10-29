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

/**
 * SECTION:nhm-unit-test
 * @title: NodeHealthMonitor (NHM) unit test
 * @short_description: Unit test for an automatic check of the NHM
 *
 * The unit test will stimulate the NHM and check for the expected reactions.
 */

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

/* Include glib to use gtypes */
#include <glib-2.0/glib.h>
#include <stdlib.h>

/* Include the stubbed main file of the NHM. Its functions will be tested! */
#include "nhm-main-test.h"


/*******************************************************************************
*
* Local variables and constants
*
*******************************************************************************/

/* There are no local variables, define or constants */


/*******************************************************************************
*
* Prototypes for file local functions (see implementation for description)
*
*******************************************************************************/

static gint nhm_test_main                (void);
static gint nhm_test_load_config         (void);
static gint nhm_test_connect_to_nsm      (void);
static gint nhm_test_nhm_bus_callbacks   (void);
static gint nhm_test_register_app_status (void);
static gint nhm_test_read_statistics     (void);
static gint nhm_test_userland_check      (void);
static gint nhm_test_watchdog            (void);
static gint nhm_test_handle_lc_request   (void);
static gint nhm_test_app_restart_request (void);
static gint nhm_test_is_dbus_alive       (void);
static gint nhm_test_on_sigterm          (void);


/*******************************************************************************
*
* Local (static) functions
*
*******************************************************************************/

/**
 * nhm_test_handle_lc_request:
 *
 * Test reaction of NHM on LC request.
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint nhm_test_app_restart_request(void)
{
  gint   retval               = 0;
  gchar* my_no_restart_apps[] = {"App1", "App2", NULL};

  no_restart_apps = my_no_restart_apps;

  /* Check 1: Request from App3 (not on black list) */
  nsm_dbus_lc_control_call_request_node_restart_sync_stub_set_error     = FALSE;
  nsm_dbus_lc_control_call_request_node_restart_sync_stub_out_ErrorCode = NsmErrorStatus_Ok;
  nhm_dbus_info_complete_request_node_restart_stub_ErrorStatus          = NsmErrorStatus_NotSet;
  nhm_main_request_node_restart_cb(NULL, NULL, "App3", NULL);
  retval = (   nhm_dbus_info_complete_request_node_restart_stub_ErrorStatus
            == NhmErrorStatus_Ok) ? 0 : -1;

  /* Check 2: Request from App1 (on black list) */
  if(retval == 0)
  {
    nhm_dbus_info_complete_request_node_restart_stub_ErrorStatus = NsmErrorStatus_NotSet;
    nhm_main_request_node_restart_cb(NULL, NULL, "App1", NULL);
    retval = (   nhm_dbus_info_complete_request_node_restart_stub_ErrorStatus
              == NhmErrorStatus_RestartNotPossible) ? 0 : -1;
  }

  no_restart_apps = NULL;

  return retval;
}

/**
 * nhm_test_handle_lc_request:
 *
 * Test reaction of NHM on LC request.
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint nhm_test_handle_lc_request(void)
{
  gint retval = 0;

  /* Check 1: Successful write of shutdown flag at "shutdown" request */
  pclKeyWriteData_stub_return   = sizeof(NhmNodeState);
  pclKeyWriteData_stub_WriteVal = 0;
  nhm_main_lc_request_cb(NULL, NULL, NSM_SHUTDOWNTYPE_FAST,  0, NULL);

  /* Check that NHM wrote 'NHM_NODESTATE_SHUTDOWN' to persistence */
  if(   ((NhmNodeState)     pclKeyWriteData_stub_WriteVal
        != NHM_NODESTATE_SHUTDOWN)
     || ((NsmErrorStatus_e) nsm_dbus_lc_consumer_complete_lifecycle_request_stub_ErrorCode
        != NsmErrorStatus_Ok))
  {
    retval = -1;
  }

  /* Check 2: Unsuccessful write of shutdown flag at "shutdown" request */
  if(retval == 0)
  {
    pclKeyWriteData_stub_return   = -1;
    pclKeyWriteData_stub_WriteVal = 0;
    nhm_main_lc_request_cb(NULL, NULL, NSM_SHUTDOWNTYPE_NORMAL,  0, NULL);

    /* Check that NHM wrote 'NHM_NODESTATE_SHUTDOWN' to persistence */
    if(   ((NhmNodeState)     pclKeyWriteData_stub_WriteVal
          != NHM_NODESTATE_SHUTDOWN)
       || ((NsmErrorStatus_e) nsm_dbus_lc_consumer_complete_lifecycle_request_stub_ErrorCode
          != NsmErrorStatus_Error))
    {
      retval = -1;
    }
  }

  /* Check 3: Successful write of shutdown flag at "runup" request */
  if(retval == 0)
  {
    pclKeyWriteData_stub_return   = sizeof(NhmNodeState);
    pclKeyWriteData_stub_WriteVal = 0;
    nhm_main_lc_request_cb(NULL, NULL, NSM_SHUTDOWNTYPE_RUNUP,  0, NULL);

    /* Check that NHM wrote 'NHM_NODESTATE_SHUTDOWN' to persistence */
    if(   ((NhmNodeState)     pclKeyWriteData_stub_WriteVal
          != NHM_NODESTATE_STARTED)
       || ((NsmErrorStatus_e) nsm_dbus_lc_consumer_complete_lifecycle_request_stub_ErrorCode
          != NsmErrorStatus_Ok))
    {
      retval = -1;
    }
  }

  /* Check 4: Unsuccessful write of shutdown flag at "runup" request */
  if(retval == 0)
  {
    pclKeyWriteData_stub_return   = -1;
    pclKeyWriteData_stub_WriteVal = 0;
    nhm_main_lc_request_cb(NULL, NULL, NSM_SHUTDOWNTYPE_RUNUP,  0, NULL);

    /* Check that NHM wrote 'NHM_NODESTATE_SHUTDOWN' to persistence */
    if(   ((NhmNodeState)     pclKeyWriteData_stub_WriteVal
          != NHM_NODESTATE_STARTED)
       || ((NsmErrorStatus_e) nsm_dbus_lc_consumer_complete_lifecycle_request_stub_ErrorCode
          != NsmErrorStatus_Error))
    {
      retval = -1;
    }
  }

  return retval;
}

/**
 * nhm_test_watchdog:
 *
 * Tests the WDOG triggering of the NHM
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint nhm_test_watchdog(void)
{
  gint retval = 0;

  sd_notify_stub_called = FALSE;
  nhm_main_timer_wdog_cb(NULL);
  retval = (sd_notify_stub_called == TRUE) ? 0 : -1;

  return retval;
}


static gint nhm_test_is_dbus_alive(void)
{
  gint            retval       = 0;
  NhmCheckedDbus *checked_dbus = g_new(NhmCheckedDbus, 1);
  GdbusConnectionCallSyncStubCalls  g_dbus_connection_call_sync_stub_calls[1];

  /* Check 1: No conn. obtained. Conn. can't be obtained. Call fails. */
  checked_dbus->bus_addr = NULL;
  checked_dbus->bus_conn = NULL;
  g_dbus_connection_new_for_address_sync_stub_set_error = TRUE;

  g_dbus_connection_call_sync_stub_control.count   = 1;
  g_dbus_connection_call_sync_stub_calls[0].method = "GetId";
  g_dbus_connection_call_sync_stub_calls[0].rval   = NULL;
  g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

  retval = nhm_main_is_dbus_alive(checked_dbus) == FALSE ? 0 : -1;

  /* Check 2: No conn. obtained. Conn. can be obtained. Call fails. */
  if(retval == 0)
  {
    checked_dbus->bus_addr = NULL;
    checked_dbus->bus_conn = NULL;
    g_dbus_connection_new_for_address_sync_stub_set_error = FALSE;

    g_dbus_connection_call_sync_stub_control.count   = 1;
    g_dbus_connection_call_sync_stub_calls[0].method = "GetId";
    g_dbus_connection_call_sync_stub_calls[0].rval   = NULL;
    g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

    retval = nhm_main_is_dbus_alive(checked_dbus) == FALSE ? 0 : -1;
  }

  /* Check 3: No conn. obtained. Conn. can be obtained. Call succeeds. */
  if(retval == 0)
  {
    checked_dbus->bus_addr = NULL;
    checked_dbus->bus_conn = NULL;
    g_dbus_connection_new_for_address_sync_stub_set_error = FALSE;

    g_dbus_connection_call_sync_stub_control.count   = 1;
    g_dbus_connection_call_sync_stub_calls[0].method = "GetId";
    g_dbus_connection_call_sync_stub_calls[0].rval   = g_variant_new("()");
    g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

    retval = nhm_main_is_dbus_alive(checked_dbus) == TRUE ? 0 : -1;
  }

  /* Check 4: Conn. obtained. Call succeeds. */
  if(retval == 0)
  {
    checked_dbus->bus_addr = NULL;
    checked_dbus->bus_conn = g_object_new(G_TYPE_DBUS_CONNECTION, NULL);

    g_dbus_connection_new_for_address_sync_stub_set_error = FALSE;

    g_dbus_connection_call_sync_stub_control.count   = 1;
    g_dbus_connection_call_sync_stub_calls[0].method = "GetId";
    g_dbus_connection_call_sync_stub_calls[0].rval   = g_variant_new("()");
    g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

    retval = nhm_main_is_dbus_alive(checked_dbus) == TRUE ? 0 : -1;

    g_object_unref(checked_dbus->bus_conn);
    checked_dbus->bus_conn = NULL;
  }

  /* Check 5: Conn. obtained. Call fails. */
  if(retval == 0)
  {
    checked_dbus->bus_addr = NULL;
    checked_dbus->bus_conn = g_object_new(G_TYPE_DBUS_CONNECTION, NULL);

    g_dbus_connection_new_for_address_sync_stub_set_error = FALSE;

    g_dbus_connection_call_sync_stub_control.count   = 1;
    g_dbus_connection_call_sync_stub_calls[0].method = "GetId";
    g_dbus_connection_call_sync_stub_calls[0].rval   = NULL;
    g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

    retval = nhm_main_is_dbus_alive(checked_dbus) == FALSE ? 0 : -1;

    g_object_unref(checked_dbus->bus_conn);
    checked_dbus->bus_conn = NULL;
  }

  nhm_main_free_checked_dbus(checked_dbus);

  return retval;
}


/**
 * nhm_test_userland_check:
 *
 * Tests the userland check functionality of the NHM.
 *
 * Returns always 0, because NHM shows no reaction yet.
 */
static gint nhm_test_userland_check(void)
{
  gchar          *my_monitored_files[]    = {"missing_file",          NULL};
  gchar          *my_monitored_progs[]    = {"invalid_prog",          NULL};
  gchar          *my_monitored_procs[]    = {"/usr/bin/invalid_proc", NULL};
  NhmCheckedDbus  my_checked_dbus         = {NULL, NULL};

  /* Check 1: No monitored files. No monitored progs. No monitored procs. No monitored dbus */
  monitored_files = NULL;
  monitored_progs = NULL;
  monitored_procs = NULL;
  checked_dbusses = NULL;

  nhm_main_timer_userland_check_cb(NULL);

  nhm_main_free_check_objects();
  nhm_main_free_config_objects();

  /* Check 2: No monitored files. No monitored progs. Monitored procs. nok. No monitored dbus. */
  monitored_files = NULL;
  monitored_progs = NULL;
  monitored_procs = g_strdupv(my_monitored_procs);
  checked_dbusses = NULL;

  nhm_main_timer_userland_check_cb(NULL);

  nhm_main_free_check_objects();
  nhm_main_free_config_objects();

  /* Check 3: No monitored files. No monitored progs. Monitored procs. ok. No monitored dbus. */
  monitored_files       = NULL;
  monitored_progs       = NULL;
  my_monitored_procs[0] = "valid_proc";
  monitored_procs       = g_strdupv(my_monitored_procs);
  checked_dbusses       = NULL;

  nhm_main_timer_userland_check_cb(NULL);

  nhm_main_free_check_objects();
  nhm_main_free_config_objects();

  /* Check 4: No monitored files. monitored progs nok. Monitored procs. ok. No monitored dbus. */
  monitored_files       = NULL;
  monitored_progs       = g_strdupv(my_monitored_progs);
  monitored_procs       = g_strdupv(my_monitored_procs);
  checked_dbusses       = NULL;
  nhm_main_timer_userland_check_cb(NULL);

  nhm_main_free_check_objects();
  nhm_main_free_config_objects();

  /* Check 5: No monitored files. monitored progs ok. Monitored procs. ok. No monitored dbus. */
  monitored_files       = NULL;
  my_monitored_progs[0] = "/usr/bin/valid_prog1";
  monitored_progs       = g_strdupv(my_monitored_progs);
  monitored_procs       = g_strdupv(my_monitored_procs);
  checked_dbusses       = NULL;
  nhm_main_timer_userland_check_cb(NULL);

  nhm_main_free_check_objects();
  nhm_main_free_config_objects();

  /* Check 6: monitored files nok. monitored progs ok. Monitored procs. ok. No monitored dbus. */
  monitored_files       = g_strdupv(my_monitored_files);
  monitored_progs       = g_strdupv(my_monitored_progs);
  monitored_procs       = g_strdupv(my_monitored_procs);
  checked_dbusses       = NULL;
  nhm_main_timer_userland_check_cb(NULL);

  nhm_main_free_check_objects();
  nhm_main_free_config_objects();

  /* Check 7: monitored files ok. monitored progs ok. Monitored procs. ok. No monitored dbus. */
  my_monitored_files[0] = "valid_file";
  monitored_files       = g_strdupv(my_monitored_files);
  monitored_progs       = g_strdupv(my_monitored_progs);
  monitored_procs       = g_strdupv(my_monitored_procs);
  checked_dbusses       = NULL;
  nhm_main_timer_userland_check_cb(NULL);

  nhm_main_free_check_objects();
  nhm_main_free_config_objects();

  /* Check 8: monitored files ok. monitored progs ok. Monitored procs. ok. Monitored dbus nok */
  monitored_files       = g_strdupv(my_monitored_files);
  monitored_progs       = g_strdupv(my_monitored_progs);
  monitored_procs       = g_strdupv(my_monitored_procs);
  checked_dbusses       = g_ptr_array_new();

  g_ptr_array_add(checked_dbusses, (gpointer) &my_checked_dbus);
  g_dbus_connection_new_for_address_sync_stub_set_error = TRUE;
  g_dbus_connection_new_for_address_sync_stub_set_error = TRUE;
  nhm_main_timer_userland_check_cb(NULL);

  nhm_main_free_check_objects();
  nhm_main_free_config_objects();

  /* Check 9: monitored files ok. monitored progs ok. Monitored procs. ok. Monitored dbus ok */
  monitored_files       = g_strdupv(my_monitored_files);
  monitored_progs       = g_strdupv(my_monitored_progs);
  monitored_procs       = g_strdupv(my_monitored_procs);
  checked_dbusses       = g_ptr_array_new();

  g_ptr_array_add(checked_dbusses, (gpointer) &my_checked_dbus);
  g_dbus_connection_new_for_address_sync_stub_set_error = FALSE;
  g_dbus_connection_new_for_address_sync_stub_set_error = FALSE;
  nhm_main_timer_userland_check_cb(NULL);

  nhm_main_free_check_objects();
  nhm_main_free_config_objects();

  return 0;
}


/**
 * nhm_test_read_statistics:
 *
 * Tests the read statistics dbus interface of the NHM.
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint nhm_test_read_statistics(void)
{
  guint               app_idx                = 0;
  NhmLcInfo           *lc_info[3]            = {0};
  NhmFailedApp        *lc_apps[5]            = {0};
  NhmCurrentFailedApp *current_failed_app[3] = {0};
  gint                 retval                = 0;

  /*
   * Create initial nodeinfo for the test:
   *
   * LC1: NHM_NODESTATE_SHUTDOWN. (App1, 3), (App2, 4), (App3, 5)
   * LC2: NHM_NODESTATE_STARTED.  (App1, 4), (App2, 5)
   * LC3: NHM_NODESTATE_SHUTDOWN. NULL
   */

  /* Create five apps that will be assigned to the LCs */
  lc_apps[0]            = g_new(NhmFailedApp, 1);
  lc_apps[0]->name      = g_strdup("App1");
  lc_apps[0]->failcount = 3;

  lc_apps[1]            = g_new(NhmFailedApp, 1);
  lc_apps[1]->name      = g_strdup("App2");
  lc_apps[1]->failcount = 4;

  lc_apps[2]            = g_new(NhmFailedApp, 1);
  lc_apps[2]->name      = g_strdup("App3");
  lc_apps[2]->failcount = 5;

  lc_apps[3]            = g_new(NhmFailedApp, 1);
  lc_apps[3]->name      = g_strdup("App1");
  lc_apps[3]->failcount = 4;

  lc_apps[4]            = g_new(NhmFailedApp, 1);
  lc_apps[4]->name      = g_strdup("App2");
  lc_apps[4]->failcount = 5;

  /* Create three LCs */
  lc_info[0]              = g_new(NhmLcInfo, 1);
  lc_info[0]->start_state = NHM_NODESTATE_SHUTDOWN;
  lc_info[0]->failed_apps = NULL;

  lc_info[1]              = g_new(NhmLcInfo, 1);
  lc_info[1]->start_state = NHM_NODESTATE_STARTED;
  lc_info[1]->failed_apps = NULL;

  lc_info[2]              = g_new(NhmLcInfo, 1);
  lc_info[2]->start_state = NHM_NODESTATE_SHUTDOWN;
  lc_info[2]->failed_apps = NULL;

  /* Add lc_apps[0], lc_apps[1] and lc_apps[2] to list of LC1 */
  lc_info[0]->failed_apps = g_slist_append(lc_info[0]->failed_apps, lc_apps[0]);
  lc_info[0]->failed_apps = g_slist_append(lc_info[0]->failed_apps, lc_apps[1]);
  lc_info[0]->failed_apps = g_slist_append(lc_info[0]->failed_apps, lc_apps[2]);

  /* Add lc_apps[4] and lc_apps[5] to list of LC2*/
  lc_info[1]->failed_apps = g_slist_append(lc_info[1]->failed_apps, lc_apps[3]);
  lc_info[1]->failed_apps = g_slist_append(lc_info[1]->failed_apps, lc_apps[4]);

  /* Create array and add LCs */
  nodeinfo = g_ptr_array_new_with_free_func(&nhm_main_free_lc_info);
  g_ptr_array_add(nodeinfo, lc_info[0]);
  g_ptr_array_add(nodeinfo, lc_info[1]);
  g_ptr_array_add(nodeinfo, lc_info[2]);

  /*
   * Create initial list of current failed apps: App1, App2, app3
   */
  current_failed_app[0]       = g_new(NhmCurrentFailedApp, 1);
  current_failed_app[0]->name = g_strdup("App1");

  current_failed_app[1]       = g_new(NhmCurrentFailedApp, 1);
  current_failed_app[1]->name = g_strdup("App2");

  current_failed_app[2]       = g_new(NhmCurrentFailedApp, 1);
  current_failed_app[2]->name = g_strdup("App3");

  current_failed_apps = NULL;
  for(app_idx = 0; app_idx < sizeof(current_failed_app)/sizeof(NhmCurrentFailedApp); app_idx++)
  {
    current_failed_apps = g_slist_append(current_failed_apps, current_failed_app[app_idx]);
  }

  /* Check 1: Request info for "App1" for up to 5 LCs => 3 LCs are delivered */
  max_lc_count = 5;

  nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount = 0;
  nhm_dbus_info_complete_read_statistics_stub_TotalFailures    = 0;
  nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  = 0;

  nhm_main_read_statistics_cb(NULL, NULL, "App1", NULL);

  retval = (   (nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount == 3)
            && (nhm_dbus_info_complete_read_statistics_stub_TotalFailures    == 7)
            && (nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  == 3)) ? 0 : -1;

  /* Check 2: Request info for "App1" for up to 1 LCs => 1 LC is delivered */
  if(retval == 0)
  {
    max_lc_count = 0;

    nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalFailures    = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  = 0;

    nhm_main_read_statistics_cb(NULL, NULL, "App1", NULL);

    retval = (   (nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount == 3)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalFailures    == 3)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  == 1)) ? 0 : -1;
  }

  /* Check 3: Request node info for up to 5 LCs => 3 LCs are delivered */
  if(retval == 0)
  {
    max_lc_count = 5;

    nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalFailures    = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  = 0;

    nhm_main_read_statistics_cb(NULL, NULL, "", NULL);

    retval = (   (nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount == 3)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalFailures    == 1)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  == 3)) ? 0 : -1;
  }

  /* Check 4: Request node info for up to 2 LCs => 2 LCs are delivered */
  if(retval == 0)
  {
    max_lc_count = 1;

    nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalFailures    = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  = 0;

    nhm_main_read_statistics_cb(NULL, NULL, "", NULL);

    retval = (   (nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount == 3)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalFailures    == 1)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  == 2)) ? 0 : -1;
  }

  /* Check 5: Request app info for App4 for up to 2 LCs => 2 LCs are delivered */
  if(retval == 0)
  {
    max_lc_count = 1;

    nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalFailures    = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  = 0;

    nhm_main_read_statistics_cb(NULL, NULL, "App4", NULL);

    retval = (   (nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount == 0)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalFailures    == 0)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  == 2)) ? 0 : -1;
  }

  /* Check 6: No current failed apps. Request node info for 2 LCs */
  if(retval == 0)
  {
    max_lc_count = 1;

    if(current_failed_apps != NULL)
    {
      g_slist_free_full(current_failed_apps, &nhm_main_free_current_failed_app);
      current_failed_apps = NULL;
    }

    nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalFailures    = 0;
    nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  = 0;

    nhm_main_read_statistics_cb(NULL, NULL, "", NULL);

    retval = (   (nhm_dbus_info_complete_read_statistics_stub_CurrentFailCount == 0)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalFailures    == 1)
              && (nhm_dbus_info_complete_read_statistics_stub_TotalLifecycles  == 2)) ? 0 : -1;
  }

  /* Clean up objects after test */
  if(current_failed_apps != NULL)
  {
    g_slist_free_full(current_failed_apps, &nhm_main_free_current_failed_app);
  }

  g_ptr_array_unref(nodeinfo);

  return retval;
}

/**
 * nhm_test_register_app_status:
 *
 * Tests the register app status dbus interface of the NHM.
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint
nhm_test_register_app_status(void)
{
  gint      retval           = 0;
  NhmLcInfo *initial_lc_info = g_new(NhmLcInfo, 1);
  gchar     *rmcmd           = NULL;

  initial_lc_info->start_state = NHM_NODESTATE_SHUTDOWN;
  initial_lc_info->failed_apps = NULL;

  nodeinfo = g_ptr_array_new_with_free_func(&nhm_main_free_lc_info);
  g_ptr_array_add(nodeinfo, initial_lc_info);
  current_failed_apps = NULL;

  /* Check 1: App1 fails. NSM nok => App1 in current_failed_apps */
  nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error = TRUE;
  nhm_main_register_app_status_cb(NULL, NULL, "App1", NhmAppStatus_Failed, NULL);
  retval = (nhm_main_find_current_failed_app("App1") != NULL) ? 0 : -1;

  /* Check 2: App2 fails. NSM ok  => App2 in current_failed_apps */
  if(retval == 0)
  {
    nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error = FALSE;
    nhm_main_register_app_status_cb(NULL, NULL, "App2", NhmAppStatus_Failed, NULL);
    retval = (nhm_main_find_current_failed_app("App2") != NULL) ? 0 : -1;
  }

  /* Check 3: App1 becomes valid. NSM ok => App1 not in current_failed_apps */
  if(retval == 0)
  {
    nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error = FALSE;
    nhm_main_register_app_status_cb(NULL, NULL, "App1", NhmAppStatus_Ok, NULL);
    retval = (nhm_main_find_current_failed_app("App1") == NULL) ? 0 : -1;
  }

  /* Check 4: App2 becomes valid. NSM ok => App2 not in current_failed_apps */
  if(retval == 0)
  {
    nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error = FALSE;
    nhm_main_register_app_status_cb(NULL, NULL, "App2", NhmAppStatus_Ok, NULL);
    retval = (nhm_main_find_current_failed_app("App2") == NULL) ? 0 : -1;
  }

  /* Check 5: App1 becomes valid. NSM ok => App1 not in current_failed_apps */
  if(retval == 0)
  {
    nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error = FALSE;
    nhm_main_register_app_status_cb(NULL, NULL, "App1", NhmAppStatus_Ok, NULL);
    retval = (nhm_main_find_current_failed_app("App1") == NULL) ? 0 : -1;
  }

  /* Check 6: App1 fails. NSM ok => App1 in current_failed_apps */
  if(retval == 0)
  {
    nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error = FALSE;
    nhm_main_register_app_status_cb(NULL, NULL, "App1", NhmAppStatus_Failed, NULL);
    retval = (nhm_main_find_current_failed_app("App1") != NULL) ? 0 : -1;
  }

  /* Check 7: App1 fails. NSM ok => App1 in current_failed_apps */
  if(retval == 0)
  {
    nsm_dbus_lc_control_call_set_app_health_status_sync_stub_set_error = FALSE;
    nhm_main_register_app_status_cb(NULL, NULL, "App1", NhmAppStatus_Failed, NULL);
    retval = (nhm_main_find_current_failed_app("App1") != NULL) ? 0 : -1;
  }

  /* Clean up objects created during the test */
  if(current_failed_apps != NULL)
  {
    g_slist_free_full(current_failed_apps, &nhm_main_free_current_failed_app);
  }

  g_ptr_array_unref(nodeinfo);

  rmcmd = g_strdup_printf("rm %s", NHM_LC_DATA_FILE);
  system(rmcmd);
  g_free(rmcmd);

  return retval;
}


/**
 * nhm_test_nhm_bus_callbacks:
 *
 * Tests the bus connection callbacks for the NHM dbus connection.
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint
nhm_test_nhm_bus_callbacks(void)
{
  gint             retval  = 0;
  GDBusConnection *busconn = NULL;

  /* Check 1: BusAcquired. Interface export ok => Mainloop should not be quit */
  busconn = g_object_new(G_TYPE_DBUS_CONNECTION, NULL);
  g_main_loop_quit_stub_called                    = FALSE;
  g_dbus_interface_skeleton_export_stub_set_error = FALSE;
  nhm_main_bus_acquired_cb(busconn, NULL, NULL);
  retval = (g_main_loop_quit_stub_called == FALSE) ? 0 : -1;
  nhm_main_free_nhm_objects();
  g_object_unref(busconn);

  /* Check 2: BusAcquired. IF export fails => Mainloop should quit */
  if(retval == 0)
  {
    busconn = g_object_new(G_TYPE_DBUS_CONNECTION, NULL);
    g_main_loop_quit_stub_called                    = FALSE;
    g_dbus_interface_skeleton_export_stub_set_error = TRUE;
    nhm_main_bus_acquired_cb(busconn, NULL, NULL);
    retval = (g_main_loop_quit_stub_called == TRUE) ? 0 : -1;
    nhm_main_free_nhm_objects();
    g_object_unref(busconn);
  }

  /* Check 3: NameAcquired. No UL checks => No timer scheduled */
  if(retval == 0)
  {
    nodeinfo = g_ptr_array_new_with_free_func(&nhm_main_free_lc_info);
    ul_chk_interval = 0;

    g_timeout_add_seconds_called          = FALSE;
    g_timeout_add_seconds_called_interval = 0;

    nhm_main_name_acquired_cb(NULL, NULL, NULL);

    retval = (g_timeout_add_seconds_called == FALSE) ? 0 : -1;
    g_ptr_array_unref(nodeinfo);
  }

  /* Check 4: NameAcquired. UL check enabled => Timer is scheduled */
  if(retval == 0)
  {
    nodeinfo = g_ptr_array_new_with_free_func(&nhm_main_free_lc_info);
    ul_chk_interval = 10000;

    g_timeout_add_seconds_called          = FALSE;
    g_timeout_add_seconds_called_interval = 0;

    nhm_main_name_acquired_cb(NULL, NULL, NULL);

    retval = (    (g_timeout_add_seconds_called          == TRUE )
               && (g_timeout_add_seconds_called_interval == 10000)) ? 0 : -1;
    g_ptr_array_unref(nodeinfo);
  }

  /* Check 5: NameLost. Connection not established => Quit Mainloop */
  if(retval == 0)
  {
    g_main_loop_quit_stub_called = FALSE;
    nhm_main_name_lost_cb(NULL, NULL, NULL);
    retval = (g_main_loop_quit_stub_called == TRUE) ? 0 : -1;
  }

  /* Check 6: NameLost. Name lost => Quit Mainloop */
  if(retval == 0)
  {
    g_main_loop_quit_stub_called = FALSE;
    nhm_main_name_lost_cb((GDBusConnection*) 0x00000001, NULL, NULL);
    retval = (g_main_loop_quit_stub_called == TRUE) ? 0 : -1;
  }

  return retval;
}


/**
 * nhm_test_connect_to_nsm:
 *
 * Will test what happens if there is an error when connecting to the NSM.
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint
nhm_test_connect_to_nsm(void)
{
  gint retval = 0;

  /* Check 1: Bus connection fails */
  if(retval == 0)
  {
    g_bus_get_sync_set_error = TRUE;
    retval = (nhm_main_connect_to_nsm() == FALSE) ? 0 : -1;
    nhm_main_free_nsm_objects();
  }

  /* Check 2: Bus connection: ok. LifecycleControl: nok */
  if(retval == 0)
  {
    g_bus_get_sync_set_error                          = FALSE;
    nsm_dbus_lc_control_proxy_new_sync_stub_set_error = TRUE;
    retval = (nhm_main_connect_to_nsm() == FALSE) ? 0 : -1;
    nhm_main_free_nsm_objects();
  }

  /* Check 3: Bus connection: ok. LifecycleControl: ok. NodeStateConsumer: nok */
  if(retval == 0)
  {
    g_bus_get_sync_set_error                          = FALSE;
    nsm_dbus_lc_control_proxy_new_sync_stub_set_error = FALSE;
    nsm_dbus_consumer_proxy_new_sync_stub_set_error   = TRUE;
    retval = (nhm_main_connect_to_nsm() == FALSE) ? 0 : -1;
    nhm_main_free_nsm_objects();
  }

  /* Check 4: Bus connection: ok. LifecycleControl: ok. NodeStateConsumer: ok. Client reg: ok.  IF export: nok */
  if(retval == 0)
  {
    g_bus_get_sync_set_error                          = FALSE;
    nsm_dbus_lc_control_proxy_new_sync_stub_set_error = FALSE;
    nsm_dbus_consumer_proxy_new_sync_stub_set_error   = FALSE;
    g_dbus_interface_skeleton_export_stub_set_error   = TRUE;
    retval = (nhm_main_connect_to_nsm() == FALSE) ? 0 : -1;
    nhm_main_free_nsm_objects();
  }

  /* Check 5: Bus connection: ok. LifecycleControl: ok. NodeStateConsumer: ok. Client reg: ok. IF export: ok. Reg: nok I */
  if(retval == 0)
  {
    g_bus_get_sync_set_error                                            = FALSE;
    nsm_dbus_lc_control_proxy_new_sync_stub_set_error                   = FALSE;
    nsm_dbus_consumer_proxy_new_sync_stub_set_error                     = FALSE;
    g_dbus_interface_skeleton_export_stub_set_error                     = FALSE;
    nsm_dbus_consumer_call_register_shutdown_client_sync_stub_set_error = TRUE;
    retval = (nhm_main_connect_to_nsm() == FALSE) ? 0 : -1;
    nhm_main_free_nsm_objects();
  }

  /* Check 6: Bus connection: ok. LifecycleControl: ok. NodeStateConsumer: ok. Client reg: ok. IF export: ok. Reg: nok II */
  if(retval == 0)
  {
    g_bus_get_sync_set_error                                                = FALSE;
    nsm_dbus_lc_control_proxy_new_sync_stub_set_error                       = FALSE;
    nsm_dbus_consumer_proxy_new_sync_stub_set_error                         = FALSE;
    g_dbus_interface_skeleton_export_stub_set_error                         = FALSE;
    nsm_dbus_consumer_call_register_shutdown_client_sync_stub_set_error     = FALSE;
    nsm_dbus_consumer_call_register_shutdown_client_sync_stub_out_ErrorCode = NsmErrorStatus_Error;
    retval = (nhm_main_connect_to_nsm() == FALSE) ? 0 : -1;
    nhm_main_free_nsm_objects();
  }

  /* Check 7: Bus connection: ok. LifecycleControl: ok. NodeStateConsumer: ok. Client reg: ok. IF export: ok. Reg: ok */
  if(retval == 0)
  {
    g_bus_get_sync_set_error                                                = FALSE;
    nsm_dbus_lc_control_proxy_new_sync_stub_set_error                       = FALSE;
    nsm_dbus_consumer_proxy_new_sync_stub_set_error                         = FALSE;
    g_dbus_interface_skeleton_export_stub_set_error                         = FALSE;
    nsm_dbus_consumer_call_register_shutdown_client_sync_stub_set_error     = FALSE;
    nsm_dbus_consumer_call_register_shutdown_client_sync_stub_out_ErrorCode = NsmErrorStatus_Ok;
    retval = (nhm_main_connect_to_nsm() == TRUE) ? 0 : -1;
    nhm_main_free_nsm_objects();
  }

  return retval;
}


/**
 * nhm_test_load_config:
 *
 * Will test loading of different formated config files.
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint
nhm_test_load_config(void)
{
  gint retval = 0;

  /* Check 1: Check if the default config file is correctly loaded */
  system("cp ../cfg/node-health-monitor.conf ./");

  nhm_main_load_config();

  retval =     (max_lc_count                      == 5   )
            && (max_failed_apps                   == 8   )
            && (no_restart_apps                   == NULL)
            && (ul_chk_interval                   == 0   )
            && (monitored_files                   == NULL)
            && (monitored_procs                   == NULL)
            && (monitored_progs                   == NULL) ? 0 : -1;

  nhm_main_free_config_objects();

  /* Check 2: Check handling if unsigned setting contains neg. value */
  if(retval == 0)
  {
    system("sed -i 's/historic_lc_count = 5/historic_lc_count = -1/g' node-health-monitor.conf");

    nhm_main_load_config();

    retval =     (max_lc_count                        == 0   )
              && (max_failed_apps                     == 8   )
              && (no_restart_apps                     == NULL)
              && (ul_chk_interval                     == 0   )
              && (monitored_files                     == NULL)
              && (monitored_procs                     == NULL)
              && (monitored_progs                     == NULL) ? 0 : -1;

    nhm_main_free_config_objects();
  }

  /* Check 3: Check handling of missing unsigned keys */
  if(retval == 0)
  {
    system("sed -i 's/historic_lc_count = -1//g' node-health-monitor.conf");

    nhm_main_load_config();

    retval =     (max_lc_count                        == 0   )
              && (max_failed_apps                     == 8   )
              && (no_restart_apps                     == NULL)
              && (ul_chk_interval                     == 0   )
              && (monitored_files                     == NULL)
              && (monitored_procs                     == NULL)
              && (monitored_progs                     == NULL) ? 0 : -1;

    nhm_main_free_config_objects();
  }

  /* Check 4: Check handling of missing string keys */
  if(retval == 0)
  {
    system("sed -i 's/no_restart_apps =//g' node-health-monitor.conf");

    nhm_main_load_config();

    retval =     (max_lc_count                        == 0   )
              && (max_failed_apps                     == 8   )
              && (no_restart_apps                     == NULL)
              && (ul_chk_interval                     == 0   )
              && (monitored_files                     == NULL)
              && (monitored_procs                     == NULL)
              && (monitored_progs                     == NULL) ? 0 : -1;

    nhm_main_free_config_objects();
  }

  /* Check 5: Load some valid values */
  if(retval == 0)
  {
    system("sed -i 's/ul_chk_interval = 0/ul_chk_interval = 10/g'        node-health-monitor.conf");
    system("sed -i 's/monitored_files =/monitored_files = File1;File2/g' node-health-monitor.conf");

    nhm_main_load_config();

    retval =     (max_lc_count                        == 0   )
              && (max_failed_apps                     == 8   )
              && (no_restart_apps                     == NULL)
              && (ul_chk_interval                     == 10  )
              && (monitored_files                     != NULL)
              && (strcmp(monitored_files[0], "File1") == 0   )
              && (strcmp(monitored_files[1], "File2") == 0   )
              && (monitored_files[2]                  == NULL)
              && (monitored_procs                     == NULL)
              && (monitored_progs                     == NULL) ? 0 : -1;

    nhm_main_free_config_objects();
  }

  system("rm -rf node-health-monitor.conf");

  return retval;
}


/**
 * nhm_test_main:
 *
 * Will check the main function and its embedded calls to nhm_main_load_config
 * and nhm_main_nsm_connect.
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint
nhm_test_main(void)
{
  gint retval = -1;

  /* Preparation for 'nhm_main_nsm_connect':
   * Bus connection: ok. LifecycleControl: ok. NodeStateConsumer: ok. Client reg: ok. IF export: ok. Reg: ok
   * => nhm_main_nsm_connect returns 'TRUE', should nhm_main proceed
   */
  g_bus_get_sync_set_error                                                = FALSE;
  nsm_dbus_lc_consumer_proxy_new_sync_stub_set_error                      = FALSE;
  nsm_dbus_consumer_proxy_new_sync_stub_set_error                         = FALSE;
  g_dbus_interface_skeleton_export_stub_set_error                         = FALSE;
  nsm_dbus_consumer_call_register_shutdown_client_sync_stub_set_error     = FALSE;
  nsm_dbus_consumer_call_register_shutdown_client_sync_stub_out_ErrorCode = NsmErrorStatus_Ok;

  /* Call main */
  retval = (nhm_main() == EXIT_FAILURE) ? 0 : -1;

  /* Preparation for 'nhm_main_nsm_connect':
   * Bus connection: nok.
   * => nhm_main_nsm_connect returns 'FALSE', should nhm_main fail
   */
  if(retval == 0)
  {
    mainreturn = EXIT_SUCCESS;
    g_bus_get_sync_set_error = TRUE;

    /* Call main */
    retval = (nhm_main() == EXIT_FAILURE) ? 0 : -1;
  }

  return retval;
}

/**
 * nhm_test_on_sigterm:
 *
 * Will check the 'nhm_test_on_sigterm' function.
 *
 * Returns 0, if test succeeds. Otherwise, it will return -1.
 */
static gint
nhm_test_on_sigterm(void)
{
  g_main_loop_quit_stub_called = FALSE;

  nhm_main_on_sigterm(NULL);

  return (   (g_main_loop_quit_stub_called == TRUE)
          && (mainreturn                   == EXIT_SUCCESS )) ? 0 : -1;
}


/*******************************************************************************
*
* Interfaces. Exported functions.
*
*******************************************************************************/

/**
 * main:
 *
 * Main function of the unit test.
 *
 * Return value: 0 if all tests succeeded. Otherwise -1.
 */
int
main(void)
{
  int retval = 0;

  /* Test 1: Test the main function of the NHM */
  retval = (retval == 0) ? nhm_test_main()        : -1;

  /* Test 2: Test loading and handling of configuration */
  retval = (retval == 0) ? nhm_test_load_config() : -1;

  /* Test 3: Test NSM connection */
  retval = (retval == 0) ? nhm_test_connect_to_nsm() : -1;

  /* Test 4: Test NHM bus connection callbacks */
  retval = (retval == 0) ? nhm_test_nhm_bus_callbacks() : -1;

  /* Test 5: Test NHM register_app_status dbus interface */
  retval = (retval == 0) ? nhm_test_register_app_status() : -1;

  /* Test 6: Test NHM read_statistics dbus interface */
  retval = (retval == 0) ? nhm_test_read_statistics() : -1;

  /* Test 7: Test NHM request node restart dbus interface */
  retval = (retval == 0) ? nhm_test_app_restart_request() : -1;

  /* Test 8: Test NHM user land check functionality */
  retval = (retval == 0) ? nhm_test_userland_check() : -1;

  /* Test 9: Test NHM WDOG handling */
  retval = (retval == 0) ? nhm_test_watchdog() : -1;

  /* Test 10: Test NHM LC request handling */
  retval = (retval == 0) ? nhm_test_handle_lc_request() : -1;

  /* Test 11: Test dbus alive */
  retval = (retval == 0) ? nhm_test_is_dbus_alive() : -1;

  /* Test 12: Test SIGTERM */
  retval = (retval == 0) ? nhm_test_on_sigterm() : -1;

  return retval;
}
