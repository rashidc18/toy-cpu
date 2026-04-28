#ifndef _ERROR_H
#define _ERROR_H

#define FILE_NOT_FOUND_ERROR "file `%s` not found"

#define MEMORY_OVERFLOW_ERROR "memory overflow"
#define MEMORY_UNDERFLOW_ERROR "memory underflow"

#define STACK_OVERFLOW_ERROR "stack overflow"
#define STACK_UNDERFLOW_ERROR "stack underflow"

#define UNKNOWN_INSTRUCTION_ERROR "unknown instruction `%d`"

void error(const char* error_message, ...);

#endif
