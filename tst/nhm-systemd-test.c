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
 * @short_description: Unit test for an automatic check of the NHM systemd
 *                     observation.
 *
 * The unit test will stimulate the NHM systemd observation and check for the
 * expected reactions.
 */


/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

/* System header files                   */
#include <stdio.h>         /* NULL       */
#include <glib-2.0/glib.h> /* use gtypes */

/* Include the stubbed main file of the NHM. Its functions will be tested! */
#include "nhm-systemd-test.h"


/*******************************************************************************
*
* Local variables and constants
*
*******************************************************************************/

/* Variables to check callback on unit state change */
static gboolean        nhm_systemd_test_app_state_changed_cb_called = FALSE;
static gchar          *nhm_systemd_test_app_state_changed_cb_name   = NULL;
static NhmAppStatus_e  nhm_systemd_test_app_state_changed_cb_status = NhmAppStatus_Ok;


/*******************************************************************************
*
* Prototypes for file local functions (see implementation for description)
*
*******************************************************************************/


/*******************************************************************************
*
* Local (static) functions
*
*******************************************************************************/

/**
 * nhm_systemd_test_app_state_changed_cb:
 * @name:   Name of the application, whose state changed
 * @status: New status of the application.
 *
 * The function is not  a test case, but a callback that will be used during
 * the tests.
 */
static void
nhm_systemd_test_app_state_changed_cb(const gchar    *name,
                                      NhmAppStatus_e  status)
{
  /* Remember that callback was called and store passed parameters */
  nhm_systemd_test_app_state_changed_cb_called = TRUE;
  nhm_systemd_test_app_state_changed_cb_name   = (gchar*) name;
  nhm_systemd_test_app_state_changed_cb_status = status;
}


/**
 * nhm_test_systemd_connect:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_connect() function.
 */
