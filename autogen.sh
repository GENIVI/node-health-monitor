#!/bin/sh -e
#
# Author: Jean-Pierre.Bogler@continental-corporation.com
#
# Script to create necessary files/folders from a fresh git check out.
#
# Copyright (C) 2013 Continental Automotive Systems, Inc.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# Date           Author             Reason
# 05th Feb. 2013 Jean-Pierre Bogler Initial creation
#
###############################################################################

autoreconf --verbose --install --force
./configure $@
