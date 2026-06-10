#include "../includes_bonus/cub_bonus.h"

typedef struct s_fps_meter
{
	double		frame_times[120];
	int			frame_count;
	double		total_time;
	double		min_frame_time;
	double		max_frame_time;
	double		avg_frame_time;
}	t_fps_meter;

static t_fps_meter g_fps = {0};
static int g_fps_enabled = 0;

void fps_meter_enable(void)
{
	g_fps_enabled = 1;
	ft_bzero(&g_fps, sizeof(t_fps_meter));
	g_fps.min_frame_time = 1000.0;
	g_fps.max_frame_time = 0.0;
}

void fps_meter_record(double frame_time_ms)
{
	if (!g_fps_enabled)
		return ;
	
	if (g_fps.frame_count < 120)
	{
		g_fps.frame_times[g_fps.frame_count] = frame_time_ms;
		g_fps.total_time += frame_time_ms;
		
		if (frame_time_ms < g_fps.min_frame_time)
			g_fps.min_frame_time = frame_time_ms;
		if (frame_time_ms > g_fps.max_frame_time)
			g_fps.max_frame_time = frame_time_ms;
		
		g_fps.frame_count++;
	}
}

void fps_meter_print(void)
{
	if (!g_fps_enabled || g_fps.frame_count == 0)
		return ;
	
	g_fps.avg_frame_time = g_fps.total_time / g_fps.frame_count;
	
	ft_fprintf_fd(2, "\n");
	ft_fprintf_fd(2, "===== FPS STATISTICS (Last %d frames) =====\n", g_fps.frame_count);
	ft_fprintf_fd(2, "Average FPS: %.1f\n", 1000.0 / g_fps.avg_frame_time);
	ft_fprintf_fd(2, "Min FPS: %.1f (%.2f ms)\n", 1000.0 / g_fps.max_frame_time, g_fps.max_frame_time);
	ft_fprintf_fd(2, "Max FPS: %.1f (%.2f ms)\n", 1000.0 / g_fps.min_frame_time, g_fps.min_frame_time);
	ft_fprintf_fd(2, "Total time: %.2f seconds\n", g_fps.total_time / 1000.0);
	ft_fprintf_fd(2, "==========================================\n\n");
}
