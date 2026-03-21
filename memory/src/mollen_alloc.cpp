#include "../include/mollen_alloc.h"
#include "../../utils/hooks/hook.hpp"
#include <cstdint>
#include <cstdlib>

static uint32_t mollenAllocCount = 0;
static bool		mollenHeapActive = false;

void* MollenWowAlloc(size_t size, const char* tag, const char* file, int line, uint32_t flags) {
	if (size == 0) {
		return nullptr;
	}
	if (mollenAllocHook != nullptr && !(flags & 0x10000000)) {
		void* result = mollenAllocHook(size, file, line, (flags >> 3) & 0xFFFFFF01);
		if (result != nullptr) {
			// Wohoo, hook handled it for us
			return result;
		}
	}

	size_t aligned = (size + 15) & ~15;
	const char* testTag = "lol";
	void* result = MollenPoolAlloc(testTag, file, line, aligned, flags);
	if (result != nullptr) {
		return result;
	}

	result = MollenHeapAlloc(file, line, aligned, flags);
	if (result == nullptr) {
		MollenWowOutOfMemory(file, line, aligned);
		return result;
	}

	mollenAllocCount++;
	mollenHeapActive = true;
	return result;
}

void MollenFreeInternal(const char* file, int line, void* ptr, int flags) {
	free(ptr); 
}

void* MollenPoolAlloc(const char* tag, const char* file, int line, size_t size, int flags) {
	return nullptr;
}

void* MollenHeapAlloc(const char* file, int line, size_t size, int flags) {
	return malloc(size);
}

void* MollenWowOutOfMemory(const char* file, int line, size_t size) {
	return nullptr;
}
