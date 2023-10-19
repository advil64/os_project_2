// File:	thread-worker.c

// List all group member's name:
// username of iLab: ac1771, tsc95
// iLab Server: cs416f23-40

#include "thread-worker.h"

//Global counter for total context switches and 
//average turn around and response time
long tot_cntx_switches=0;
double avg_turn_time=0;
double avg_resp_time=0;
uint first_run = 1;


// INITAILIZE ALL YOUR OTHER VARIABLES HERE

// Here the scheduler context is set, it gets swapped to
// when a thread is interrupted/finished running
ucontext_t sched_cctx;
void * sched_stack;

// This variable contains a pointer to the currently running TCB
// as set by the scheduler
struct TCB * running_thread;


/* scheduler */
static void schedule() {
	puts("Scheduler started");
	// - every time a timer interrupt occurs, your worker thread library 
	// should be contexted switched from a thread context to this 
	// schedule() function

	// - invoke scheduling algorithms according to the policy (PSJF or MLFQ)

	// if (sched == PSJF)
	//		sched_psjf();
	// else if (sched == MLFQ)
	// 		sched_mlfq();

	// YOUR CODE HERE

// - schedule policy
// #ifndef MLFQ
// 	// Choose PSJF
// #else 
// 	// Choose MLFQ
// #endif

}

/* Pre-emptive Shortest Job First (POLICY_PSJF) scheduling algorithm */
static void sched_psjf() {
	// - your own implementation of PSJF
	// (feel free to modify arguments and return types)

	// YOUR CODE HERE
}


/* Preemptive MLFQ scheduling algorithm */
static void sched_mlfq() {
	// - your own implementation of MLFQ
	// (feel free to modify arguments and return types)

	// YOUR CODE HERE
}


/* create a new thread */
int worker_create(worker_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg) {

	// - create Thread Control Block (TCB)
	struct TCB * myTCB = (struct TCB *) malloc(sizeof(struct TCB));

	// - allocate space of stack for this thread to run
	myTCB->stack = malloc(STACK_SIZE);
	
	// - create and initialize the context of this worker thread
	myTCB->cctx.uc_link=NULL;
	myTCB->cctx.uc_stack.ss_sp=myTCB->stack;
	myTCB->cctx.uc_stack.ss_size=STACK_SIZE;
	myTCB->cctx.uc_stack.ss_flags=0;
	makecontext(&myTCB->cctx,(void *)&function,0);

	// after everything is set, push this thread into run queue and 
	if (first_run) {
		// Set up the scheduler context
		sched_stack=malloc(STACK_SIZE);
		sched_cctx.uc_link=NULL;
		sched_cctx.uc_stack.ss_sp=sched_stack;
		sched_cctx.uc_stack.ss_size=STACK_SIZE;
		sched_cctx.uc_stack.ss_flags=0;

		makecontext(&sched_cctx,(void *)&schedule,0);
		setcontext(&sched_cctx);
		
		// LOGIC TO SETUP THE SCHEDULER QUEUE HERE
		first_run = 0;
	}

	// - make it ready for the execution.
	myTCB->thread_status = 0;
	
    return 0;
};

/* give CPU possession to other user-level worker threads voluntarily */
int worker_yield() {
	
	// - change worker thread's state from Running to Ready
	running_thread->thread_status = 0;
	// - save context of this thread to its thread control block
	// - switch from thread context to scheduler context

	// YOUR CODE HERE
	
	return 0;
};

/* terminate a thread */
void worker_exit(void *value_ptr) {
	// - de-allocate any dynamic memory created when starting this thread

	// YOUR CODE HERE
};


/* Wait for thread termination */
int worker_join(worker_t thread, void **value_ptr) {
	
	// - wait for a specific thread to terminate
	// - de-allocate any dynamic memory created by the joining thread
  
	// YOUR CODE HERE
	return 0;
};

/* initialize the mutex lock */
int worker_mutex_init(worker_mutex_t *mutex, 
                          const pthread_mutexattr_t *mutexattr) {
	//- initialize data structures for this mutex

	// YOUR CODE HERE
	return 0;
};

/* aquire the mutex lock */
int worker_mutex_lock(worker_mutex_t *mutex) {

        // - use the built-in test-and-set atomic function to test the mutex
        // - if the mutex is acquired successfully, enter the critical section
        // - if acquiring mutex fails, push current thread into block list and
        // context switch to the scheduler thread

        // YOUR CODE HERE
        return 0;
};

/* release the mutex lock */
int worker_mutex_unlock(worker_mutex_t *mutex) {
	// - release mutex and make it available again. 
	// - put threads in block list to run queue 
	// so that they could compete for mutex later.

	// YOUR CODE HERE
	return 0;
};


/* destroy the mutex */
int worker_mutex_destroy(worker_mutex_t *mutex) {
	// - de-allocate dynamic memory created in worker_mutex_init

	return 0;
};

//DO NOT MODIFY THIS FUNCTION
/* Function to print global statistics. Do not modify this function.*/
void print_app_stats(void) {

       fprintf(stderr, "Total context switches %ld \n", tot_cntx_switches);
       fprintf(stderr, "Average turnaround time %lf \n", avg_turn_time);
       fprintf(stderr, "Average response time  %lf \n", avg_resp_time);
}


// Feel free to add any other functions you need

// YOUR CODE HERE