static gint
nhm_test_systemd_connect(void)
{
  gint                              retval   = 0;
  NhmSystemdAppStatusCb             callback = NULL;
  GdbusConnectionCallSyncStubCalls  g_dbus_connection_call_sync_stub_calls[3];
  GVariantBuilder                  *builder;

  /* Check 1: Callback nok. */
  callback = NULL;
  retval = (nhm_systemd_connect(callback) == FALSE) ? 0 : -1;

  /* Check 2: Callback ok. Bus conn. nok. */
  if(retval == 0)
  {
    callback = &nhm_systemd_test_app_state_changed_cb;
    g_bus_get_sync_set_error = TRUE;

    retval = (nhm_systemd_connect(callback) == FALSE) ? 0 : -1;
  }

  /* Check 3: Callback ok. Bus conn. ok. Subscribe nok. */
  if(retval == 0)
  {
    callback = &nhm_systemd_test_app_state_changed_cb;
    g_bus_get_sync_set_error = FALSE;

    g_dbus_connection_call_sync_stub_control.count    = 1;
    g_dbus_connection_call_sync_stub_calls[0].method  = "Subscribe";
    g_dbus_connection_call_sync_stub_calls[0].rval    = NULL;
    g_dbus_connection_call_sync_stub_control.calls    = g_dbus_connection_call_sync_stub_calls;

    retval = (nhm_systemd_connect(callback) == FALSE) ? 0 : -1;
  }

  /* Check 4: Callback ok. Bus conn. ok. Subscribe ok. ListUnits nok */
  if(retval == 0)
  {
    callback = &nhm_systemd_test_app_state_changed_cb;

    g_bus_get_sync_set_error = FALSE;

    g_dbus_connection_call_sync_stub_control.count   = 1;
    g_dbus_connection_call_sync_stub_calls[0].method = "Subscribe";
    g_dbus_connection_call_sync_stub_calls[0].rval   = g_variant_new("()");
    g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

    g_dbus_connection_call_sync_stub_control.count   = 2;
    g_dbus_connection_call_sync_stub_calls[1].method = "ListUnits";
    g_dbus_connection_call_sync_stub_calls[1].rval   = NULL;
    g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

    g_dbus_connection_call_sync_stub_control.count   = 3;
    g_dbus_connection_call_sync_stub_calls[2].method = "Unsubscribe";
    g_dbus_connection_call_sync_stub_calls[2].rval   = NULL;
    g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

    retval = (nhm_systemd_connect(callback) == FALSE) ? 0 : -1;
  }

  /* Check 5: Callback ok. Bus conn. ok. Subscribe ok. ListUnits ok */
  if(retval == 0)
  {
    /* Callback ok */
    callback = &nhm_systemd_test_app_state_changed_cb;

    /* Bus conn. ok */
    g_bus_get_sync_set_error = FALSE;

    /* Subscribe ok */
    g_dbus_connection_call_sync_stub_control.count   = 1;
    g_dbus_connection_call_sync_stub_calls[0].method = "Subscribe";
    g_dbus_connection_call_sync_stub_calls[0].rval   = g_variant_new("()");
    g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

    /* ListUnits ok */
    g_dbus_connection_call_sync_stub_control.count   = 2;
    g_dbus_connection_call_sync_stub_calls[1].method = "ListUnits";

    builder = g_variant_builder_new (G_VARIANT_TYPE("a(ssssssouso)"));
    g_variant_builder_add (builder, "(ssssssouso)",  "1", "2", "3", "4", "5", "6", "/a/b/c", 100, "7", "/a/b/c");
    g_variant_builder_add (builder, "(ssssssouso)",  "1.service", "2", "3", "4", "5", "6", "/a/b/c", 100, "7", "/a/b/c");
    g_dbus_connection_call_sync_stub_calls[1].rval = g_variant_new("(a(ssssssouso))", builder);
    g_variant_builder_unref (builder);

    g_dbus_connection_call_sync_stub_control.calls = g_dbus_connection_call_sync_stub_calls;

    /* Call */
    retval = (nhm_systemd_connect(callback) == TRUE) ? 0 : -1;

    /* Free created unit object. Destroy bus conn. */
    g_slist_free_full(nhm_systemd_observed_units, &nhm_systemd_free_unit);
    g_object_unref(nhm_systemd_conn);
  }

  return retval;
}


/**
 * nhm_test_systemd_disconnect:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_disconnect() function.
 */
static gint
nhm_test_systemd_disconnect(void)
{
  NhmSystemdUnit                   *unit = NULL;
  GdbusConnectionCallSyncStubCalls  g_dbus_connection_call_sync_stub_calls[1];

  /* Check 1: Sub nok. No UnitAdd sig. No UnitRem sig. No obs. units. No systemd conn. */
  nhm_systemd_events_subscribed = FALSE;
  g_dbus_connection_call_sync_stub_control.count   = 1;
  g_dbus_connection_call_sync_stub_calls[0].method = "Unsubscribe";
  g_dbus_connection_call_sync_stub_calls[0].rval   = NULL;
  g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

  nhm_systemd_unit_add_sig_id = 0;
  nhm_systemd_unit_rem_sig_id = 0;
  nhm_systemd_observed_units  = NULL;
  nhm_systemd_conn            = NULL;

  nhm_systemd_disconnect();

  /* Check 2: Sub ok. Unsub. nok. No UnitAdd sig. No UnitRem sig. No obs. units. No systemd conn. */
  nhm_systemd_events_subscribed = TRUE;
  g_dbus_connection_call_sync_stub_control.count   = 1;
  g_dbus_connection_call_sync_stub_calls[0].method = "Unsubscribe";
  g_dbus_connection_call_sync_stub_calls[0].rval   = NULL;
  g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

  nhm_systemd_unit_add_sig_id = 0;
  nhm_systemd_unit_rem_sig_id = 0;
  nhm_systemd_observed_units  = NULL;
  nhm_systemd_conn            = NULL;

  nhm_systemd_disconnect();

  /* Check 3: Unsub. ok. UnitAdd sig. UnitRem sig. Obs. units. Systemd conn. */
  nhm_systemd_events_subscribed = TRUE;
  g_dbus_connection_call_sync_stub_control.count   = 1;
  g_dbus_connection_call_sync_stub_calls[0].method = "Unsubscribe";
  g_dbus_connection_call_sync_stub_calls[0].rval   = g_variant_new("()");
  g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

  nhm_systemd_unit_add_sig_id = 1;
  nhm_systemd_unit_rem_sig_id = 1;

  unit = g_new(NhmSystemdUnit, 1);
  unit->active_state = NHM_ACTIVE_STATE_UNKNOWN;
  unit->name         = g_strdup("Unit");
  unit->path         = g_strdup("/a/unit/to/destroy");
  unit->sig_sub_id   = 0;
  nhm_systemd_observed_units  = g_slist_append(nhm_systemd_observed_units, unit);

  nhm_systemd_conn = g_object_new(G_TYPE_DBUS_CONNECTION, NULL);

  nhm_systemd_disconnect();

  return 0;
}


