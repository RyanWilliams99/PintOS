#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}


static void
syscall_handler (struct intr_frame *f UNUSED)
{
    uint32_t *p=f->esp; // get the syscall number, which is defined in ‘Pintos/lib/syscall-nr.h’)

    //Then implement syscalls
    switch(*p)
    {
        case SYS_HALT: {
            shutdown();
            break;
        }
        case SYS_EXIT: {
            struct thread *current = thread_current();
            //current->process_info->exit_status = status; // or exit_code.
            thread_exit();
            break;
        }
        case SYS_WRITE: {
            /*Add by lsc Working*/
            printf("<2> In SYS_WRITE: %d\n", *p);
            int fd =*(int *)(f->esp + 4);
            void *buffer = *(char**) (f->esp + 8);
            unsigned size = *(unsigned *)(f->esp + 12);
            if(fd==STDOUT_FILENO) {
                putbuf((const char*)buffer, (unsigned ) size);
            }
            else {
                printf("sys_write does not support fd output\n");
            }
            break;
        }
        default: {
            printf("SYS_CALL (%d) not implemented\n", *p);
            thread_exit();
        }
    }
}

void halt(void)
{
    shutdown_power_off();
}


//char *temp2;
//char *thread_name_split = strtok_r(thread_name(), " ", &temp2);
//printf("system call!\n");
//printf("%s: exit(%d) ", thread_name_split, exit_code());
//thread_exit ();