#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

static uint32_t malloc_count = 0;
static uint32_t free_count = 0;

void *(*calloc__)(size_t count, size_t size);
void (*free__)(void *ptr);
void *(*malloc__)(size_t size);
void *(*realloc__)(void *ptr, size_t size);
void *(*reallocf__)(void *ptr, size_t size);
void *(*valloc__)(size_t size);
void *(*aligned_alloc__)(size_t alignment, size_t size);

void free(void *ptr)
{
	free_count++;
	free__(ptr);
}

void *calloc(size_t count, size_t size)
{
	malloc_count++;
	return calloc__(count, size);
}
void *malloc(size_t size)
{
	malloc_count++;
	return malloc__(size);
}
void *realloc(void *ptr, size_t size)
{
	malloc_count++;
	return realloc__(ptr, size);
}
void *reallocf(void *ptr, size_t size)
{
	malloc_count++;
	return reallocf__(ptr, size);
}

void *valloc(size_t size)
{
	malloc_count++;
	return valloc__(size);
}
void *aligned_alloc(size_t alignment, size_t size)
{
	malloc_count++;
	return aligned_alloc__(alignment, size);
}

static __attribute__((constructor)) void init(void)
{
	calloc__ = dlsym(RTLD_NEXT, "calloc");
	free__ = dlsym(RTLD_NEXT, "free");
	malloc__ = dlsym(RTLD_NEXT, "malloc");
	realloc__ = dlsym(RTLD_NEXT, "realloc");
	reallocf__ = dlsym(RTLD_NEXT, "reallocf");
	valloc__ = dlsym(RTLD_NEXT, "valloc");
	aligned_alloc__ = dlsym(RTLD_NEXT, "aligned_alloc");
}

static __attribute__((destructor)) void finish(void)
{
	printf("MALLOC:%d ,FREE:%d\n", malloc_count, free_count);
}