/**
 * nhm_systemd_test_active_state_string_to_enum:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_active_state_string_to_enum() function.
 */
static gint
nhm_systemd_test_active_state_string_to_enum(void)
{
  gint retval = 0;

  /* Check 1: active -> NHM_ACTIVE_STATE_ACTIVE */
  retval = (   nhm_systemd_active_state_string_to_enum("active")
            == NHM_ACTIVE_STATE_ACTIVE) ? 0 : -1;

  /* Check 2: inactive -> NHM_ACTIVE_STATE_INACTIVE */
  if(retval == 0)
  {
    retval = (nhm_systemd_active_state_string_to_enum("inactive")
              == NHM_ACTIVE_STATE_INACTIVE) ? 0 : -1;
  }

  /* Check 3: activating -> NHM_ACTIVE_STATE_ACTIVATING */
  if(retval == 0)
  {
    retval = (nhm_systemd_active_state_string_to_enum("activating")
              == NHM_ACTIVE_STATE_ACTIVATING) ? 0 : -1;
  }

  /* Check 4: deactivating -> NHM_ACTIVE_STATE_DEACTIVATING */
  if(retval == 0)
  {
    retval = (nhm_systemd_active_state_string_to_enum("deactivating")
              == NHM_ACTIVE_STATE_DEACTIVATING) ? 0 : -1;
  }

  /* Check 5: failed -> NHM_ACTIVE_STATE_FAILED */
  if(retval == 0)
  {
    retval = (nhm_systemd_active_state_string_to_enum("failed")
              == NHM_ACTIVE_STATE_FAILED) ? 0 : -1;
  }

  /* Check 6: reloading -> NHM_ACTIVE_STATE_RELOADING */
  if(retval == 0)
  {
    retval = (nhm_systemd_active_state_string_to_enum("reloading")
              == NHM_ACTIVE_STATE_RELOADING) ? 0 : -1;
  }

  /* Check 6: ? -> NHM_ACTIVE_STATE_UNKNOWN */
  if(retval == 0)
  {
    retval = (nhm_systemd_active_state_string_to_enum("")
              == NHM_ACTIVE_STATE_UNKNOWN) ? 0 : -1;
  }

  return retval;
}


/**
 * nhm_systemd_test_subscribe_properties_changed:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_subscribe_properties_changed() function.
 */
static gint
nhm_systemd_test_subscribe_properties_changed(void)
{
  NhmSystemdUnit unit;

  /* Check 1: Do a subscription */
  return (nhm_systemd_subscribe_properties_changed(&unit) == 0) ? 0 : -1;
}


/**
 * nhm_systemd_test_find_unit_by_name:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_find_unit_by_name() function.
 */
