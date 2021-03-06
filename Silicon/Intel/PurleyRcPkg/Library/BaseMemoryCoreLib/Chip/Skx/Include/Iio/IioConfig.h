/** @file

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _IIO_CONFIG_H
#define _IIO_CONFIG_H

#pragma pack(1) //to align members on byte boundary
typedef struct {

/**
==================================================================================================
==================================      VTd Setup Options       ==================================
==================================================================================================
**/

    UINT8                   VTdSupport;
    UINT8                   InterruptRemap;
    UINT8                   CoherencySupport;
    UINT8                   ATS;
    UINT8                   PostedInterrupt;
    UINT8                   PassThroughDma;

/**
==================================================================================================
==================================      PCIE Setup Options       ==================================
==================================================================================================
**/
    UINT8   IioPresent[MAX_SOCKET];
    UINT8   VtdAcsWa;

    // Platform data needs to update these PCI Configuration settings
    UINT8    SLOTIMP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];          // Slot Implemented - PCIE Capabilities (D0-10 / F0 / R0x92 / B8)
    UINT16   SLOTPSP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];          // Physical slot Number - Slot Capabilities (D0-10 / F0 / R0xA4 / B31:19). Change to use 13 bits instead of 8
    UINT8    SLOTEIP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];          // Electromechanical Interlock Present - Slot Capabilities (D0-10 / F0 / R0xA4 / B17)
    UINT8    SLOTSPLS[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];         // Slot Power Limit Scale - Slot Capabilities (D0-10 / F0 / R0xA4 / B16:15)
    UINT8    SLOTSPLV[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];         // Slot Power Limit Value - Slot Capabilities (D0-10 / F0 / R0xA4 / B14:7)
    UINT8    SLOTHPCAP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];        // Slot Hot Plug capable - Slot Capabilities (D0-10 / F0 / R0xA4 / B6)
    UINT8    SLOTHPSUP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];        // Hot Plug surprise supported - Slot Capabilities (D0-10 / F0 / R0xA4 / B5)
    UINT8    SLOTPIP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];          // Power Indicator Present - Slot Capabilities (D0-10 / F0 / R0xA4 / B4)
    UINT8    SLOTAIP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];          // Attention Inductor Present - Slot Capabilities (D0-10 / F0 / R0xA4 / B3)
    UINT8    SLOTMRLSP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];        // MRL Sensor Present - Slot Capabilities (D0-10 / F0 / R0xA4 / B2)
    UINT8    SLOTPCP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];          // Power Controller Present - Slot Capabilities (D0-10 / F0 / R0xA4 /B1)
    UINT8    SLOTABP[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];          // Attention Button Present - Slot Capabilities (D0-10 / F0 / R0xA4 / B0)
    UINT8    PcieSSDCapable[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];          // Indicate if Port will PcieSSD capable.

    // General PCIE Configuration
    UINT8   ConfigIOU0[MAX_SOCKET];         // 00-x4x4x4x4, 01-x4x4x8NA, 02-x8NAx4x4, 03-x8NAx8NA, 04-x16 (P5p6p7p8)
    UINT8   ConfigIOU1[MAX_SOCKET];         // 00-x4x4x4x4, 01-x4x4x8NA, 02-x8NAx4x4, 03-x8NAx8NA, 04-x16 (P9p10p11p12)
    UINT8   ConfigIOU2[MAX_SOCKET];         // 00-x4x4x4x4, 01-x4x4x8NA, 02-x8NAx4x4, 03-x8NAx8NA, 04-x16 (P1p2p3p4)
    UINT8   ConfigMCP0[MAX_SOCKET];         // 04-x16 (p13)
    UINT8   ConfigMCP1[MAX_SOCKET];         // 04-x16 (p14)
    UINT8   CompletionTimeoutGlobal;            //
    UINT8   CompletionTimeoutGlobalValue;
    UINT8   CompletionTimeout[MAX_SOCKET];  // On Setup
    UINT8   CompletionTimeoutValue[MAX_SOCKET]; // On Setup
    UINT8   CoherentReadPart;
    UINT8   CoherentReadFull;
    UINT8   PcieGlobalAspm;                    //
    UINT8   StopAndScream;                     //
    UINT8   SnoopResponseHoldOff;              //
    //
    // PCIE capability
    //
    UINT8   PCIe_LTR;                          //
    UINT8   PcieExtendedTagField;              //
    UINT8   PCIe_AtomicOpReq;                  //
    UINT8   PcieMaxReadRequestSize;            //


    UINT8   RpCorrectableErrorEsc[MAX_SOCKET];           //on Setup
    UINT8   RpUncorrectableNonFatalErrorEsc[MAX_SOCKET]; //on Setup
    UINT8   RpUncorrectableFatalErrorEsc[MAX_SOCKET];    //on Setup


    // mixc PCIE configuration
    UINT8    PcieLinkDis[MAX_TOTAL_PORTS];          // On Setup
    UINT8    PcieAspm[MAX_TOTAL_PORTS];             // On Setup
    UINT8    PcieCommonClock[MAX_TOTAL_PORTS];  // On Setup
    UINT8    PcieMaxPayload[MAX_TOTAL_PORTS];       // On Setup PRD
    UINT8    PcieDState[MAX_TOTAL_PORTS];           // On Setup
    UINT8    PcieL0sLatency[MAX_TOTAL_PORTS];       //On Setup
    UINT8    PcieL1Latency[MAX_TOTAL_PORTS];        //On Setup
    UINT8    MsiEn[MAX_TOTAL_PORTS];                // On Setup
    UINT8    ExtendedSync[MAX_TOTAL_PORTS];         // On Setup
    UINT8    InbandPresenceDetect[MAX_TOTAL_PORTS]; // Not implemented in code
    UINT8    PciePortDisable[MAX_TOTAL_PORTS];      // Not implemented in code
    UINT8    PciePmeIntEn[MAX_TOTAL_PORTS];         // Not implemented in code
    UINT8    IODC[MAX_TOTAL_PORTS];                 // On Setup
    //
    // VPP Control
    //
    UINT8    VppEnable[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];        // 00 -- Disable, 01 -- Enable  //no setup option defined- aj
    UINT8    VppPort[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];          // 00 -- Port 0, 01 -- Port 1   //no setup option defined- aj
    UINT8    VppAddress[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];       // 01-07 for SMBUS address of Vpp   //no setup option defined- aj

    //
    // PCIE setup options for Link Control2
    //
    UINT8    PciePortLinkSpeed[MAX_TOTAL_PORTS];   //on Setup
    UINT8    ComplianceMode[MAX_TOTAL_PORTS];   // On Setup  PRD
    UINT8    PciePortLinkMaxWidth[MAX_TOTAL_PORTS]; // On Setup
    UINT8    DeEmphasis[MAX_TOTAL_PORTS];       // On Setup

    //
    // PCIE setup options for MISCCTRLSTS
    //
    UINT8    EOI[MAX_TOTAL_PORTS];              // On Setup
    UINT8    MSIFATEN[MAX_TOTAL_PORTS];         //On Setup.
    UINT8    MSINFATEN[MAX_TOTAL_PORTS];        //On Setup.
    UINT8    MSICOREN[MAX_TOTAL_PORTS];         //On Setup.
    UINT8    ACPIPMEn[MAX_TOTAL_PORTS];         //On Setup
    UINT8    DISL0STx[MAX_TOTAL_PORTS];         //On Setup
    UINT8    P2PWrtDis[MAX_TOTAL_PORTS];        //On Setup Peer 2 Peer
    UINT8    P2PRdDis[MAX_TOTAL_PORTS];         //On Setup Peer 2 peer
    UINT8    DisPMETOAck[MAX_TOTAL_PORTS];      //On Setup
    UINT8    ACPIHP[MAX_TOTAL_PORTS];           //On Setup
    UINT8    ACPIPM[MAX_TOTAL_PORTS];           //On Setup
    UINT8    SRIS[MAX_TOTAL_PORTS];             //On Setup
    UINT8    TXEQ[MAX_TOTAL_PORTS];             //On Setup
    UINT8    ECRC[MAX_TOTAL_PORTS];             //On Setup
    //
    // PCIE RAS (Errors)
    //

    UINT8   PcieUnsupportedRequests[MAX_TOTAL_PORTS];   // Unsupported Request per-port option
    UINT8   Serr;
    UINT8   Perr;
    UINT8   IioErrorEn;
    UINT8   LerEn;
    UINT8   WheaPcieErrInjEn;

    //
    // PciePll
    //
    UINT8    PciePllSsc;                        //On Setup

    //
    // PCIE  Link Training Ctrl
    //

