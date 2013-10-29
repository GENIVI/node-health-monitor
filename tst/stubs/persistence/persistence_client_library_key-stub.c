/* NHM - NodeHealthMonitor
 *
 * Implementation of stubs for the persistence client library
 *
 * Author: Jean-Pierre Bogler <Jean-Pierre.Bogler@continental-corporation.com>
 *
 * Copyright (C) 2013 Continental Automotive Systems, Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

/*******************************************************************************
*
* Header includes
*
*******************************************************************************/

/* Own header */
#include <stdio.h>
#include <string.h>
#include <tst/stubs/persistence/persistence_client_library_key-stub.h>

/*******************************************************************************
*
* Exported variables and constants
*
*******************************************************************************/

int pclInitLibrary_stub_return    = 0;
int pclKeyWriteData_stub_return   = 0;
int pclKeyWriteData_stub_WriteVal = 0;
int pclKeyReadData_stub_return    = 0;
int pclKeyReadData_stub_ReadVal   = 0;
int pclDeinitLibrary_stub_return  = 0;

/*******************************************************************************
*
* Interfaces. Exported functions.
*
*******************************************************************************/


/**
 * pclInitLibrary_stub:
 *
 * Stub for pclInitLibrary()
 */
int
pclInitLibrary_stub(const char *appname,
                    int         shutdownMode)
{
  return pclInitLibrary_stub_return;
}


/**
 * pclKeyWriteData_stub:
 *
 * Stub for pclKeyWriteData()
 */
int
pclKeyWriteData_stub(unsigned int ldbid,
                     const char* resource_id,
                     unsigned int user_no,
                     unsigned int seat_no,
                     unsigned char* buffer,
                     int buffer_size)
{
  memcpy(&pclKeyWriteData_stub_WriteVal, buffer, buffer_size);

  return pclKeyWriteData_stub_return;
}

/**
 * pclKeyReadData_stub:
 *
 * Stub for pclKeyReadData()
 */
int pclKeyReadData_stub(unsigned int ldbid,
                        const char* resource_id,
                        unsigned int user_no,
                        unsigned int seat_no,
                        unsigned char* buffer,
                        int buffer_size)
{
  memcpy(buffer, &pclKeyReadData_stub_ReadVal, buffer_size);

  return pclKeyReadData_stub_return;
}


/**
 * pclDeinitLibrary_stub:
 *
 * Stub for pclDeinitLibrary()
 */
int
pclDeinitLibrary_stub(void)
{
  return pclDeinitLibrary_stub_return;
}