static gint
nhm_systemd_test_find_unit_by_name(void)
{
  gint           retval = 0;
  NhmSystemdUnit u1;
  NhmSystemdUnit u2;

  /* Check 1: Valid compare */
  u1.name = "Unit1";
  u2.name = "Unit1";
  retval = (nhm_systemd_find_unit_by_name(&u1, &u2) == 0) ? 0 : -1;

  /* Check 2: Invalid compare I */
  if(retval == 0)
  {
    u1.name = "Unit1";
    u2.name = "Unit2";
    retval = (nhm_systemd_find_unit_by_name(&u1, &u2) == -1) ? 0 : -1;
  }

  /* Check 3: Invalid compare II */
  if(retval == 0)
  {
    u1.name = "Unit2";
    u2.name = "Unit1";
    retval = (nhm_systemd_find_unit_by_name(&u1, &u2) == 1) ? 0 : -1;
  }

  return retval;
}


/**
 * nhm_systemd_test_free_unit:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_free_unit() function.
 */
static gint
nhm_systemd_test_free_unit(void)
{
  NhmSystemdUnit *unit = g_new(NhmSystemdUnit, 1);

  /* Check 1: Free normal unit object */
  unit->active_state = NHM_ACTIVE_STATE_UNKNOWN;
  unit->name         = g_strdup("Unit");
  unit->path         = g_strdup("/path/to/unit");
  unit->sig_sub_id   = 0;

  nhm_systemd_free_unit(unit);

  return 0;
}


/**
 * nhm_systemd_test_unit_active_state_changed:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_unit_active_state_changed() function.
 */
static gint
nhm_systemd_test_unit_active_state_changed(void)
{
  gint           retval = 0;
  NhmSystemdUnit unit   = {"Unit", "Path", NHM_ACTIVE_STATE_UNKNOWN, 0};

  /* Check 1: Change NHM_ACTIVE_STATE_UNKNOWN -> NHM_ACTIVE_STATE_UNKNOWN */
  nhm_systemd_app_status_cb = &nhm_systemd_test_app_state_changed_cb;
  nhm_systemd_test_app_state_changed_cb_called = FALSE;
  nhm_systemd_test_app_state_changed_cb_name   = NULL;
  nhm_systemd_test_app_state_changed_cb_status = NhmAppStatus_Ok;

  nhm_systemd_unit_active_state_changed(&unit, NHM_ACTIVE_STATE_UNKNOWN);

  /* Check that no callback occured */
  retval = (nhm_systemd_test_app_state_changed_cb_called == FALSE) ? 0 : -1;

  /* Check 2: Change NHM_ACTIVE_STATE_UNKNOWN -> NHM_ACTIVE_STATE_ACTIVE */
  if(retval == 0)
  {
    nhm_systemd_app_status_cb                    = &nhm_systemd_test_app_state_changed_cb;
    nhm_systemd_test_app_state_changed_cb_called = FALSE;
    nhm_systemd_test_app_state_changed_cb_name   = NULL;
    nhm_systemd_test_app_state_changed_cb_status = NhmAppStatus_Failed;

    nhm_systemd_unit_active_state_changed(&unit, NHM_ACTIVE_STATE_ACTIVE);

    /* Assert that callback occurred */
    retval = (   (nhm_systemd_test_app_state_changed_cb_called == TRUE)
              && (g_strcmp0(nhm_systemd_test_app_state_changed_cb_name, unit.name) == 0)
              && (nhm_systemd_test_app_state_changed_cb_status == NhmAppStatus_Ok))
             ? 0 : -1;
  }

  /* Check 2: Change NHM_ACTIVE_STATE_UNKNOWN -> NHM_ACTIVE_STATE_ACTIVE */
  if(retval == 0)
  {
    nhm_systemd_app_status_cb                    = &nhm_systemd_test_app_state_changed_cb;
    nhm_systemd_test_app_state_changed_cb_called = FALSE;
    nhm_systemd_test_app_state_changed_cb_name   = NULL;
    nhm_systemd_test_app_state_changed_cb_status = NhmAppStatus_Ok;

    nhm_systemd_unit_active_state_changed(&unit, NHM_ACTIVE_STATE_FAILED);

    /* Assert that callback occurred */
    retval = (   (nhm_systemd_test_app_state_changed_cb_called == TRUE)
              && (g_strcmp0(nhm_systemd_test_app_state_changed_cb_name, unit.name) == 0)
              && (nhm_systemd_test_app_state_changed_cb_status == NhmAppStatus_Failed))
             ? 0 : -1;
  }

  return retval;
}


