/** @file
  MISC DXE policy definitions
  
Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef _MISC_DXE_CONFIG_H_
#define _MISC_DXE_CONFIG_H_

#pragma pack(push, 1)

#define MISC_DXE_CONFIG_REVISION 1

/**
  This data structure includes miscellaneous configuration variables such SA thermal device
  control. The data elements should be initialized by a Platform Module.\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                    ///< Offset 0-27 Config Block Header
  UINT32                EnableAbove4GBMmio : 1;    ///< Enable/disable above 4GB MMIO resource support: <b>0=Disable</b>, 1=Enable
  UINT32                RsvdBits0          : 31;   ///< Reserved bits.
  EFI_PHYSICAL_ADDRESS  *RmrrUsbBaseAddress;       ///< The field is used to describe the platform USB Reserved memory for Intel VT-d support. Platform code should provide this information for Intel VT-d DXE driver use
} MISC_DXE_CONFIG;
#pragma pack(pop)

#endif // _MISC_DXE_CONFIG_H_