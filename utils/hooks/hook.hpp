#include <cstdint>

using mollenAllocHookFunc = void*(*)(size_t size, const char* file, int line, uint32_t flags);
extern mollenAllocHookFunc mollenAllocHook;
