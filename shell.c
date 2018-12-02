
/**********************************************************************************
 * FILE : shell.c
 * Description:
 * Author: Kevin He
 * Created On: 2018-12-02 , At 14:45:14
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#include "shell.h"
#include "util.h"
#include "console.h"

/*******************************************************************/

#define module_strcmp	kv_strcmp
#define module_memset	kv_memset
#define module_strlen	kv_strlen
#define module_strcat	kv_strcat
#define console_printf  kv_printf

#define LOGI kv_printf

static void send_cr(int argc, char **argv);

cmd_list_t cmdlist_arr[] = 
{
	{"clear", send_cr},
};



#define LIST_START() cmdlist_arr
#define LIST_NUM()	ARRAY_SIZE(cmdlist_arr)

/*********************************************************************************/

#if 0
#define MAX_PRINT_CACHE_SIZE 200
/* 
 * this is used to print in any place.
 */
int force_printf(const char *fmt, ...)
{
	va_list ap;
	int i;
	char str[MAX_PRINT_CACHE_SIZE];
	va_start(ap, fmt);
	i = vsnprintf(str, MAX_PRINT_CACHE_SIZE, fmt, ap);
	va_end(ap);
	return drv_uart_send(OFO_UART_DEBUG, (const unsigned char * )str, i);
}
#endif

static char stdout_off = 0;

//xmodem, ′??ú??á?1?ó?buffer
char xbuff[1128] = {0}; /* 1024 for XModem 1k + 3 head chars + 2 crc + nul */

void stdout_open(void)
{
	stdout_off = 0;
}


static void stdout_close(void)
{
	stdout_off = 1;
}




/******************************** For shell ***********************************************/
#define next_line() console_printf("\r\n") 

static void print_help(int argc, char **argv)
{
#if 0
	int i;
	if (argc != 1)
		return;
	console_printf("Usage Cmd --help\r\n");
	const cmd_list_t *plist = LIST_START();
	for(i = 0; i < LIST_NUM(); i++, plist++){
		console_printf("%s -- help\r\n",plist->cmd);
	}
#endif	
}

static void send_cr(int argc, char **argv)
{
	if (argc == 1)
		console_printf("\033[2J\033[1H");
}

/********************************** Task ************************************************/
static void exec_cmd(char *const cmd)
{
	const cmd_list_t *list;
	int index;
	char *argv[10];
	int i =0,j=0,flag=0;
//	next_line();
	if(*cmd < ' ' || *cmd > '~') return;
	
	argv[j++] = cmd;
	for(i=0;cmd[i];i++,flag = 0){
		if(cmd[i] == ' ' || cmd[i] == '\t'){
			cmd[i++]=0;
			flag = 1;
		}	
		if(flag && cmd[i] && cmd[i] != ' ' && cmd[i] != '\t') {
			if(j + 1 <ARRAY_SIZE(argv)){ 
				argv[j++]=cmd+i;
			}else{
				break;
			}
		}	
	}
	argv[j] = NULL;
	for(list = LIST_START(), index = 0; index < LIST_NUM(); index++, list++)
	{
		if(list->func && 0 == module_strcmp(argv[0],list->cmd)){
			list->func(j, (char **)argv);
			break;
		}
	}
	if(index == LIST_NUM()){
		console_printf(" \"%s\" not support now",argv[0]);
	}
	next_line();
}

//#define TEST_UART 
int do_shell_loop(void)
{
	static unsigned short i=0;
	int ch;
	/*get one byte ,it may block */
	ch = fgetc(stdin);
	if (ch < 0)  {
		return -1 ;
	}
#ifdef TEST_UART
	fputc(ch, stdout);
#else	
	if(ch == '\r' || ch == '\n'){
//		if(i !=0)
			xbuff[i]=0;
		console_printf("\n");
		exec_cmd(xbuff);
		console_printf("# ");
		i=0;
	}else{
		if (ch == '\b') {
			if(i > 0){
				xbuff[--i] = 0;
				console_printf("\b \b");
			} 			
		} else if (i + 1 < sizeof(xbuff)){
			xbuff[i++]=ch;
			console_printf("%c", ch);
		}	
	}
#endif	
	return 0;
}

#if 0
static void check_user_cmd(void)
{
	const char *cmd1, *cmd2;
	cmd_list_t *list = LIST_START();
	int i,j, num, list_num = LIST_NUM();
	for (i = 0; i < list_num; i++)
	{
		cmd1 = list[i].cmd;
		num = 0;
		for (j = i + 1; j < list_num; j++)
		{
			cmd2 = list[j].cmd;
			if (0 == module_strcmp(cmd1, cmd2))
			{
				num++;
			}
		}
		if (num)
		{
			printf("######## user has registered %d same command: \"%s\" ############\n", num +1, cmd1);
		}
	}
}
#endif

void _outbyte(int c)
{
	fputc((char)c, stdout);
}

int _inbyte(unsigned short timeout) // msec timeout
{
    unsigned char ch;
		
//	if (drv_uart_wait_rx(OFO_UART_DEBUG, timeout) >= 0 && drv_uart_recv(OFO_UART_DEBUG, &ch, 1) == 1) {
//			return ch;
//	}
	return -2;
}

static void xmodem_recv(int argc, char **argv)
{
	char fullName[13] = "0:/";

	if ((argc < 2) || NULL == argv[1])
	{
		return;
	}
	
	if (0 != module_strcmp(argv[0], "xmodem"))
	{
		return;
	}

	if (module_strlen(argv[1]) > 12)
	{
		console_printf("file name too long:%d\r\n", module_strlen(argv[1]));
		return;
	}

	module_strcat(fullName, argv[1]);
	console_printf("xmodem -> [%s]\r\n", fullName);

	stdout_close();
//	xmodemReceive(fullName);

	//xmodem ?áê???1?ó??o′?????￡?±ü?a2Dá?êy?Yó°?ì?üá?DD′|àí
	module_memset(xbuff, 0, sizeof(xbuff));
	
	stdout_open();
	
}

unsigned char cmd_return_log_lv = 1;
static void cmd_return_control(int argc, char **argv)
{
	if (0 == module_strcmp(argv[1], "off"))
		cmd_return_log_lv = 0;
	else if (0 == module_strcmp(argv[1], "on"))
		cmd_return_log_lv = 1;
}


void debug_data(const char *name, const uint8_t *data, int len)
{
	int i;
	LOGI("[%s] (%d)", name, len);
	for (i = 0; i < len; i++)
	{
		if ((i&0x1f) == 0)
			LOGI("\n");
		LOGI("%02X ", data[i]);
	}
	LOGI("\n");
}




