################################################################################
#
# Author: Jean-Pierre.Bogler@continental-corporation.com
#
# Makefile template for the NodeHealthMonitor
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

# Build trough subfolders. Make sure "gen" is called before "src" and "tst".
SUBDIRS = cfg gen inc mod src tst

# A README is required according to GNU coding standards and autoreconf
# will otherwise fail.  Since we use README.md, this build rule is one
# workaround (there are other ways too)
README: README.md
