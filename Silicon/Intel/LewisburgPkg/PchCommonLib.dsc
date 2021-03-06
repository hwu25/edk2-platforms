### @file
#
# Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
#
# This program and the accompanying materials are licensed and made available under
# the terms and conditions of the BSD License which accompanies this distribution.
# The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
###

[LibraryClasses.common]
  GpioLib|$(PCH_PKG)/Library/PeiDxeSmmGpioLib/PeiDxeSmmGpioLib.inf
  PchPolicyLib|$(PCH_PKG)/Library/PeiPchPolicyLib/PeiPchPolicyLib.inf
  PchCycleDecodingLib|$(PCH_PKG)/Library/PeiDxeSmmPchCycleDecodingLib/PeiDxeSmmPchCycleDecodingLib.inf
  PchGbeLib|$(PCH_PKG)/Library/PeiDxeSmmPchGbeLib/PeiDxeSmmPchGbeLib.inf
  PchInfoLib|$(PCH_PKG)/Library/PeiDxeSmmPchInfoLib/PeiDxeSmmPchInfoLib.inf
  PchP2sbLib|$(PCH_PKG)/Library/PeiDxeSmmPchP2sbLib/PeiDxeSmmPchP2sbLib.inf
  PchPcrLib|$(PCH_PKG)/Library/PeiDxeSmmPchPcrLib/PeiDxeSmmPchPcrLib.inf
  PchSbiAccessLib|$(PCH_PKG)/Library/PeiDxeSmmPchSbiAccessLib/PeiDxeSmmPchSbiAccessLib.inf
  PchResetCommonLib|$(PCH_PKG)/LibraryPrivate/BasePchResetCommonLib/BasePchResetCommonLib.inf
  PchPmcLib|$(PCH_PKG)/Library/PeiDxeSmmPchPmcLib/PeiDxeSmmPchPmcLib.inf
