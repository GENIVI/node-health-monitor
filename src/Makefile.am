################################################################################
#
# Author: Jean-Pierre.Bogler@continental-corporation.com
#
# Makefile template for the node-health-monitor
#
# Process this file with automake to produce a Makefile.in.
#
# Copyright (C) 2013 Continental Automotive Systems, Inc.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, 
# v. 2.0. If a copy of the MPL was not distributed with this file, You can 
# obtain one at http://mozilla.org/MPL/2.0/.
#
################################################################################

# Program built by the Makefile
bin_PROGRAMS                       = node-health-monitor

# Sources that belong to NHM
node_health_monitor_SOURCES        = nhm-main.c                               \
                                     nhm-systemd.c                            \
                                     nhm-systemd.h                            \
                                     nhm-helper.c                             \
                                     nhm-helper.h                             \
                                     $(top_srcdir)/inc/NodeHealthMonitor.h

# Generated sources that belong to the NHM, but don't have to be distributed
nodist_node_health_monitor_SOURCES = $(top_srcdir)/gen/nhm-dbus-info.c        \
                                     $(top_srcdir)/gen/nhm-dbus-info.h        \
                                     $(top_srcdir)/gen/nsm-dbus-lc-control.c  \
                                     $(top_srcdir)/gen/nsm-dbus-lc-control.h  \
                                     $(top_srcdir)/gen/nsm-dbus-consumer.c    \
                                     $(top_srcdir)/gen/nsm-dbus-consumer.h    \
                                     $(top_srcdir)/gen/nsm-dbus-lc-consumer.c \
                                     $(top_srcdir)/gen/nsm-dbus-lc-consumer.h

# C flags to compile NHM
node_health_monitor_CFLAGS         = -DCONFDIR=\"$(sysconfdir)/\"             \
                                     -DDATADIR=\"$(localstatedir)/lib/\"      \
                                     -I $(top_srcdir)                         \
                                     $(DLT_CFLAGS)                            \
                                     $(GIO_CFLAGS)                            \
                                     $(GIO_UNIX_CFLAGS)                       \
                                     $(GLIB_CFLAGS)                           \
                                     $(GOBJECT_CFLAGS)                        \
                                     $(SYSTEMD_CFLAGS)                        \
                                     $(NSM_CFLAGS)                            \
                                     $(PCL_CFLAGS)

# Libraries to be linked in NHM
node_health_monitor_LDADD          = $(DLT_LIBS)                              \
                                     $(GIO_LIBS)                              \
                                     $(GIO_UNIX_LIBS)                         \
                                     $(GLIB_LIBS)                             \
                                     $(GOBJECT_LIBS)                          \
                                     $(SYSTEMD_LIBS)                          \
                                     $(PCL_LIBS)
