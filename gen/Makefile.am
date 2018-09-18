################################################################################
#
# Author: Jean-Pierre.Bogler@continental-corporation.com
#
# Makefile template for the node-health-monitor generated sources
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

# List generated sources here to assert that they are available at built start
BUILT_SOURCES = nhm-dbus-info.c        \
                nhm-dbus-info.h        \
                nsm-dbus-lc-control.c  \
                nsm-dbus-lc-control.h  \
                nsm-dbus-consumer.c    \
                nsm-dbus-consumer.h    \
                nsm-dbus-lc-consumer.c \
                nsm-dbus-lc-consumer.h

# Delete all generated files on 'make clean'
CLEANFILES    = nhm-dbus-info.c        \
                nhm-dbus-info.h        \
                nsm-dbus-lc-control.c  \
                nsm-dbus-lc-control.h  \
                nsm-dbus-consumer.c    \
                nsm-dbus-consumer.h    \
                nsm-dbus-lc-consumer.c \
                nsm-dbus-lc-consumer.h

# Targets to create generated sources during the build
nhm-dbus-info.c nhm-dbus-info.h: $(top_srcdir)/mod/org.genivi.NodeHealthMonitor.Info.xml
	gdbus-codegen --interface-prefix org.genivi.NodeHealthMonitor. --c-namespace NhmDbus --generate-c-code nhm-dbus-info $(top_srcdir)/mod/org.genivi.NodeHealthMonitor.Info.xml

nsm-dbus-lc-control.c nsm-dbus-lc-control.h: $(nsmdbusinterfacesdir)/org.genivi.NodeStateManager.LifecycleControl.xml
	gdbus-codegen --interface-prefix org.genivi.NodeStateManager.Lifecycle --c-namespace NsmDbusLc --generate-c-code nsm-dbus-lc-control $(nsmdbusinterfacesdir)/org.genivi.NodeStateManager.LifecycleControl.xml

nsm-dbus-consumer.c nsm-dbus-consumer.h: $(nsmdbusinterfacesdir)/org.genivi.NodeStateManager.Consumer.xml
	gdbus-codegen --interface-prefix org.genivi.NodeStateManager. --c-namespace NsmDbus --generate-c-code nsm-dbus-consumer $(nsmdbusinterfacesdir)/org.genivi.NodeStateManager.Consumer.xml

nsm-dbus-lc-consumer.c nsm-dbus-lc-consumer.h: $(nsmdbusinterfacesdir)/org.genivi.NodeStateManager.LifecycleConsumer.xml
	gdbus-codegen --interface-prefix org.genivi.NodeStateManager.LifeCycle --c-namespace NsmDbusLc --generate-c-code nsm-dbus-lc-consumer $(nsmdbusinterfacesdir)/org.genivi.NodeStateManager.LifecycleConsumer.xml
