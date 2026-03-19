#include "../include/mollen_alloc.h"
#include "../../utils/hooks/hook.hpp"
#include <cstddef>

void* mollenWowAlloc(size_t size, const char* tag, const char* file, int line, uint32_t flags) {
	void* (*allocHook)(size_t size, const char *file, int line, uint32_t flags) = gAllocHook;
	if (size == 0) {
		return nullptr;
	}
	if (gAllocHook != nullptr && !(flags & 0x10000000)) {
		void* result = gAllocHook(size, file, line, (flags >> 3) & 0xFFFFFFF01);
			if (result != nullptr) {
				// Wohoo, hook handled it for us
				return result;
			}
	}

		size_t aligned = (size + 15) & ~15;
	return 0;
}
