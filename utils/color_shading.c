#include "../includes/thedump.h"

unsigned int	apply_depth_shading(unsigned int color, double dist)
{
	double	intensity;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (color == TRANSPARENT_BACKGROUND)
		return (color);
	intensity = 1.0 / (1.0 + dist * 0.3); // Factor 0.15 controls the darkness
	if (intensity > 1.0)
		intensity = 1.0;
	a = (color >> 24) & 0xFF;
	r = (uint8_t)(((color >> 16) & 0xFF) * intensity);
	g = (uint8_t)(((color >> 8) & 0xFF) * intensity);
	b = (uint8_t)((color & 0xFF) * intensity);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}
