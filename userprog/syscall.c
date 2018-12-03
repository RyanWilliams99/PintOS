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
    uint32_t *p=f->esp; //Get the syscall number, which is defined in ‘Pintos/lib/syscall-nr.h’)


    //SYS_HALT, /* Halt the operating system. */            DONE
    //SYS_EXIT, /* Terminate this process. */               DONE
    //SYS_EXEC, /* Start another process. */
    //SYS_WAIT, /* Wait for a child process to die. */
    //SYS_CREATE, /* Create a file. */
    //SYS_REMOVE, /* Delete a file. */
    //SYS_OPEN, /* Open a file. */
    //SYS_FILESIZE, /* Obtain a file’s size. */
    //SYS_READ, /* Read from a file. */
    //SYS_WRITE, /* Write to a file. */                     DONE
    //SYS_SEEK, /* Change position in a file. */
    //SYS_TELL, /* Report current position in a file. */
    //SYS_CLOSE, /* Close a file. */


    switch(*p)
    {
        case SYS_HALT: { //Tested and works as expected
            printf("In Syscall number %d, SYS_HALT\n",*p);
            shutdown();
            break;
        }
        case SYS_EXIT: { //Tested and works as expected
            printf("In Syscall number %d, SYS_EXIT\n",*p);
            struct thread *current = thread_current();
            //current->process_info->exit_status = status; // or exit_code.
            thread_exit();
            break;
        }
        case SYS_EXEC: {
            printf("In Syscall number %d, SYS_EXEC\n",*p);
            break;
        }
        case SYS_WAIT: {
            printf("In Syscall number %d, SYS_WAIT\n",*p);
            break;
        }
        case SYS_CREATE: {
            printf("In Syscall number %d, SYS_CREATE\n",*p);
            //bool create(const char* file, unsigned initial_size)
            break;
        }
        case SYS_REMOVE: {
            printf("In Syscall number %d, SYS_REMOVE\n",*p);
            break;
        }
        case SYS_OPEN: {
            printf("In Syscall number %d, SYS_OPEN\n",*p);
            break;
        }
        case SYS_FILESIZE: {
            printf("In Syscall number %d, SYS_FILESIZE\n",*p);
            break;
        }
        case SYS_READ: {
            printf("In Syscall number %d, SYS_READ\n",*p);
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
        case SYS_SEEK: {
            printf("In Syscall number %d, SYS_SEEK\n",*p);
            break;
        }
        case SYS_TELL: {
            printf("In Syscall number %d, SYS_TELL\n",*p);
            break;
        }
        case SYS_CLOSE: {
            printf("In Syscall number %d, SYS_CLOSE\n",*p);
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
