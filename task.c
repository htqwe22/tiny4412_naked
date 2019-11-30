
/**********************************************************************************
 * FILE : task.c
 * Description:
 * Author: Kevin He
 * Created On: 2019-04-15 , At 00:59:40
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/
#include "util.h"
#include "task.h"
#include "heap.h"
#include "util_string.h"
struct kv_task
{
	volatile unsigned long top_stack; //Used by System
	char task_name[16];
//	tid_t tid;
	volatile int state; /* 0 suspend,-1 stopped,1 runing */
	// struct list_head node;
//	singal_t singal; /*** signal ***/
	task_fun_t thread_func;
	void *arg;
	unsigned short stack_size; /*real size is sizeof(uint32_t)*stack_size in bytes*/
	unsigned char stack_malloc;	
	unsigned char;  /*priority leve*/
	unsigned int *stack;
};

struct kv_task *current = NULL;


struct kv_task *get_next_run_task(void)
{
	debug("next: %p %p\n", current, &current);
	return current;
}

void debug_lable(uint32_t addr)
{
	debug("debug_lable: %X\n", addr);
}

static void *idle_task(void *arg)
{
	debug("idle_task");
	schedule();
}

//uint32_t stack_1[200];

void init_task(void)
{
	current = (struct kv_task *) kv_create_task("idle", idle_task, NULL, NULL, 200);
	debug("%s %p\n", __FUNCTION__, idle_task);
	schedule();	
}

void start_task(void)
{
	current = (struct kv_task *) kv_create_task("idle", idle_task, NULL, NULL, 200);
	debug("%s %p\n", __FUNCTION__, idle_task);
	schedule();	
}



// return task_id, if return 0, fail
task_id_t kv_create_task(const char *task_name, task_fun_t task_func, void *arg, void *stack_mem, uint32_t stack_size)
{
	struct kv_task *task;	
	if (stack_mem == NULL)
		task = kv_malloc(sizeof(struct kv_task) + (stack_size << 2));
	else
		task = kv_malloc(sizeof(struct kv_task));	
	if (task == NULL)
		return 0;
	kv_memset(task, 0, sizeof(struct kv_task));
	
	kv_strcpy(task->task_name, task_name);

	if (stack_mem == NULL) {
		task->stack_malloc = 1;
		task->stack = (unsigned int *)(task + 1);
	}else{
		task->stack = stack_mem;
	}
	task->stack_size = stack_size>>2;
	kv_memset(task->stack,0xAE,task->stack_size<<2);
	
	task->thread_func = task_func;
	task->arg = arg;
	
	// FULL decrease stack reserve to save stack top;
	uint32_t *p_stack = task->stack+task->stack_size;
	p_stack = (uint32_t *)(((uint32_t)p_stack) &(~0x7));
	debug("%s\n", __FUNCTION__);
	
	/*8 is : spsr, r0, ... r12, r14*/
	p_stack -= 15;
	kv_memset(p_stack, 0, 16*4);
	// r0
	p_stack[0]= 0x10; // user mode
	p_stack[1]=(uint32_t)arg; //r0 = args
	p_stack[14]=(uint32_t)task_func; //LR

	task->top_stack=(uint32_t)p_stack;
	return (task_id_t)task;

}

void kv_destroy_task(task_id_t task_id)
{

}

