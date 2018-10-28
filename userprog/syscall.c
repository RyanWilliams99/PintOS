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
  char *temp2;
  char *thread_name_split = strtok_r(thread_name(), " ", &temp2);
  printf("system call!\n");
  printf("%s: exit(%d) ", thread_name_split, exit_code());
  thread_exit ();
}
