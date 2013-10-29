################################################################################
#
# Author: Jean-Pierre.Bogler@continental-corporation.com
#
# Makefile template for the node-health-monitor dbus interface
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

# Export the dbus interface descrition of the NHM
dbusinterfaces_DATA = org.genivi.NodeHealthMonitor.Info.xml

# XML model not automatically delivered in "dist", because there is no *.in file
EXTRA_DIST          = $(dbusinterfaces_DATA)