/**
==================================================================================================
==================================    Crystal Beach 3 Setup Options    ===========================
==================================================================================================
**/
      UINT8                 Cb3DcaEn[MAX_SOCKET];           // on setup
      UINT8                 Cb3DmaEn[TOTAL_CB3_DEVICES];        // on setup
      UINT8                 Cb3NoSnoopEn[TOTAL_CB3_DEVICES];    // on setup
      UINT8                 DisableTPH;
      UINT8                 PrioritizeTPH;
      UINT8                 CbRelaxedOrdering;
/**
==================================================================================================
==================================    MISC IOH Setup Options            ==========================
==================================================================================================
**/

    // The following are for hiding each individual device and function
    UINT8   PEXPHIDE[MAX_SOCKET*NUMBER_PORTS_PER_SOCKET];  // Hide any of the DMI or PCIE devices - SKT 0,1,2,3; Device 0-10 PRD
    UINT8   PCUF6Hide;                            // Hide Device PCU Device 30, Function 6
    UINT8   EN1K;                                 // Enable/Disable 1K granularity of IO for P2P bridges 0:20:0:98 bit 2
    UINT8   DualCvIoFlow;                         // Dual CV IO Flow
    UINT8   PcieBiosTrainEnable;                  // Used as a work around for A0 PCIe
    UINT8   MultiCastEnable;                      // MultiCastEnable test enable
    UINT8   McastBaseAddrRegion;                  // McastBaseAddrRegion
    UINT8   McastIndexPosition;                   // McastIndexPosition
    UINT8   McastNumGroup;                        // McastNumGroup
    UINT8   MctpEn;

    UINT8   LegacyVgaSoc;
    UINT8   LegacyVgaStack;

    UINT8   HidePEXPMenu[MAX_TOTAL_PORTS];          // to suppress /display the PCIe port menu

