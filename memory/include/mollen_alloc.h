#ifndef MOLLEN_ALLOC_H
#define MOLLEN_ALLOC_H
#include <cstddef>
#include <cstdint>
#include <cstdlib>


void* MollenWowAlloc(size_t size, const char* tag, const char* file, int line, uint32_t flags);
void MollenFreeInternal(const char* file, int line, void* ptr, int flags); 
void* MollenPoolAlloc(const char* tag, const char* file, int line, size_t size, int flags);
void* MollenHeapAlloc(const char* file, int line, size_t size, int flags);
void* MollenWowOutOfMemory(const char* file, int line, size_t size);

#endif

