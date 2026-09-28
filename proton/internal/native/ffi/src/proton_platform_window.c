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

int32_t proton_platform_window_set_icon(proton_platform_window_t *window,
                                        const char *path, char *error,
                                        size_t error_len) {
  if (window == NULL || window->backend == NULL) {
    return PROTON_ERR_UNSUPPORTED;
  }
  return proton_engine_window_set_icon(window->backend, path, error, error_len);
}

int32_t proton_platform_window_set_parent(proton_platform_window_t *window,
                                          proton_platform_window_t *parent,
                                          int32_t modal, char *error,
                                          size_t error_len) {
  if (window == NULL || window->backend == NULL) {
    return PROTON_ERR_UNSUPPORTED;
  }
  proton_engine_window_t *parent_backend =
      parent == NULL ? NULL : parent->backend;
  return proton_engine_window_set_parent(window->backend, parent_backend, modal,
                                         error, error_len);
}

int32_t proton_platform_window_set_content_size(
    proton_platform_window_t *window, int32_t width, int32_t height,
    char *error, size_t error_len) {
  if (window == NULL || window->backend == NULL) {
    return PROTON_ERR_UNSUPPORTED;
  }
  return proton_engine_window_set_content_size(window->backend, width, height,
                                               error, error_len);
}

int32_t proton_platform_window_get_content_size(
    proton_platform_window_t *window, int32_t *out_width, int32_t *out_height,
    char *error, size_t error_len) {
  if (window == NULL || window->backend == NULL) {
    return PROTON_ERR_UNSUPPORTED;
  }
  return proton_engine_window_get_content_size(window->backend, out_width,
                                               out_height, error, error_len);
}

int32_t proton_platform_window_get_titlebar_area(
    proton_platform_window_t *window, int32_t *out_x, int32_t *out_y,
    int32_t *out_width, int32_t *out_height, int32_t *out_zoom_percent,
    char *error, size_t error_len) {
  if (window == NULL || window->backend == NULL) {
    return PROTON_ERR_UNSUPPORTED;
  }
  return proton_engine_window_get_titlebar_area(
      window->backend, out_x, out_y, out_width, out_height, out_zoom_percent,
      error, error_len);
}

int32_t proton_platform_window_apply(
    proton_platform_window_t *window,
    const proton_engine_window_action_t *action, char *error,
    size_t error_len) {
  if (window == NULL || window->backend == NULL) {
    return PROTON_ERR_UNSUPPORTED;
  }
  return proton_engine_window_apply(window->backend, action, error, error_len);
}

int32_t proton_platform_window_get_state(
    proton_platform_window_t *window, proton_engine_window_state_t *out_state,
    char *error, size_t error_len) {
  if (window == NULL || window->backend == NULL) {
    return PROTON_ERR_UNSUPPORTED;
  }
  return proton_engine_window_get_state(window->backend, out_state, error,
                                        error_len);
}