/**
==================================================================================================
==================================    NTB Related Setup Options ==========================
==================================================================================================
**/
  UINT8   NtbPpd[MAX_NTB_PORTS];                   //on setup option
  UINT8   NtbBarSizeOverride[MAX_NTB_PORTS];       //on setup option
  UINT8   NtbSplitBar[MAX_NTB_PORTS];             //on setup option
  UINT8   NtbBarSizePBar23[MAX_NTB_PORTS];         //on setup option
  UINT8   NtbBarSizePBar45[MAX_NTB_PORTS];         //on setup option
  UINT8   NtbBarSizePBar4[MAX_NTB_PORTS];          //on setup option
  UINT8   NtbBarSizePBar5[MAX_NTB_PORTS];          //on setup option
  UINT8   NtbBarSizeSBar23[MAX_NTB_PORTS];         //on setup option
  UINT8   NtbBarSizeSBar45[MAX_NTB_PORTS];         //on setup option
  UINT8   NtbBarSizeSBar4[MAX_NTB_PORTS];          //on setup option
  UINT8   NtbBarSizeSBar5[MAX_NTB_PORTS];          //on setup option
  UINT8   NtbSBar01Prefetch[MAX_NTB_PORTS];        //on setup option
  UINT8   NtbXlinkCtlOverride[MAX_NTB_PORTS];      //on setup option

/**
==================================================================================================
==================================    VMD Related Setup Options ==========================
==================================================================================================
**/
  UINT8   VMDEnabled[MAX_VMD_STACKS];
  UINT8   VMDPortEnable[MAX_VMD_PORTS];
  UINT8   VMDHotPlugEnable[MAX_VMD_STACKS];
  UINT8   VMDCfgBarSz[MAX_VMD_STACKS];
  UINT8   VMDCfgBarAttr[MAX_VMD_STACKS];
  UINT8   VMDMemBarSz1[MAX_VMD_STACKS];
  UINT8   VMDMemBar1Attr[MAX_VMD_STACKS];
  UINT8   VMDMemBarSz2[MAX_VMD_STACKS];
  UINT8   VMDMemBar2Attr[MAX_VMD_STACKS];

  /**
  ==================================================================================================
  ==================================    PcieSSD Related Setup Options ==========================
  ==================================================================================================
  **/
  UINT8   PcieAICEnabled[MAX_VMD_STACKS];                         // Indicate if PCIE AIC Device will be connected behind an specific IOUx
  UINT8   PcieAICPortEnable[MAX_VMD_PORTS];
  UINT8   PcieAICHotPlugEnable[MAX_VMD_STACKS];

