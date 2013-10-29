/* NHM - NodeHealthMonitor
 *
 * Definition of stubs for the persistence client library
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef PERSISTENCE_CLIENT_LIBRARY_KEY_STUB_H
#define PERSISTENCE_CLIENT_LIBRARY_KEY_STUB_H

/*******************************************************************************
*
* Exported variables, constants and defines
*
*******************************************************************************/

extern int pclInitLibrary_stub_return;
extern int pclKeyWriteData_stub_return;
extern int pclKeyWriteData_stub_WriteVal;
extern int pclKeyReadData_stub_ReadVal;
extern int pclKeyReadData_stub_return;
extern int pclDeinitLibrary_stub_return;

/*******************************************************************************
*
* Exported functions
*
*******************************************************************************/

int pclInitLibrary_stub  (const char    *appname,
                          int            shutdownMode);
int pclKeyWriteData_stub (unsigned int   ldbid,
                          const char    *resource_id,
                          unsigned int   user_no,
                          unsigned int   seat_no,
                          unsigned char *buffer,
                          int            buffer_size);
int pclKeyReadData_stub  (unsigned int   ldbid,
                          const char    *resource_id,
                          unsigned int   user_no,
                          unsigned int   seat_no,
                          unsigned char *buffer,
                          int            buffer_size);
int pclDeinitLibrary_stub(void);

#endif /* PERSISTENCE_CLIENT_LIBRARY_KEY_STUB_H */
