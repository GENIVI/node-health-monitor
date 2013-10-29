#ifndef NODEHEALTHMONITOR_H
#define NODEHEALTHMONITOR_H

/*******************************************************************************
*
* Author: Jean-Pierre.Bogler@continental-corporation.com
*
* Header file of the NodeHealthMonitor
*
* This header file defines the data types and settings that should be used to
* communicate to the NHM over D-Bus.
*
* Copyright (C) 2013 Continental Automotive Systems, Inc.
*
* This Source Code Form is subject to the terms of the Mozilla Public License,
* v. 2.0. If a copy of the MPL was not distributed with this file, You can
* obtain one at http://mozilla.org/MPL/2.0/.
*
* Date             Author              Reason
* 05th Feb. 2013   Jean-Pierre Bogler  Initial revision
*
*******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * NHM interface version. The lower significant byte is equal 0 for released version only.
 */
#define NODEHEALTHMONITOR_INTERFACE_VERSION 0x01000001UL

/*****************************************************************************
  HEADER FILE INCLUDES
******************************************************************************/

/*
 * Module version. The lower significant byte is equal 0 for released version only.
 */
#define NHM_INTERFACE_VERSION  0x01000001U

#define NHM_BUS_TYPE    2                               /**< Defines bus type according to GBusType  */
#define NHM_BUS_NAME    "org.genivi.NodeHealthMonitor"  /**< The bus name of the Node Health Monitor */
#define NHM_INFO_OBJECT "/org/genivi/NodeHealthMonitor" /**< D-Bus object path                       */

/*****************************************************************************
  TYPE
******************************************************************************/

/* This enum will be used to report the status of an application before/after or during a failure */
typedef enum
{
    NhmAppStatus_Failed,     /**< Used when an application has failed                                      */
    NhmAppStatus_Restarting, /**< Used when an application has failed but is in process of being restarted */
    NhmAppStatus_Ok          /**< Used when an application failed but has correctly been restarted         */
} NhmAppStatus_e;


/* This enum will be used for indicating the status of method calls */
typedef enum
{
    NhmErrorStatus_Ok,                 /**< This value will be used to state that the method worked as expected                                  */
    NhmErrorStatus_Error,              /**< This value can be used to state that an error occurred handling the request                          */
    NhmErrorStatus_UnknownApp,         /**< This value will be set when the passed string does not correspond to a failed application            */
    NhmErrorStatus_RestartNotPossible  /**< This value will be used when an application requests a node restart but it is not currently possible */
} NhmErrorStatus_e;

#ifdef __cplusplus
}
#endif

#endif /* NODEHEALTHMONITOR_H */
