/* NHM - NodeHealthMonitor
 *
 * Implementation of stubs for gio
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

#include <stdio.h>                  /* NULL               */
#include <string.h>                 /* strcmp             */
#include <gio/gio.h>                /* Header of real gio */
#include <tst/stubs/gio/gio-stub.h> /* Header of stub gio */


/*******************************************************************************
*
* Exported variables and constants
*
*******************************************************************************/

gboolean  g_bus_get_sync_set_error                              = FALSE;
gboolean  g_dbus_interface_skeleton_export_stub_set_error       = FALSE;
gboolean  g_main_loop_quit_stub_called                          = FALSE;
guint     g_timeout_add_seconds_called_interval                 = 0;
gboolean  g_timeout_add_seconds_called                          = FALSE;
gboolean  g_dbus_connection_new_for_address_sync_stub_set_error = FALSE;
GdbusConnectionCallSyncStubControl g_dbus_connection_call_sync_stub_control;


/*******************************************************************************
*
* File local variables and constants
*
*******************************************************************************/

static guint  folder_file_idx = 0;
static gchar *folder_files[]  = {"0000", "0001", NULL};

/*******************************************************************************
*
* Interfaces. Exported functions.
*
*******************************************************************************/

/**
 * g_file_test_stub:
 *
 * Stub for g_file_test()
 */
gboolean
g_file_test_stub(const gchar *filename,
                 GFileTest    test)
{
  return (g_strcmp0(filename, "existing_file") == 0);
}

/**
 * g_file_read_link_stub:
 *
 * Stub for g_file_read_link()
 */
gchar*
g_file_read_link_stub(const gchar  *filename,
                      GError      **error)
{
  gchar *linked_file = NULL;

  if(strcmp("/proc/0000/exe", filename) == 0)
  {
    linked_file = g_strdup("/usr/bin/valid_prog1");
  }
  else if(strcmp("/proc/0001/exe", filename) == 0)
  {
    linked_file = g_strdup("/usr/bin/valid_prog2");
  }
  else
  {
    linked_file = NULL;
  }

  return linked_file;
}

/**
 * g_dir_open_stub:
 *
 * Stub for g_dir_open()
 */
GDir*
g_dir_open_stub(const gchar *path,
                guint        flags,
                GError     **error)
{
  folder_file_idx = 0;
  return (GDir*) folder_files;
}

/**
 * g_dir_read_name_stub:
 *
 * Stub for g_dir_read_name()
 */
const gchar*
g_dir_read_name_stub(GDir *dir)
{
  gchar *file_name = NULL;

  if(folder_file_idx < sizeof(folder_files)/sizeof(gchar*))
  {
    file_name = folder_files[folder_file_idx];
    folder_file_idx++;
  }

  return file_name;
}

/**
 * g_dir_close_stub:
 *
 * Stub for g_dir_close()
 */
void
g_dir_close_stub(GDir *dir)
{
  folder_file_idx = 0;
}


/**
 * g_bus_get_sync_stub:
 *
 * Stub for g_bus_get_sync()
 */
GDBusConnection*
g_bus_get_sync_stub(GBusType       bus_type,
                    GCancellable  *cancellable,
                    GError       **error)
{
  gpointer retval = FALSE;

  if(g_bus_get_sync_set_error == FALSE)
  {
    retval = g_object_new(G_TYPE_DBUS_CONNECTION, NULL);
  }
  else
  {
    retval = NULL;
    g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_FAILED, NULL);
  }

  return retval;
}

/**
 * g_bus_own_name_stub:
 *
 * Stub for g_bus_own_name()
 */
guint
g_bus_own_name_stub(GBusType                  bus_type,
                    const gchar              *name,
                    GBusNameOwnerFlags        flags,
                    GBusAcquiredCallback      bus_acquired_handler,
                    GBusNameAcquiredCallback  name_acquired_handler,
                    GBusNameLostCallback      name_lost_handler,
                    gpointer                  user_data,
                    GDestroyNotify            user_data_free_func)
{
  return 0;
}

/**
 * g_dbus_connection_get_unique_name_stub:
 *
 * Stub for g_dbus_connection_get_unique_name()
 */
const gchar*
g_dbus_connection_get_unique_name_stub(GDBusConnection *connection)
{
  return NULL;
}

/**
 * g_dbus_interface_skeleton_export_stub:
 *
 * Stub for g_dbus_interface_skeleton_export()
 */
gboolean
g_dbus_interface_skeleton_export_stub(GDBusInterfaceSkeleton *interface_,
                                      GDBusConnection        *connection,
                                      const gchar            *object_path,
                                      GError                **error)
{
  gboolean retval = FALSE;

  if(g_dbus_interface_skeleton_export_stub_set_error == FALSE)
  {
    retval = TRUE;
  }
  else
  {
    retval = FALSE;
    g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_FAILED, NULL);
  }

  return retval;
}


/**
 * g_dbus_connection_new_for_address_sync_stub:
 *
 * Stub for g_dbus_connection_new_for_address_sync()
 */
