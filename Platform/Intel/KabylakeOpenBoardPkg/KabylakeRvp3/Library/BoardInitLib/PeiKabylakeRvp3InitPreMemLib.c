/** @file

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiPei.h>
#include <SaPolicyCommon.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PciLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>

#include <Library/PeiSaPolicyLib.h>
#include <Library/BoardInitLib.h>
#include <PchAccess.h>
#include <Library/GpioNativeLib.h>
#include <Library/GpioLib.h>
#include <GpioPinsSklLp.h>
#include <GpioPinsSklH.h>
#include <Library/GpioExpanderLib.h>
#include <SioRegs.h>
#include <Library/PchPcrLib.h>
#include <Library/SiliconInitLib.h>

#include "PeiKabylakeRvp3InitLib.h"

#include <ConfigBlock.h>
#include <ConfigBlock/MemoryConfig.h>

//
// Reference RCOMP resistors on motherboard - for SKL RVP1
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT16 RcompResistorSklRvp1[SA_MRC_MAX_RCOMP] = { 200, 81, 162 };
//
// RCOMP target values for RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk - for SKL RVP1
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT16 RcompTargetSklRvp1[SA_MRC_MAX_RCOMP_TARGETS] = { 100, 40, 40, 23, 40 };

/**
  SkylaeA0Rvp3 board configuration init function for PEI pre-memory phase.

  PEI_BOARD_CONFIG_PCD_INIT

  @param  Content  pointer to the buffer contain init information for board init.

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_INVALID_PARAMETER   The parameter is NULL.
**/
EFI_STATUS
EFIAPI
KabylakeRvp3InitPreMem (
  VOID
  )
{
  PcdSet32S (PcdPcie0WakeGpioNo, 0);
  PcdSet8S  (PcdPcie0HoldRstExpanderNo, 0);
  PcdSet32S (PcdPcie0HoldRstGpioNo, 8);
  PcdSetBoolS (PcdPcie0HoldRstActive, TRUE);
  PcdSet8S  (PcdPcie0PwrEnableExpanderNo, 0);
  PcdSet32S (PcdPcie0PwrEnableGpioNo, 16);
  PcdSetBoolS (PcdPcie0PwrEnableActive, FALSE);

  //
  // HSIO PTSS Table
  //
  PcdSet32S (PcdSpecificLpHsioPtssTable1,     (UINTN) PchLpHsioPtss_Bx_KabylakeRvp3);
  PcdSet16S (PcdSpecificLpHsioPtssTable1Size, (UINTN) PchLpHsioPtss_Bx_KabylakeRvp3_Size);
  PcdSet32S (PcdSpecificLpHsioPtssTable2,     (UINTN) PchLpHsioPtss_Cx_KabylakeRvp3);
  PcdSet16S (PcdSpecificLpHsioPtssTable2Size, (UINTN) PchLpHsioPtss_Cx_KabylakeRvp3_Size);

  //
  // DRAM related definition
  //
  PcdSet8S (PcdSaMiscUserBd, 5);

  PcdSet8S (PcdMrcSpdAddressTable0, 0xA2);
  PcdSet8S (PcdMrcSpdAddressTable1, 0xA0);
  PcdSet8S (PcdMrcSpdAddressTable2, 0xA2);
  PcdSet8S (PcdMrcSpdAddressTable3, 0xA0);

  PcdSet32S (PcdMrcDqByteMap, (UINTN) mDqByteMapSklRvp3);
  PcdSet16S (PcdMrcDqByteMapSize, sizeof (mDqByteMapSklRvp3));
  PcdSet32S (PcdMrcDqsMapCpu2Dram, (UINTN) mDqsMapCpu2DramSklRvp3);
  PcdSet16S (PcdMrcDqsMapCpu2DramSize, sizeof (mDqsMapCpu2DramSklRvp3));
  PcdSet32S (PcdMrcRcompResistor, (UINTN) RcompResistorSklRvp1);
  PcdSet32S (PcdMrcRcompTarget, (UINTN) RcompTargetSklRvp1);

    PcdSet32S (PcdMrcSpdData, (UINTN) mSkylakeRvp3Spd110);
    PcdSet16S (PcdMrcSpdDataSize, mSkylakeRvp3Spd110Size);

  PcdSetBoolS (PcdIoExpanderPresent, TRUE);
  
  return EFI_SUCCESS;
}

#define SIO_RUNTIME_REG_BASE_ADDRESS                          0x0680

/**
  Configures GPIO

  @param[in]  GpioTable       Point to Platform Gpio table
  @param[in]  GpioTableCount  Number of Gpio table entries

**/
VOID
ConfigureGpio (
  IN GPIO_INIT_CONFIG                 *GpioDefinition,
  IN UINT16                           GpioTableCount
  )
{
  EFI_STATUS          Status;

  DEBUG ((DEBUG_INFO, "ConfigureGpio() Start\n"));

  Status = GpioConfigurePads (GpioTableCount, GpioDefinition);

  DEBUG ((DEBUG_INFO, "ConfigureGpio() End\n"));
}

/**
  Configure GPIO Before Memory is not ready.

**/
VOID
GpioInitPreMem (
  VOID
  )
{
  // ConfigureGpio ();
}

/**
  Configure Super IO

**/
VOID
SioInit (
  VOID
  )
{
  //
  // Program and Enable Default Super IO Configuration Port Addresses and range
  //
  PchLpcGenIoRangeSet (PcdGet16 (PcdLpcSioConfigDefaultPort) & (~0xF), 0x10);

  //
  // 128 Byte Boundary and SIO Runtime Register Range is 0x0 to 0xF;
  //
  PchLpcGenIoRangeSet (SIO_RUNTIME_REG_BASE_ADDRESS  & (~0x7F), 0x10);

  return;
}

/**
  Configues the IC2 Controller on which GPIO Expander Communicates.
  This Function is to enable the I2CGPIOExapanderLib to programm the Gpios
  Complete intilization will be done in later Stage

**/
VOID
EFIAPI
I2CGpioExpanderInitPreMem(
  VOID
  )
{
  ConfigureSerialIoController (PchSerialIoIndexI2C4, PchSerialIoAcpiHidden);
  SerialIoI2cGpioInit (PchSerialIoIndexI2C4, PchSerialIoAcpiHidden, PchSerialIoIs33V);
}

/**
  Configure GPIO and SIO before memory ready

  @retval  EFI_SUCCESS   Operation success.
**/
EFI_STATUS
EFIAPI
KabylakeRvp3BoardInitBeforeMemoryInit (
  VOID
  )
{
  KabylakeRvp3InitPreMem ();

  //
  // Configures the I2CGpioExpander
  //
  if (PcdGetBool (PcdIoExpanderPresent)) {
    I2CGpioExpanderInitPreMem();
  }

  GpioInitPreMem ();
  SioInit ();
    
  ///
  /// Do basic PCH init
  ///
  SiliconInit ();

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
KabylakeRvp3BoardDebugInit (
  VOID
  )
{
  ///
  /// Do Early PCH init
  ///
  EarlySiliconInit ();
  return EFI_SUCCESS;
}

EFI_BOOT_MODE
EFIAPI
KabylakeRvp3BoardBootModeDetect (
  VOID
  )
{
  return BOOT_WITH_FULL_CONFIGURATION;
}