/**
 * nhm_systemd_test_unit_get_active_state:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_unit_get_active_state() function.
 */
static gint
nhm_systemd_test_unit_get_active_state(void)
{
  gint                             retval             = 0;
  GVariant                        *unit_state_variant = NULL;
  NhmSystemdUnit                   unit               = {"Name", "Path", NHM_ACTIVE_STATE_ACTIVE, 0};
  GdbusConnectionCallSyncStubCalls g_dbus_connection_call_sync_stub_calls[1];

  /* Check 1: D-Bus error getting ActiveState property */
  g_dbus_connection_call_sync_stub_control.count   = 1;
  g_dbus_connection_call_sync_stub_calls[0].method = "Get";
  g_dbus_connection_call_sync_stub_calls[0].rval   = NULL;
  g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

  retval = (nhm_systemd_unit_get_active_state(&unit) == NHM_ACTIVE_STATE_UNKNOWN)
           ? 0 : -1;

  /* Check 2: Retrieve D-Bus property value successful */
  if(retval == 0)
  {
    g_dbus_connection_call_sync_stub_control.count   = 1;
    g_dbus_connection_call_sync_stub_calls[0].method = "Get";

    unit_state_variant = g_variant_new_string("active");
    unit_state_variant = g_variant_new_variant(unit_state_variant);
    unit_state_variant = g_variant_new_tuple(&unit_state_variant, 1);
    g_dbus_connection_call_sync_stub_calls[0].rval  = unit_state_variant;

    g_dbus_connection_call_sync_stub_control.calls   = g_dbus_connection_call_sync_stub_calls;

    retval = (nhm_systemd_unit_get_active_state(&unit) == NHM_ACTIVE_STATE_ACTIVE)
             ? 0 : -1;
  }

  return retval;
}


/**
 * nhm_systemd_test_unit_added:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_unit_added() function.
 */
