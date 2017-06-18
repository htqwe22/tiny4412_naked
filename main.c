
#define GPM4CON (*(volatile unsigned int *)0x110002e0)
#define GPM4DAT (*(volatile unsigned int *)0x110002e4)
// key 
#define GPX3CON (*(volatile unsigned int *)0x11000c60)
#define GPX3DAT (*(volatile unsigned int *)0x11000c64)

void mdelay(int time);
extern show_led(int num);
extern void code_relocate(void);
extern void system_clock_init(void);

int main(void)
{
	unsigned int tmp;
	unsigned int i = 0;
	
	/*Init LED*/
    tmp = GPM4CON;  
    tmp &= ~0xffff;  
    tmp |= 0x1111;  
    GPM4CON = tmp; 

//	code_relocate();
	system_clock_init();
	for (;; mdelay(1000)) {
		show_led(++i);	
	}
	return 0;
}

void mdelay(int time)
{
	int j;
	for (; time > 0; time--) {
		for (j = 0; j < 500; j++) ;
	}
}

