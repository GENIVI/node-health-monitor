################################################################################
#
# Author: Jean-Pierre.Bogler@continental-corporation.com
#
# Makefile template for the node-health-monitor config files
#
# Process this file with automake to produce a Makefile.in.
#
# Copyright (C) 2013 Continental Automotive Systems, Inc.
#
# This Source Code Form is subject to the terms of the Mozilla Public License,
# v. 2.0. If a copy of the MPL was not distributed with this file, You can 
# obtain one at http://mozilla.org/MPL/2.0/.
#
# Date             Author              Reason
# 05th Feb. 2013   Jean-Pierre Bogler  Initial revision
#
################################################################################

# Write the package config file of the NHM to it destination
pkgconfigdir   = $(libdir)/pkgconfig
pkgconfig_DATA = node-health-monitor.pc

# Write the initial config file of the NHM to the config destination
sysconf_DATA = node-health-monitor.conf

# Write the systemd unit file of the NHM to the related systemd directory
systemdsystemunit_DATA = node-health-monitor.service

# Write the dbus service file (start NHM on dbus demand) to related dbus path
dbussystemunit_DATA = org.genivi.NodeHealthMonitor.service

# Add config file to distribution (*.in files were automatically added)
EXTRA_DIST = $(sysconf_DATA)