static gint
nhm_systemd_test_unit_added(void)
{
  gint                              retval             = 0;
  GVariant                         *param              = NULL;
  GVariant                         *unit_state_variant = NULL;
  NhmSystemdUnit                   *unit               = NULL;
  GdbusConnectionCallSyncStubCalls  g_dbus_connection_call_sync_stub_calls[1];

  /* Check 1: Wrong parameter format */
  nhm_systemd_observed_units = NULL;
  param = g_variant_new("(uss)", 10, "Wrong", "Unit");

  nhm_systemd_unit_added(NULL,
                         NULL,
                         NULL,
                         NULL,
                         NULL,
                         param,
                         NULL);

  retval = (nhm_systemd_observed_units == NULL) ? 0 : -1;

  /* Check 2: New unit added, but no service */
  if(retval == 0)
  {
    nhm_systemd_observed_units = NULL;
    param = g_variant_new("(so)", "Unit", "/Path/to/Unit");

    /* Function will retrieve unit's active state */
    g_dbus_connection_call_sync_stub_control.count   = 1;
    g_dbus_connection_call_sync_stub_calls[0].method = "Get";

    unit_state_variant = g_variant_new_string("active");
    unit_state_variant = g_variant_new_variant(unit_state_variant);
    unit_state_variant = g_variant_new_tuple(&unit_state_variant, 1);
    g_dbus_connection_call_sync_stub_calls[0].rval  = unit_state_variant;

    g_dbus_connection_call_sync_stub_control.calls = g_dbus_connection_call_sync_stub_calls;

    nhm_systemd_unit_added(NULL,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           param,
                           NULL);
    g_variant_unref(param);
    /* Check that unit was not added */
    retval = (nhm_systemd_observed_units == NULL) ? 0 : -1;
  }

  /* Check 3: Add new service */
  if(retval == 0)
  {
    nhm_systemd_observed_units = NULL;
    param = g_variant_new("(so)", "Unit.service", "/Path/to/Unit");

    /* Function will retrieve unit's active state */
    g_dbus_connection_call_sync_stub_control.count   = 1;
    g_dbus_connection_call_sync_stub_calls[0].method = "Get";

    unit_state_variant = g_variant_new_string("active");
    unit_state_variant = g_variant_new_variant(unit_state_variant);
    unit_state_variant = g_variant_new_tuple(&unit_state_variant, 1);
    g_dbus_connection_call_sync_stub_calls[0].rval  = unit_state_variant;

    g_dbus_connection_call_sync_stub_control.calls = g_dbus_connection_call_sync_stub_calls;

    nhm_systemd_unit_added(NULL,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           param,
                           NULL);

    g_variant_unref(param);
    /* Check that unit was not added */
    unit = (NhmSystemdUnit*) nhm_systemd_observed_units->data;
    retval = (   (g_strcmp0(unit->name, "Unit.service") == 0)
              && (g_strcmp0(unit->path, "/Path/to/Unit") == 0)
              && (unit->active_state == NHM_ACTIVE_STATE_ACTIVE)
              && (unit->sig_sub_id   == 0)) ? 0 : -1;

    g_slist_free_full(nhm_systemd_observed_units, &nhm_systemd_free_unit);
  }

  /* Check 4: Add same service */
  if(retval == 0)
  {
    param = g_variant_new("(so)", "Unit.service", "/Path/to/Unit");

    /* Add unit to the list */
    nhm_systemd_observed_units = NULL;
    unit = g_new(NhmSystemdUnit, 1);
    unit->name         = g_strdup("Unit.service");
    unit->path         = g_strdup("/Path/to/Unit");
    unit->active_state = NHM_ACTIVE_STATE_UNKNOWN;
    unit->sig_sub_id   = 0;
    nhm_systemd_observed_units = g_slist_append(nhm_systemd_observed_units, unit);

    nhm_systemd_unit_added(NULL,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           param,
                           NULL);

    g_variant_unref(param);
    retval = (g_slist_length(nhm_systemd_observed_units) == 1) ? 0 : -1;

    g_slist_free_full(nhm_systemd_observed_units, &nhm_systemd_free_unit);
  }

  return retval;
}


/**
 * nhm_systemd_test_unit_removed:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_unit_removed() function.
 */
