
#define DMC0_BASE 0x10600000

#define CONCONTROL VA(DMC0_BASE + 0)
#define MEMCONTROL VA(DMC0_BASE + 4)
#define MEMCONFIG0 VA(DMC0_BASE + 8)
#define MEMCONFIG1 VA(DMC0_BASE + 0xC)
#define DIRECTCMD VA(DMC0_BASE + 0x10)
#define PRECHCONFIG VA(DMC0_BASE + 0x14)

#define PHYCONTROL0 VA(DMC0_BASE + 0x18)
#define PHYCONTROL1 VA(DMC0_BASE + 0x1C)
#define PHYCONTROL2 VA(DMC0_BASE + 0x20)
#define PHYCONTROL3 VA(DMC0_BASE + 0x24)

#define PWRDNCONFIG VA(DMC0_BASE + 0x28)
#define TIMINGAREF VA(DMC0_BASE + 0x30)
#define TIMINGROW VA(DMC0_BASE + 0x34)
#define TIMINGDATA VA(DMC0_BASE + 0x38)

#define TIMINGPOWER VA(DMC0_BASE + 0x3c)
#define PHYSTATUS VA(DMC0_BASE + 0x40)
#define PHYZQCONTROL VA(DMC0_BASE + 0x44)
#define CHIP0STATUS VA(DMC0_BASE + 0x48)
#define CHIP1STATUS VA(DMC0_BASE + 0x4c)
#define AREFSTATUS 	VA(DMC0_BASE + 0x50)
#define MRSTATUS 	VA(DMC0_BASE + 0x54)
#define PHYTEST0 	VA(DMC0_BASE + 0x58)
#define PHYTEST1 	VA(DMC0_BASE + 0x5c)
#define QOSCONTROL0 VA(DMC0_BASE + 0x60)
#define QOSCONFIG0	VA(DMC0_BASE + 0x64)
#define QOSCONTROL1 VA(DMC0_BASE + 0x68)
#define QOSCONFIG1 	VA(DMC0_BASE + 0x6c)
#define QOSCONTROL2 VA(DMC0_BASE + 0x70)
#define QOSCONFIG2 	VA(DMC0_BASE + 0x74)
#define QOSCONTROL3 VA(DMC0_BASE + 0x78)
#define QOSCONFIG3 	VA(DMC0_BASE + 0x7c)

#define QOSCONTROL4 VA(DMC0_BASE + 0x80)
#define QOSCONFIG4 	VA(DMC0_BASE + 0x84)

#define QOSCONFIG4 	VA(DMC0_BASE + 0x84)
#define QOSCONTROL5 VA(DMC0_BASE + 0x88)
#define QOSCONFIG5 	VA(DMC0_BASE + 0x8c)
#define QOSCONTROL6 	VA(DMC0_BASE + 0x90)
#define QOSCONFIG6 		VA(DMC0_BASE + 0x94)
#define QOSCONTROL7 	VA(DMC0_BASE + 0x98)
#define QOSCONFIG7 		VA(DMC0_BASE + 0x9c)
#define QOSCONTROL8 	VA(DMC0_BASE + 0xa0)
#define QOSCONFIG8 		VA(DMC0_BASE + 0xa4)
#define QOSCONTROL9 	VA(DMC0_BASE + 0xa8)
#define QOSCONFIG9 		VA(DMC0_BASE + 0xac)
#define QOSCONTROL10 	VA(DMC0_BASE + 0xb0)
#define QOSCONFIG10 	VA(DMC0_BASE + 0xb4)
#define QOSCONTROL11 	VA(DMC0_BASE + 0xb8)
#define QOSCONFIG11 	VA(DMC0_BASE + 0xbc)
#define QOSCONTROL12 	VA(DMC0_BASE + 0xc0)
#define QOSCONFIG12 	VA(DMC0_BASE + 0xc4)

#define QOSCONTROL13 	VA(DMC0_BASE + 0xc8)
#define QOSCONFIG13 	VA(DMC0_BASE + 0xcc)
#define QOSCONTROL14 	VA(DMC0_BASE + 0xd0)
#define QOSCONFIG14 	VA(DMC0_BASE + 0xd4)
#define QOSCONTROL15 	VA(DMC0_BASE + 0xd8)
#define QOSCONFIG15 	VA(DMC0_BASE + 0xdc)

#define QOSTIMEOUT0 	VA(DMC0_BASE + 0xe0)
#define QOSTIMEOUT1 	VA(DMC0_BASE + 0xe4)
#define IVCONTROL 		VA(DMC0_BASE + 0xf0)
#define PEREVCONFIG 	VA(DMC0_BASE + 0xfc)

#define PMNC_PPC_A 			VA(DMC0_BASE + 0xe000)
#define CNTENS_PPC_A 		VA(DMC0_BASE + 0xe010)
#define CNTENC_PPC_A 		VA(DMC0_BASE + 0xe020)
#define INTENS_PPC_A 		VA(DMC0_BASE + 0xe030)
#define INTENC_PPC_A 		VA(DMC0_BASE + 0xe040)
#define FLAG_PPC_A 			VA(DMC0_BASE + 0xe050)
#define CCNT_PPC_A 			VA(DMC0_BASE + 0xe100)
#define PMCNT0_PPC_A 		VA(DMC0_BASE + 0xe110)
#define PMCNT1_PPC_A 		VA(DMC0_BASE + 0xe120)
#define PMCNT2_PPC_A 		VA(DMC0_BASE + 0xe130)
#define PMCNT3_PPC_A 		VA(DMC0_BASE + 0xe140)

#define PMNC_PPC_M 			VA(DMC0_BASE + 0xf000)
#define CNTENS_PPC_M 		VA(DMC0_BASE + 0xf010)
#define CNTENC_PPC_M 		VA(DMC0_BASE + 0xf020)
#define INTENS_PPC_M 		VA(DMC0_BASE + 0xf030)
#define INTENC_PPC_M  		VA(DMC0_BASE + 0xf040)
#define FLAG_PPC_M   		VA(DMC0_BASE + 0xf050)
#define CCNT_PPC_M  		VA(DMC0_BASE + 0xf100)
#define PMCNT0_PPC_M  		VA(DMC0_BASE + 0xf110)
#define PMCNT1_PPC_M   		VA(DMC0_BASE + 0xf120)
#define PMCNT2_PPC_M  		VA(DMC0_BASE + 0xf130)
#define PMCNT3_PPC_M   		VA(DMC0_BASE + 0xf140)


void init_ddr(void);

