#ifndef EXCEPTION_H_RAWU1HQL
#define EXCEPTION_H_RAWU1HQL

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __JMP_STACK_MAX_DEPTH
#define __JMP_STACK_MAX_DEPTH 8
#endif

static __thread struct {
	jmp_buf buf[__JMP_STACK_MAX_DEPTH];
	int depth;
} __local_jmp_stack = {
	.depth = 0
};

#define _TRY 									\
	do { 										\
		__local_jmp_stack.depth++; 						\
		if(__local_jmp_stack.depth > __JMP_STACK_MAX_DEPTH) { 			\
			fprintf(stderr, "CURRENT TRY-CATCH DEPTH EXCEEDS MAXIMUM" 	\
					" ALLOWED DEPTH (%d)\n", __JMP_STACK_MAX_DEPTH);\
			abort(); 						\
		} 									\
		int __jmp_status = setjmp(__local_jmp_stack.buf[__local_jmp_stack.depth - 1]); 	\
		if(__jmp_status == 0)
#define _CATCH else
#define _TRYEND __local_jmp_stack.depth--; } while(0)

#define _TRY_STATUS_CODE __jmp_status

#define _THROW(_STATUS_CODE) do { 						\
	if(__local_jmp_stack.depth == 0) { 					\
		fprintf(stderr, "UNHANDLED EXCEPTION\n"); 			\
		abort(); 							\
	} else { 								\
		longjmp(__local_jmp_stack.buf[__local_jmp_stack.depth - 1], 	\
				_STATUS_CODE); 					\
	} 									\
} while(0)

#endif /* end of include guard: EXCEPTION_H_RAWU1HQL */
