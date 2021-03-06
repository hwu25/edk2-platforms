/** @file
  VT-d policy definitions.

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef _VTD_CONFIG_H_
#define _VTD_CONFIG_H_

#pragma pack(push, 1)

#define SA_VTD_ENGINE_NUMBER        2

#define VTD_CONFIG_REVISION 1

/**
  The data elements should be initialized by a Platform Module.
  The data structure is for VT-d driver initialization\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER  Header;                                       ///< Offset 0-27 Config Block Header
  /**
    Offset 28:0 :
    VT-D Support can be verified by reading CAP ID register as expalined in BIOS Spec.
    This policy is for debug purpose only.
    If VT-D is not supported, all other policies in this config block will be ignored.
    <b>0 = To use Vt-d</b>;
    1 = Avoids programming Vtd bars, Vtd overrides and DMAR table.
  **/
  UINT32        VtdDisable               : 1;
  UINT32        X2ApicOptOut             : 1;       ///< Offset 28:1 :This field is used to enable the X2APIC_OPT_OUT bit in the DMAR table. 1=Enable/Set and <b>0=Disable/Clear</b>
  UINT32        RsvdBits0                : 30;      ///< Offset 28:2 :Reserved bits for future use
  UINT32        BaseAddress[SA_VTD_ENGINE_NUMBER];  ///< Offset 32: This field is used to describe the base addresses for VT-d function: <b>BaseAddress[0]=0xFED90000, BaseAddress[0]=0xFED91000 </b>
} VTD_CONFIG;
#pragma pack(pop)

#endif   //  _VTD_CONFIG_H_
