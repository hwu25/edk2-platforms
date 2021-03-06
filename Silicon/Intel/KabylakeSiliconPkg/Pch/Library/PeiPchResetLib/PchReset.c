/** @file
  PCH RESET PEIM DRIVER.

Copyright (c) 2017 - 2019, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include <PiPei.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <PchAccess.h>
#include <Ppi/Reset2.h>
#include <Ppi/PchReset.h>
#include <Library/ResetSystemLib.h>
#include <PchResetPlatformSpecific.h>

VOID
EFIAPI
ResetPlatformSpecific (
  IN UINTN            DataSize,
  IN VOID             *ResetData OPTIONAL
  );


/**
  Resets the entire platform.

  @param[in] ResetType            UEFI defined reset type.
  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.

**/
VOID
EFIAPI
ResetSystem (
  IN EFI_RESET_TYPE     ResetType,
  IN EFI_STATUS         ResetStatus,
  IN UINTN              DataSize,
  IN VOID               *ResetData OPTIONAL
  )
{
  switch (ResetType) {
  case EfiResetWarm:
    ResetWarm ();
    break;

  case EfiResetCold:
    ResetCold ();
    break;

  case EfiResetShutdown:
    ResetShutdown ();
    return;

  case EfiResetPlatformSpecific:
    ResetPlatformSpecific (DataSize, ResetData);
    return;

  default:
    return;
  }

  //
  // Given we should have reset getting here would be bad
  //
  ASSERT (FALSE);
}

/**
  Execute Pch Reset from the host controller.

  @param[in] This                 Pointer to the PCH_RESET_PPI instance.
  @param[in] PchResetType         Pch Reset Types which includes PchColdReset, PchWarmReset,
                                  PchShutdownReset, PchGlobalReset

  @retval EFI_SUCCESS             Successfully completed.
  @retval EFI_INVALID_PARAMETER   If ResetType is invalid.
**/
EFI_STATUS
EFIAPI
Reset (
  IN PCH_RESET_PPI        *This,
  IN PCH_RESET_TYPE       PchResetType
  )
{
  PCH_RESET_DATA          ResetData;

  switch (PchResetType) {
    case PchColdReset:
      ResetCold();
      break;

    case PchWarmReset:
      ResetWarm();
      break;

    case PchShutdownReset:
      ResetShutdown();
      break;

    case PchGlobalReset:
      CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
      StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
      ResetPlatformSpecific (sizeof (PCH_RESET_DATA), &ResetData);
      break;

    default:
      return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

/**
  Initialize PCH Reset APIs

  @retval EFI_SUCCESS             APIs are installed successfully
  @retval EFI_OUT_OF_RESOURCES    Can't allocate pool
**/
EFI_STATUS
EFIAPI
PchInitializeReset (
  VOID
  )
{
  EFI_STATUS              Status;
  PCH_RESET_PPI           *PeiPchResetPpi;
  EFI_PEI_PPI_DESCRIPTOR  *PeiPchResetDescriptor;
  EFI_PEI_RESET2_PPI      *EfiPeiReset2Ppi;
  EFI_PEI_PPI_DESCRIPTOR  *EfiPeiReset2Descriptor;

  DEBUG ((DEBUG_INFO, "PchInitializeReset() Start\n"));

  PeiPchResetDescriptor = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  PeiPchResetPpi = (PCH_RESET_PPI *) AllocateZeroPool (sizeof (PCH_RESET_PPI));
  if ((PeiPchResetDescriptor == NULL) ||
      (PeiPchResetPpi == NULL)) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }

  ///
  /// Initialize the Reset ppi instance
  ///
  PeiPchResetPpi->Reset         = Reset;
  PeiPchResetDescriptor->Flags  = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  PeiPchResetDescriptor->Guid   = &gPchResetPpiGuid;
  PeiPchResetDescriptor->Ppi    = PeiPchResetPpi;

  ///
  /// Install the PCH RESET PPI
  ///
  Status = PeiServicesInstallPpi (PeiPchResetDescriptor);
  ASSERT_EFI_ERROR (Status);

  EfiPeiReset2Descriptor = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  EfiPeiReset2Ppi = (EFI_PEI_RESET2_PPI *) AllocateZeroPool (sizeof (EFI_PEI_RESET2_PPI));
  if ((EfiPeiReset2Descriptor == NULL) ||
      (EfiPeiReset2Ppi == NULL)) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }

  ///
  /// Initialize the EFI Reset2 ppi instance
  ///
  EfiPeiReset2Ppi->ResetSystem  = ResetSystem;

  EfiPeiReset2Descriptor->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  EfiPeiReset2Descriptor->Guid  = &gEfiPeiReset2PpiGuid;
  EfiPeiReset2Descriptor->Ppi   = EfiPeiReset2Ppi;

  Status = PeiServicesInstallPpi (EfiPeiReset2Descriptor);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "PchInitializeReset() End\n"));

  return Status;
}

