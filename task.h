
/**********************************************************************************
 * FILE : task.h
 * Description:
 * Author: Kevin He
 * Created On: 2019-04-15 , At 00:59:40
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#ifndef KV_TASK_H
#define KV_TASK_H

#ifdef __cplusplus
extern "C" {
#endif
#include <util.h>
typedef void *(*task_fun_t)(void *);
typedef void * task_id_t;
extern void schedule(void);
void init_task(void);

void start_task(void);


// return task_id, if return 0, fail
task_id_t kv_create_task(const char *task_name, task_fun_t task_func, void *arg, void *stack_mem, uint32_t stack_size);


void kv_destroy_task(task_id_t task_id);






#ifdef __cplusplus
}
#endif

#endif