/**
==================================================================================================
==================================    Gen3 Related Setup Options ==========================
==================================================================================================
**/

  //PCIE Global Option
  UINT8   NoSnoopRdCfg;                             //on Setup
  UINT8   NoSnoopWrCfg;                             //on Setup
  UINT8   MaxReadCompCombSize;                      //on Setup
  UINT8   ProblematicPort;                          //on Setup
  UINT8   DmiAllocatingFlow;                        //on Setup
  UINT8   PcieAllocatingFlow;                       //on Setup
  UINT8   PcieHotPlugEnable;                        //on Setup
  UINT8   PcieAcpiHotPlugEnable;                    //on Setup
  UINT8   HaltOnDmiDegraded;                        //on Setup
  UINT8   RxClockWA;
  UINT8   GlobalPme2AckTOCtrl;                      //on Setup

  UINT8   PcieSlotOprom1;                           //On Setup
  UINT8   PcieSlotOprom2;                           //On Setup
  UINT8   PcieSlotOprom3;                           //On Setup
  UINT8   PcieSlotOprom4;                           //On Setup
  UINT8   PcieSlotOprom5;                           //On Setup
  UINT8   PcieSlotOprom6;                           //On Setup
  UINT8   PcieSlotOprom7;                           //On Setup
  UINT8   PcieSlotOprom8;                           //On Setup
  UINT8   PcieSlotItemCtrl;                         //On Setup
  UINT8   PcieRelaxedOrdering;                      //On Setup
  UINT8   PciePhyTestMode;                          //On setup
/**
==================================================================================================
==================================    IOAPIC Related Setup Options ==========================
==================================================================================================
**/

  UINT8   DevPresIoApicIio[TOTAL_IIO_STACKS];
/**
==================================================================================================
==================================    Security Related Setup Options ==========================
==================================================================================================
**/
  UINT8   LockChipset;
  UINT8   PeciInTrustControlBit;
  UINT8   ProcessorX2apic;
  UINT8   ProcessorMsrLockControl;

/**
==================================================================================================
==================================    Iio Related Setup Options ==========================
==================================================================================================
**/
  UINT8   RtoEnable;                     // On Setup
  UINT8   RtoLtssmLogger;                // On Setup
  UINT8   RtoLtssmLoggerStop;            // On Setup
  UINT8   RtoLtssmLoggerSpeed;           // On Setup
  UINT8   RtoLtssmLoggerMask;            // On Setup
  UINT8   RtoJitterLogger;               // On Setup
  UINT32  RtoSocketDevFuncHide[MAX_DEVHIDE_REGS_PER_SYSTEM];     // On Setup
  UINT8   RtoGen3NTBTestCard[MAX_TOTAL_PORTS];  // On Setup

  UINT8   RtoGen3OverrideMode[MAX_TOTAL_PORTS];  		//On Setup
  UINT8   RtoGen3TestCard[MAX_TOTAL_PORTS];				//On Setup
  UINT8   RtoGen3ManualPh2_Precursor[MAX_TOTAL_PORTS];	//On Setup
  UINT8   RtoGen3ManualPh2_Cursor[MAX_TOTAL_PORTS];		//On Setup
  UINT8   RtoGen3ManualPh2_Postcursor[MAX_TOTAL_PORTS];	//On Setup
  UINT8   RtoGen3ManualPh3_Precursor[MAX_TOTAL_PORTS];	//On Setup
  UINT8   RtoGen3ManualPh3_Cursor[MAX_TOTAL_PORTS];		//On Setup
  UINT8   RtoGen3ManualPh3_Postcursor[MAX_TOTAL_PORTS];	//On Setup
  UINT8   RtoDnTxPreset[MAX_TOTAL_PORTS];				//On Setup
  UINT8   RtoRxPreset[MAX_TOTAL_PORTS];					//On Setup
  UINT8   RtoUpTxPreset[MAX_TOTAL_PORTS];				//On Setup

  UINT8   InboundConfiguration[MAX_TOTAL_PORTS];		//On Setup
  
} IIO_CONFIG;
#pragma pack()

#endif // _IIO_CONFIG_H
