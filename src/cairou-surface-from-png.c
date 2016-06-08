#include "cairou.h"

#include <string.h>

typedef struct {
	unsigned int last;
	unsigned char* data;
} cairou_read_png_closure_t;

static cairo_status_t cairou_read_png(
	void* closure,
	unsigned char* data,
	unsigned int length
) {
	cairou_read_png_closure_t* c = (cairou_read_png_closure_t*)(closure);

	memcpy(data, &c->data[c->last], length);

	c->last += length;

	return CAIRO_STATUS_SUCCESS;
}

cairo_surface_t* cairou_surface_from_png_data(unsigned char* data) {
	cairo_surface_t* surface;
	cairou_read_png_closure_t closure;

	closure.last = 0;
	closure.data = data;

	surface = cairo_image_surface_create_from_png_stream(
		cairou_read_png,
		&closure
	);

	return surface;
}