static gint
nhm_systemd_test_unit_removed(void)
{
  gint            retval = 0;
  GVariant       *param  = NULL;
  NhmSystemdUnit *unit;

  /* Preparation: Build up a list with an observed unit */
  nhm_systemd_observed_units = NULL;
  unit = g_new(NhmSystemdUnit, 1);
  unit->name         = g_strdup("Unit.service");
  unit->path         = g_strdup("/Path/to/Unit");
  unit->active_state = NHM_ACTIVE_STATE_UNKNOWN;
  unit->sig_sub_id   = 0;
  nhm_systemd_observed_units = g_slist_append(nhm_systemd_observed_units, unit);

  /* Reuse unit variable to point on first list element */
  unit = (NhmSystemdUnit*) (nhm_systemd_observed_units->data);


  /* Check 1: Invalid parameter format  */
  param = g_variant_new("(uss)", 10, "Unit", "/Path/to/Unit");

  nhm_systemd_unit_removed(NULL,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           param,
                           NULL);
  g_variant_unref(param);
  /* Assert unit still on the list */
  retval = (   (g_strcmp0(unit->name, "Unit.service") == 0)
            && (g_strcmp0(unit->path, "/Path/to/Unit") == 0)
            && (unit->active_state == NHM_ACTIVE_STATE_UNKNOWN)
            && (unit->sig_sub_id   == 0)) ? 0 : -1;

  /* Check 2: No service removed */
  if(retval == 0)
  {
    param = g_variant_new("(so)", "Unit1", "/Path/to/Unit");

    nhm_systemd_unit_removed(NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             param,
                             NULL);
    g_variant_unref(param);
    /* Assert unit still on the list */
    retval = (   (g_strcmp0(unit->name, "Unit.service") == 0)
              && (g_strcmp0(unit->path, "/Path/to/Unit") == 0)
              && (unit->active_state == NHM_ACTIVE_STATE_UNKNOWN)
              && (unit->sig_sub_id   == 0)) ? 0 : -1;
  }

  /* Check 3: Unknown unit removed */
  if(retval == 0)
  {
    param = g_variant_new("(so)", "Unit1.service", "/Path/to/Unit");

    nhm_systemd_unit_removed(NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             param,
                             NULL);
    g_variant_unref(param);
    /* Assert unit still on the list */
    retval = (   (g_strcmp0(unit->name, "Unit.service") == 0)
              && (g_strcmp0(unit->path, "/Path/to/Unit") == 0)
              && (unit->active_state == NHM_ACTIVE_STATE_UNKNOWN)
              && (unit->sig_sub_id   == 0)) ? 0 : -1;
  }

  /* Check 4: Unit removed */
  if(retval == 0)
  {
    param = g_variant_new("(so)", "Unit.service", "/Path/to/Unit");

    nhm_systemd_unit_removed(NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             param,
                             NULL);
    g_variant_unref(param);
    retval = (nhm_systemd_observed_units == NULL) ? 0 : -1;
  }

  return retval;
}


/**
 * nhm_systemd_test_unit_properties_changed:
 * @Return: 0, if test succeeded. Otherwise -1.
 *
 * Test nhm_systemd_unit_properties_changed() function.
 */
