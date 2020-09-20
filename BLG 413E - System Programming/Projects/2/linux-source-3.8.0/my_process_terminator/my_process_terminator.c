#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/capability.h>

asmlinkage long sys_my_process_terminator(pid_t pid, int flag){
	if(! capable(CAP_SYS_ADMIN)){
		return EPERM;
	}
	long errorFlag = 0;
	
	if(flag == 0){	  
		struct task_struct *p;
		struct task_struct *child_task;
		struct list_head *children_list;  
		for_each_process(p){ 
			if(p->pid == pid){	
				list_for_each(children_list, &(p->children)){ 				 
					child_task = list_entry(children_list, struct task_struct, sibling);
					printk("Child %d killed\n",child_task->pid);					
					sys_kill(child_task->pid,SIGKILL);
				} 
			}
		}
	}
	else if(flag == 1){
		struct task_struct *p;
		struct task_struct *s;
		struct task_struct *child_task;
		struct task_struct *sibling_task;
		struct task_struct *sibling_child_task;
		struct list_head *children_list; 
		struct list_head *sibling_list; 
		struct list_head *sibling_children_list; 
		for_each_process(p){ 
			if(p->pid == pid){	
				list_for_each(children_list, &(p->children)){ 				 
					child_task = list_entry(children_list, struct task_struct, sibling);
					printk("Child %d killed\n",child_task->pid);
					sys_kill(child_task->pid,SIGKILL);
				}	   
				list_for_each(sibling_list, &(p->sibling)){
					sibling_task = list_entry(sibling_list, struct task_struct, sibling);
					if (sibling_task->pid != 0){
						for_each_process(s){
							if(s->pid == sibling_task->pid){
								list_for_each(children_list, &(s->children)){ 				 
									child_task = list_entry(children_list, struct task_struct, sibling);
									printk("Siblings child %d killed\n",child_task->pid);
									sys_kill(child_task->pid,SIGKILL);
								}
							}
						}
						printk("Sibling %d killed\n",sibling_task->pid);
						sys_kill(sibling_task->pid,SIGKILL);
					}	
				}
			}
		}	
	}
	return errorFlag;
}