GDBusConnection*
g_dbus_connection_new_for_address_sync_stub(const gchar          *address,
                                            GDBusConnectionFlags  flags,
                                            GDBusAuthObserver    *observer,
                                            GCancellable         *cancellable,
                                            GError              **error)
{
  GDBusConnection *retval = NULL;

  if(g_dbus_connection_new_for_address_sync_stub_set_error == FALSE)
  {
    retval = g_object_new(G_TYPE_DBUS_CONNECTION, NULL);
  }
  else
  {
    retval = NULL;
    g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_FAILED, NULL);
  }

  return retval;
}


/**
 * g_dbus_connection_call_sync_stub:
 *
 * Stub for g_dbus_connection_call_sync()
 */
GVariant*
g_dbus_connection_call_sync_stub(GDBusConnection    *connection,
                                 const gchar        *bus_name,
                                 const gchar        *object_path,
                                 const gchar        *interface_name,
                                 const gchar        *method_name,
                                 GVariant           *parameters,
                                 const GVariantType *reply_type,
                                 GDBusCallFlags      flags,
                                 gint                timeout_msec,
                                 GCancellable       *cancellable,
                                 GError            **error)
{
  GVariant                         *rval              = NULL;
  guint                             control_array_idx = 0;
  GdbusConnectionCallSyncStubCalls *call              = NULL;

  for(control_array_idx = 0;
         (control_array_idx < g_dbus_connection_call_sync_stub_control.count)
      && (call == NULL);
      control_array_idx++)
  {
    if(g_strcmp0(g_dbus_connection_call_sync_stub_control.calls[control_array_idx].method,
        method_name) == 0)
    {
      call = &g_dbus_connection_call_sync_stub_control.calls[control_array_idx];
    }
  }

  if(call != NULL)
  {
    rval = call->rval;

    if((rval == NULL) && (error != NULL))
    {
      g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_FAILED, NULL);
    }
  }

  return rval;
}


/**
 * g_dbus_connection_signal_subscribe_stub:
 *
 * Stub for g_dbus_connection_signal_subscribe()
 */
guint
g_dbus_connection_signal_subscribe_stub(GDBusConnection     *connection,
                                        const gchar         *sender,
                                        const gchar         *interface_name,
                                        const gchar         *member,
                                        const gchar         *object_path,
                                        const gchar         *arg0,
                                        GDBusSignalFlags     flags,
                                        GDBusSignalCallback  callback,
                                        gpointer             user_data,
                                        GDestroyNotify       user_data_free_func)
{
  return 0;
}


/**
 * g_dbus_connection_signal_unsubscribe_stub:
 *
 * Stub for g_dbus_connection_signal_unsubscribe()
 */
void
g_dbus_connection_signal_unsubscribe_stub(GDBusConnection *connection,
                                          guint            subscription_id)
{

}


/**
 * g_main_loop_run_stub:
 *
 * Stub for g_main_loop_run()
 */
void
g_main_loop_run_stub(GMainLoop *loop)
{
}

/**
 * g_main_loop_quit_stub:
 *
 * Stub for g_main_loop_quit()
 */
void
g_main_loop_quit_stub(GMainLoop *loop)
{
  g_main_loop_quit_stub_called = TRUE;
}

/**
 * g_timeout_add_seconds_stub:
 *
 * Stub for g_timeout_add_seconds()
 */
guint
g_timeout_add_seconds_stub(guint       interval,
                           GSourceFunc function,
                           gpointer    data)
{
  g_timeout_add_seconds_called_interval = interval;
  g_timeout_add_seconds_called          = TRUE;

  return 0;
}

/**
 * g_signal_connect_data_stub:
 *
 * Stub for g_signal_connect_data()
 */
gulong
g_signal_connect_data_stub(gpointer       instance,
                           const gchar   *detailed_signal,
                           GCallback      c_handler,
                           gpointer       data,
                           GClosureNotify destroy_data,
                           GConnectFlags  connect_flags)
{
  return 0;
}

/**
 * g_spawn_sync_stub:
 *
 * Stub for g_spawn_sync()
 */
gboolean
g_spawn_sync_stub(const gchar          *working_directory,
                  gchar               **argv,
                  gchar               **envp,
                  GSpawnFlags           flags,
                  GSpawnChildSetupFunc  child_setup,
                  gpointer              user_data,
                  gchar               **standard_output,
                  gchar               **standard_error,
                  gint                 *exit_status,
                  GError              **error)
{
  gboolean retval = FALSE;

  if(strcmp(argv[0], "valid_proc") == 0)
  {
    retval       = TRUE;
    *exit_status = 0;
    *error       = NULL;
  }
  else if(strcmp(argv[0], "failing_proc") == 0)
  {
    retval       = TRUE;
    *exit_status = -1;
    *error       = NULL;
  }
  else
  {
    retval = FALSE;
    g_set_error(error, G_SPAWN_ERROR, G_SPAWN_ERROR_FAILED, NULL);
  }

  return retval;
}
