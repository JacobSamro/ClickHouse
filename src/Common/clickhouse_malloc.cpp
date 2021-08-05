#include <Common/memory.h>
#include <cstdlib>


extern "C" void * clickhouse_malloc(size_t size)
{
    void * res = malloc(size);
    if (res)
        Memory::trackMemory(size);
    return res;
}

extern "C" void * clickhouse_calloc(size_t number_of_members, size_t size)
{
    void * res = calloc(number_of_members, size);
    if (res)
        Memory::trackMemory(number_of_members * size);
    return res;
}

extern "C" void * clickhouse_realloc(void * ptr, size_t size)
{
    void * res = realloc(ptr, size);
    if (res)
    {
        if (ptr)
            Memory::untrackMemory(ptr);
        Memory::trackMemory(size);
    }
    return res;
}

extern "C" void * clickhouse_reallocarray(void * ptr, size_t number_of_members, size_t size)
{
    void * res = reallocarray(ptr, number_of_members, size);
    if (res)
    {
        if (ptr)
            Memory::untrackMemory(ptr);
        Memory::trackMemory(number_of_members * size);
    }
    return res;
}

extern "C" void clickhouse_free(void * ptr)
{
    Memory::untrackMemory(ptr);
    free(ptr);
}

extern "C" int clickhouse_posix_memalign(void ** memptr, size_t alignment, size_t size)
{
    int res = posix_memalign(memptr, alignment, size);
    if (res == 0)
        Memory::trackMemory(size);
    return res;
}
