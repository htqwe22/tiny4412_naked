
/**********************************************************************************
 * FILE : kv_usb.c
 * Description:
 * Author: Kevin He
 * Created On: 2019-07-20 , At 13:07:51
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#include "kv_usb.h"
#include "util.h"

#if 0
0x12580000	//ehci
0x12590000	//ohci
#endif
// GPM2(4) reset DM9621 PULL 0 lasts 1ms and pull up
#define CLK_GATE_IP_FSYS 	0x1003C940
#define USB_PHY_CONTROL		0x10020704
#define ETC6PUD				0x11000228
void usb_host_clock_ctl(int enable)
{
	unsigned int tmp =  VA(CLK_GATE_IP_FSYS);
	debug("B CLK_GATE_IP_FSYS %X\n", tmp);
	if (enable) {
		tmp |= 3<<12;
	} else {
		tmp &= ~(3<<12);
	}
	VA(CLK_GATE_IP_FSYS) = tmp;
	debug("A CLK_GATE_IP_FSYS %X\n", tmp);
}

void usb_host_power_ctl(int enable)
{
	unsigned int tmp =  VA(USB_PHY_CONTROL);
	debug("B CLK_GATE_IP_FSYS %X\n", tmp);
	if (enable) {
		tmp |= 1;
	} else {
		tmp &= ~(1);
	}
	VA(USB_PHY_CONTROL) = tmp;


	tmp =  VA(USB_PHY_CONTROL+4);
	if (enable) {
		tmp |= 1;
	} else {
		tmp &= ~(1);
	}
	VA(USB_PHY_CONTROL+4) = tmp;


	tmp =  VA(USB_PHY_CONTROL+8);
	if (enable) {
		tmp |= 1;
	} else {
		tmp &= ~(1);
	}
	VA(USB_PHY_CONTROL+8) = tmp;

	debug("A CLK_GATE_IP_FSYS %X\n", tmp);
}

int usb_init(void)
{
	
	unsigned int tmp;
	usb_host_clock_ctl(1);
	usb_host_power_ctl(1);

	//set XuhostOVERCUR to in-active by controlling ET6PUD[15:14]
	tmp =  VA(ETC6PUD);
	tmp |= 3<<14;
	VA(ETC6PUD) = tmp;


	
}

