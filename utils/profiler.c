#include "../includes/thedump.h"
#include <stdio.h>

static struct timeval g_prof_start;
static int g_prof_enabled = 1;

void prof_enable(int enable)
{
	g_prof_enabled = enable;
}

void prof_start(void)
{
	if (g_prof_enabled)
		gettimeofday(&g_prof_start, NULL);
}

long prof_end(const char *name)
{
	struct timeval	tv;
	long			elapsed_ms;
    (void)name;

	if (!g_prof_enabled)
		return (0);
	gettimeofday(&tv, NULL);
	elapsed_ms = (tv.tv_sec - g_prof_start.tv_sec) * 1000 +
		(tv.tv_usec - g_prof_start.tv_usec) / 1000;
	// ft_fprintf_fd(2, "[PROF] %s: %ld ms\n", name, elapsed_ms);
	return (elapsed_ms);
}

void prof_start_named(struct timeval *t)
{
	if (g_prof_enabled)
		gettimeofday(t, NULL);
}

long prof_end_named(const char *name, struct timeval *t)
{
	struct timeval	tv;
	long			elapsed_ms;

    (void)name;
	if (!g_prof_enabled)
		return (0);
	gettimeofday(&tv, NULL);
	elapsed_ms = (tv.tv_sec - t->tv_sec) * 1000 +
		(tv.tv_usec - t->tv_usec) / 1000;
	// ft_fprintf_fd(2, "[PROF] %s: %ld ms\n", name, elapsed_ms);
	return (elapsed_ms);
}
