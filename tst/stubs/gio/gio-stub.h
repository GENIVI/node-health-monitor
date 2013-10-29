/* NHM - NodeHealthMonitor
 *
 * Definition of stubs for gio
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef GIO_STUB_H
#define GIO_STUB_H

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

#include <gio/gio.h> /* Include header of real gio */

/*******************************************************************************
*
* Exported variables, constants and defines
*
*******************************************************************************/

typedef struct
{
  gchar    *method;
  GVariant *rval;
} GdbusConnectionCallSyncStubCalls;

typedef struct
{
  guint                             count;
  GdbusConnectionCallSyncStubCalls *calls;
} GdbusConnectionCallSyncStubControl;


extern gboolean                           g_main_loop_quit_stub_called;
extern gboolean                           g_bus_get_sync_set_error;
extern guint                              g_timeout_add_seconds_called_interval;
extern gboolean                           g_timeout_add_seconds_called;
extern gboolean                           g_dbus_interface_skeleton_export_stub_set_error;
extern gboolean                           g_dbus_connection_new_for_address_sync_stub_set_error;
extern gboolean                           g_dbus_connection_call_sync_stub_set_error;
extern GdbusConnectionCallSyncStubControl g_dbus_connection_call_sync_stub_control;


/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

/* File and folder reading */
gboolean          g_file_test_stub                      (const gchar             *filename,
                                                         GFileTest                test);
gchar            *g_file_read_link_stub                 (const gchar             *filename,
                                                         GError                 **error);
GDir             *g_dir_open_stub                       (const gchar             *path,
                                                         guint                    flags,
                                                         GError                 **error);
const gchar      *g_dir_read_name_stub                  (GDir                    *dir);
void              g_dir_close_stub                      (GDir                    *dir);

/* Mainloop handling */
void              g_main_loop_run_stub                  (GMainLoop               *loop);
void              g_main_loop_quit_stub                 (GMainLoop               *loop);

/* Dbus handling */
GDBusConnection  *g_bus_get_sync_stub                   (GBusType                 bus_type,
                                                         GCancellable            *cancellable,
                                                         GError                 **error);
const gchar      *g_dbus_connection_get_unique_name_stub(GDBusConnection         *connection);
guint             g_bus_own_name_stub                   (GBusType                 bus_type,
                                                         const gchar             *name,
                                                         GBusNameOwnerFlags       flags,
                                                         GBusAcquiredCallback     bus_acquired_handler,
                                                         GBusNameAcquiredCallback name_acquired_handler,
                                                         GBusNameLostCallback     name_lost_handler,
                                                         gpointer                 user_data,
                                                         GDestroyNotify           user_data_free_func);


gboolean          g_dbus_interface_skeleton_export_stub (GDBusInterfaceSkeleton  *interface_,
                                                         GDBusConnection         *connection,
                                                         const gchar             *object_path,
                                                         GError                 **error);

GDBusConnection *g_dbus_connection_new_for_address_sync_stub(const gchar            *address,
                                                             GDBusConnectionFlags    flags,
                                                             GDBusAuthObserver      *observer,
                                                             GCancellable           *cancellable,
                                                             GError                **error);

GVariant        *g_dbus_connection_call_sync_stub           (GDBusConnection    *connection,
                                                             const gchar        *bus_name,
                                                             const gchar        *object_path,
                                                             const gchar        *interface_name,
                                                             const gchar        *method_name,
                                                             GVariant           *parameters,
                                                             const GVariantType *reply_type,
                                                             GDBusCallFlags      flags,
                                                             gint                timeout_msec,
                                                             GCancellable       *cancellable,
                                                             GError            **error);
guint            g_dbus_connection_signal_subscribe_stub    (GDBusConnection     *connection,
                                                             const gchar         *sender,
                                                             const gchar         *interface_name,
                                                             const gchar         *member,
                                                             const gchar         *object_path,
                                                             const gchar         *arg0,
                                                             GDBusSignalFlags     flags,
                                                             GDBusSignalCallback  callback,
                                                             gpointer             user_data,
                                                             GDestroyNotify       user_data_free_func);
void             g_dbus_connection_signal_unsubscribe_stub  (GDBusConnection     *connection,
                                                             guint                subscription_id);
GVariant        *g_dbus_connection_call_sync_stub           (GDBusConnection    *connection,
                                                             const gchar        *bus_name,
                                                             const gchar        *object_path,
                                                             const gchar        *interface_name,
                                                             const gchar        *method_name,
                                                             GVariant           *parameters,
                                                             const GVariantType *reply_type,
                                                             GDBusCallFlags      flags,
                                                             gint                timeout_msec,
                                                             GCancellable       *cancellable,
                                                             GError            **error);

/* Timer and signals */
guint             g_timeout_add_seconds_stub            (guint                    interval,
                                                         GSourceFunc              function,
                                                         gpointer                 data);

gulong            g_signal_connect_data_stub            (gpointer                 instance,
                                                         const gchar             *detailed_signal,
                                                         GCallback                c_handler,
                                                         gpointer                 data,
                                                         GClosureNotify           destroy_data,
                                                         GConnectFlags            connect_flags);

/* Process handling */
gboolean          g_spawn_sync_stub                     (const gchar             *working_directory,
                                                         gchar                  **argv,
                                                         gchar                  **envp,
                                                         GSpawnFlags              flags,
                                                         GSpawnChildSetupFunc     child_setup,
                                                         gpointer                 user_data,
                                                         gchar                  **standard_output,
                                                         gchar                  **standard_error,
                                                         gint                    *exit_status,
                                                         GError                 **error);


#endif /* GIO_STUB_H */
