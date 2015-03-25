################################################################################
#
# Author: Jean-Pierre.Bogler@continental-corporation.com
#
# Configure template for the NodeHealthMonitor
#
# Process this file with autoconf to produce a configure script.
#
# Copyright (C) 2013 Continental Automotive Systems, Inc.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, 
# v. 2.0. If a copy of the MPL was not distributed with this file, You can 
# obtain one at http://mozilla.org/MPL/2.0/.
#
################################################################################

# Initialize autoconf
AC_INIT([node-health-monitor], [1.3.5])
AC_PREREQ([2.50])
AC_COPYRIGHT([Copyright (c) 2013 Continental Automotive GmbH])

# Initialize automake
AM_INIT_AUTOMAKE([tar-ustar])

# Check for basic programs
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL

# Check for basic headers
AC_CHECK_HEADERS([string.h])

# Check for basic types
AC_TYPE_SIZE_T

# Check for basic functions
AC_CHECK_FUNCS([strtol])

# Check for required packages
PKG_CHECK_MODULES([DLT],      [automotive-dlt             >= 2.2.0  ])
PKG_CHECK_MODULES([GIO],      [gio-2.0                    >= 2.30.0 ])
PKG_CHECK_MODULES([GIO_UNIX], [gio-unix-2.0               >= 2.30.0 ])
PKG_CHECK_MODULES([GLIB],     [glib-2.0                   >= 2.30.0 ])
PKG_CHECK_MODULES([GOBJECT],  [gobject-2.0                >= 2.30.0 ])
PKG_CHECK_MODULES([DBUS],     [dbus-1                     >= 1.4.10 ])
PKG_CHECK_MODULES([SYSTEMD],  [libsystemd-daemon          >= 187    ])
PKG_CHECK_MODULES([NSM],      [node-state-manager         >= 1.2.0.0])
PKG_CHECK_MODULES([PCL],      [persistence_client_library >= 0.6.0  ])

# Derive path for storing systemd service files (e. g. /lib/systemd/system)
AC_ARG_WITH([systemdsystemunitdir],
        AS_HELP_STRING([--with-systemdsystemunitdir=DIR], [Directory for systemd service files]),
        [],
        [with_systemdsystemunitdir=$(pkg-config --silence-errors --variable=systemdsystemunitdir systemd)])
AC_SUBST([systemdsystemunitdir], [$with_systemdsystemunitdir])

# Derive path for storing 'dbus' service files (e. g. /usr/share/dbus-1/system-services)
AC_ARG_WITH([dbussystemunitdir],
        AS_HELP_STRING([--with-dbussystemunitdir=DIR], [Directory for D-Bus system service files]),
        [],
        [with_dbussystemunitdir=$(pkg-config --silence-errors --variable=session_bus_services_dir dbus-1)])
AC_SUBST([dbussystemunitdir], [$with_dbussystemunitdir])

# Derive path for storing 'dbus' interface files (e. g. /usr/share/dbus-1/interfaces)
AC_ARG_WITH([dbusinterfacesdir],
        AS_HELP_STRING([--with-dbusinterfacesdir=DIR], [Directory for D-Bus interface files]),
        [],
        [with_dbusinterfacesdir=$(pkg-config --silence-errors --variable=interfaces_dir dbus-1)])
AC_SUBST([dbusinterfacesdir], [$with_dbusinterfacesdir])

# Derive path of the NSM dbus xml models
AC_SUBST([nsmdbusinterfacesdir], [$(pkg-config --silence-errors --variable=dbusinterfacesdir node-state-manager)])

# Define configure output
AC_CONFIG_FILES([ Makefile
                  cfg/Makefile 
                  gen/Makefile
                  inc/Makefile
                  mod/Makefile
                  src/Makefile
                  tst/Makefile
                  cfg/node-health-monitor.service 
                  cfg/org.genivi.NodeHealthMonitor.service 
                  cfg/node-health-monitor.pc ])
AC_OUTPUT
