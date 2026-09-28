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

int32_t proton_platform_window_show(proton_platform_window_t *window,
                                    char *error, size_t error_len) {
  return window == NULL || window->backend == NULL
             ? PROTON_OK
             : proton_engine_window_show(window->backend, error, error_len);
}

int32_t proton_platform_window_show_inactive(proton_platform_window_t *window,
                                             char *error, size_t error_len) {
  return window == NULL || window->backend == NULL
             ? PROTON_OK
             : proton_engine_window_show_inactive(window->backend, error,
                                                   error_len);
}

int32_t proton_platform_window_hide(proton_platform_window_t *window,
                                    char *error, size_t error_len) {
  return window == NULL || window->backend == NULL
             ? PROTON_OK
             : proton_engine_window_hide(window->backend, error, error_len);
}

int32_t proton_platform_window_focus(proton_platform_window_t *window,
                                     char *error, size_t error_len) {
  return window == NULL || window->backend == NULL
             ? PROTON_OK
             : proton_engine_window_focus(window->backend, error, error_len);
}

int32_t proton_platform_window_set_title(proton_platform_window_t *window,
                                         const char *title, char *error,
                                         size_t error_len) {
  return window == NULL || window->backend == NULL
             ? PROTON_OK
             : proton_engine_window_set_title(window->backend, title, error,
                                              error_len);
}

int32_t proton_platform_window_set_size(proton_platform_window_t *window,
                                        int32_t width, int32_t height,
                                        char *error, size_t error_len) {
  return window == NULL || window->backend == NULL
             ? PROTON_OK
             : proton_engine_window_set_size(window->backend, width, height,
                                             error, error_len);
}
