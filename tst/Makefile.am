################################################################################
#
# Author: Jean-Pierre.Bogler@continental-corporation.com
#
# Makefile template for the NodeHealthMonitor unit test
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


# Create target for "make check" and test programs
check_PROGRAMS               = nhm-main-test nhm-systemd-test

# Sources for the NHM unit test
nhm_main_test_SOURCES        = nhm-main-test.c                                         \
                               nhm-main-test.h                                         \
                               $(top_srcdir)/inc/NodeHealthMonitor.h                   \
                               $(top_srcdir)/src/nhm-helper.c                          \
                               $(top_srcdir)/src/nhm-helper.h                          \
                               stubs/dlt/dlt-stub.c                                    \
                               stubs/dlt/dlt-stub.h                                    \
                               stubs/nhm/nhm-systemd-stub.c                            \
                               stubs/nhm/nhm-systemd-stub.h                            \
                               stubs/systemd/sd-daemon-stub.c                          \
                               stubs/systemd/sd-daemon-stub.h                          \
                               stubs/gio/gio-stub.c                                    \
                               stubs/gio/gio-stub.h                                    \
                               stubs/gen/nsm-dbus-lc-consumer-stub.c                   \
                               stubs/gen/nsm-dbus-lc-consumer-stub.h                   \
                               stubs/gen/nsm-dbus-consumer-stub.c                      \
                               stubs/gen/nsm-dbus-consumer-stub.h                      \
                               stubs/gen/nsm-dbus-lc-control-stub.c                    \
                               stubs/gen/nsm-dbus-lc-control-stub.h                    \
                               stubs/gen/nhm-dbus-info-stub.c                          \
                               stubs/gen/nhm-dbus-info-stub.h                          \
                               stubs/persistence/persistence_client_library_key-stub.c \
                               stubs/persistence/persistence_client_library_key-stub.h

# The unit test depends on the tested c file, but it should not be compiled in.
nhm_main_test_DEPENDENCIES   = $(top_srcdir)/src/nhm-main.c

# Sources for the NHM unit test that are compiled but not in distributed
nodist_nhm_main_test_SOURCES = $(top_srcdir)/gen/nhm-dbus-info.c        \
                               $(top_srcdir)/gen/nhm-dbus-info.h        \
                               $(top_srcdir)/gen/nsm-dbus-lc-control.c  \
                               $(top_srcdir)/gen/nsm-dbus-lc-control.h  \
                               $(top_srcdir)/gen/nsm-dbus-consumer.c    \
                               $(top_srcdir)/gen/nsm-dbus-consumer.h    \
                               $(top_srcdir)/gen/nsm-dbus-lc-consumer.c \
                               $(top_srcdir)/gen/nsm-dbus-lc-consumer.h

# Same C flags as real NHM, but use local directory for config and data
nhm_main_test_CFLAGS         = -DCONFDIR=\"\"                           \
                               -DDATADIR=\"\"                           \
                               -I $(top_srcdir)                         \
                               $(DLT_CFLAGS)                            \
                               $(GIO_CFLAGS)                            \
                               $(GIO_UNIX_CFLAGS)                       \
                               $(GLIB_CFLAGS)                           \
                               $(GOBJECT_CFLAGS)                        \
                               $(SYSTEMD_CFLAGS)                        \
                               $(NSM_CFLAGS)                            \
                               $(PCL_CFLAGS)

# Same libraries as real NHM
nhm_main_test_LDADD          = $(GIO_LIBS)                              \
                               $(GIO_UNIX_LIBS)                         \
                               $(GLIB_LIBS)                             \
                               $(GOBJECT_LIBS)

############################# NHM systemd test #################################

nhm_systemd_test_SOURCES      = nhm-systemd-test.c                       \
                                nhm-systemd-test.h                       \
                                $(top_srcdir)/src/nhm-systemd.h          \
                                $(top_srcdir)/src/nhm-helper.c           \
                                $(top_srcdir)/src/nhm-helper.h           \
                                stubs/dlt/dlt-stub.c                     \
                                stubs/dlt/dlt-stub.h                     \
                                stubs/gio/gio-stub.c                     \
                                stubs/gio/gio-stub.h

nhm_systemd_test_DEPENDENCIES = $(top_srcdir)/src/nhm-systemd.c

nhm_systemd_test_CFLAGS       = -I $(top_srcdir)                         \
                                $(DLT_CFLAGS)                            \
                                $(GIO_CFLAGS)                            \
                                $(GIO_UNIX_CFLAGS)                       \
                                $(GLIB_CFLAGS)                           \
                                $(GOBJECT_CFLAGS)

nhm_systemd_test_LDADD        = $(GIO_LIBS)                              \
                                $(GIO_UNIX_LIBS)                         \
                                $(GLIB_LIBS)                             \
                                $(GOBJECT_LIBS)
                               
TESTS = nhm-main-test nhm-systemd-test
