#include "proton_platform_window.h"

#include <stdlib.h>

proton_platform_window_t *proton_platform_window_alloc(void) {
  return (proton_platform_window_t *)calloc(1, sizeof(proton_platform_window_t));
}

void proton_platform_window_free(proton_platform_window_t *window) {
  free(window);
}

void proton_platform_window_attach_backend(proton_platform_window_t *window,
                                           proton_engine_window_t *backend) {
  if (window != NULL) {
    window->backend = backend;
  }
}

proton_engine_window_t *proton_platform_window_backend(
    proton_platform_window_t *window) {
  return window == NULL ? NULL : window->backend;
}