static gint
nhm_systemd_test_unit_properties_changed(void)
{
  gint                              retval             = 0;
  GVariant                         *param              = NULL;
  GVariant                         *unit_state_variant = NULL;
  gchar                            *inv_prop[2]        = {"state", NULL};
  NhmSystemdUnit                    unit;
  GdbusConnectionCallSyncStubCalls  g_dbus_connection_call_sync_stub_calls[1];

  /* Check 1: Parameter format nok. */
  param = g_variant_new("(s)", "Test");
  nhm_systemd_app_status_cb = &nhm_systemd_test_app_state_changed_cb;
  nhm_systemd_test_app_state_changed_cb_called = FALSE;

  nhm_systemd_unit_properties_changed(NULL,
                                      NULL,
                                      NULL,
                                      NULL,
                                      NULL,
                                      param,
                                      NULL);
  g_variant_unref(param);
  retval = (nhm_systemd_test_app_state_changed_cb_called == FALSE) ? 0 : -1;

  /* Check 2: Parameter format ok. ActiveState unchanged. */
  if(retval == 0)
  {
    inv_prop[0] = "Invalid";
    param = g_variant_new("(sa{sv}^as)", "Test", NULL, inv_prop);

    nhm_systemd_app_status_cb = &nhm_systemd_test_app_state_changed_cb;
    nhm_systemd_test_app_state_changed_cb_called = FALSE;

    nhm_systemd_unit_properties_changed(NULL,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL,
                                        param,
                                        NULL);
    g_variant_unref(param);
    retval = (nhm_systemd_test_app_state_changed_cb_called == FALSE) ? 0 : -1;
  }

  /* Check 3: Parameter format ok. Same ActiveState. */
  if(retval == 0)
  {
    inv_prop[0] = "ActiveState";
    param = g_variant_new("(sa{sv}^as)", "Test", NULL, inv_prop);

    unit.name = "Unit";
    unit.path = "Path";
    unit.active_state = NHM_ACTIVE_STATE_ACTIVE;
    unit.sig_sub_id = 0;

    g_dbus_connection_call_sync_stub_control.count    = 1;
    g_dbus_connection_call_sync_stub_calls[0].method  = "Get";
    unit_state_variant = g_variant_new_string("active");
    unit_state_variant = g_variant_new_variant(unit_state_variant);
    unit_state_variant = g_variant_new_tuple(&unit_state_variant, 1);
    g_dbus_connection_call_sync_stub_calls[0].rval  = unit_state_variant;
    g_dbus_connection_call_sync_stub_control.calls  = g_dbus_connection_call_sync_stub_calls;

    nhm_systemd_app_status_cb = &nhm_systemd_test_app_state_changed_cb;
    nhm_systemd_test_app_state_changed_cb_called = FALSE;

    nhm_systemd_unit_properties_changed(NULL,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL,
                                        param,
                                        &unit);
    g_variant_unref(param);
    retval = (nhm_systemd_test_app_state_changed_cb_called == FALSE) ? 0 : -1;
  }

  /* Check 4: Parameter format ok. ActiveState changed. */
  if(retval == 0)
  {
    inv_prop[0] = "ActiveState";
    param = g_variant_new("(sa{sv}^as)", "Test", NULL, inv_prop);

    unit.name = "Unit";
    unit.path = "Path";
    unit.active_state = NHM_ACTIVE_STATE_FAILED;
    unit.sig_sub_id = 0;
    g_dbus_connection_call_sync_stub_control.count = 1;
    g_dbus_connection_call_sync_stub_calls[0].method  = "Get";
    unit_state_variant = g_variant_new_string("active");
    unit_state_variant = g_variant_new_variant(unit_state_variant);
    unit_state_variant = g_variant_new_tuple(&unit_state_variant, 1);
    g_dbus_connection_call_sync_stub_calls[0].rval  = unit_state_variant;
    g_dbus_connection_call_sync_stub_control.calls  = g_dbus_connection_call_sync_stub_calls;

    nhm_systemd_test_app_state_changed_cb_called = FALSE;
    nhm_systemd_app_status_cb = &nhm_systemd_test_app_state_changed_cb;
    nhm_systemd_unit_properties_changed(NULL,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL,
                                        param,
                                        &unit);
    g_variant_unref(param);
    retval = (nhm_systemd_test_app_state_changed_cb_called == TRUE) ? 0 : -1;
  }

  return retval;
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

  g_type_init();

  /* Test interfaces */
  retval = nhm_test_systemd_connect();
  retval = (retval == 0) ? nhm_test_systemd_disconnect()                   : -1;

  /* Test static functions */
  retval = (retval == 0) ? nhm_systemd_test_active_state_string_to_enum()  : -1;

  /* Test helper functions */
  retval = (retval == 0) ? nhm_systemd_test_subscribe_properties_changed() : -1;
  retval = (retval == 0) ? nhm_systemd_test_find_unit_by_name()            : -1;
  retval = (retval == 0) ? nhm_systemd_test_free_unit()                    : -1;

  /* Test unit state change chain */
  retval = (retval == 0) ? nhm_systemd_test_unit_active_state_changed()    : -1;
  retval = (retval == 0) ? nhm_systemd_test_unit_get_active_state()        : -1;
  retval = (retval == 0) ? nhm_systemd_test_unit_added()                   : -1;
  retval = (retval == 0) ? nhm_systemd_test_unit_removed()                 : -1;
  retval = (retval == 0) ? nhm_systemd_test_unit_properties_changed()      : -1;

  return retval;
}
