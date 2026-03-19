#include "hook.hpp"
#include <sec_api/stdio_s.h>

void* gAllocHook(size_t size, const char *file, int line, uint32_t flags) {
	printf_s("gg");
	int* x = new int(42);
	return x;
}
