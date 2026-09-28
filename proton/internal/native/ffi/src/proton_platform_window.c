#include "proton_platform_window.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

proton_platform_window_t *proton_platform_window_alloc(void) {
  return (proton_platform_window_t *)calloc(1, sizeof(proton_platform_window_t));
}

int32_t proton_platform_window_configure(
    proton_platform_window_t *window, const char *title, int32_t width,
    int32_t height, int32_t size_hint, int32_t titlebar_overlay,
    int32_t theme_preference, int32_t button_position_custom,
    int32_t button_position_x, int32_t button_position_y,
    const char *titlebar_minimize_label, const char *titlebar_maximize_label,
    const char *titlebar_restore_label, const char *titlebar_close_label) {
  if (window == NULL || width <= 0 || height <= 0 || title == NULL) {
    return PROTON_ERR_INVALID_ARGUMENT;
  }
  snprintf(window->title, sizeof(window->title), "%s", title);
  window->width = width;
  window->height = height;
  window->size_hint = size_hint;
  window->titlebar_overlay = titlebar_overlay;
  window->theme_preference =
      (proton_window_theme_preference_t)theme_preference;
  window->button_position_custom = button_position_custom;
  window->button_position_x = button_position_x;
  window->button_position_y = button_position_y;
  snprintf(window->titlebar_minimize_label,
           sizeof(window->titlebar_minimize_label), "%s",
           titlebar_minimize_label != NULL ? titlebar_minimize_label : "");
  snprintf(window->titlebar_maximize_label,
           sizeof(window->titlebar_maximize_label), "%s",
           titlebar_maximize_label != NULL ? titlebar_maximize_label : "");
  snprintf(window->titlebar_restore_label,
           sizeof(window->titlebar_restore_label), "%s",
           titlebar_restore_label != NULL ? titlebar_restore_label : "");
  snprintf(window->titlebar_close_label,
           sizeof(window->titlebar_close_label), "%s",
           titlebar_close_label != NULL ? titlebar_close_label : "");
  return PROTON_OK;
}


int32_t proton_platform_window_materialize(
    proton_platform_window_t *window, proton_engine_runtime_t *runtime,
    proton_window_id_t public_window, char *error, size_t error_len) {
  if (window == NULL) {
    return PROTON_ERR_INVALID_ARGUMENT;
  }
  if (window->backend != NULL) {
    return PROTON_OK;
  }
  proton_engine_window_config_t config;
  memset(&config, 0, sizeof(config));
  config.public_window = public_window;
  snprintf(config.title, sizeof(config.title), "%s", window->title);
  config.width = window->width;
  config.height = window->height;
  config.size_hint = window->size_hint;
  config.titlebar_overlay = window->titlebar_overlay;
  config.theme_preference = window->theme_preference;
  config.button_position_custom = window->button_position_custom;
  config.button_position_x = window->button_position_x;
  config.button_position_y = window->button_position_y;
  snprintf(config.titlebar_minimize_label,
           sizeof(config.titlebar_minimize_label), "%s",
           window->titlebar_minimize_label);
  snprintf(config.titlebar_maximize_label,
           sizeof(config.titlebar_maximize_label), "%s",
           window->titlebar_maximize_label);
  snprintf(config.titlebar_restore_label,
           sizeof(config.titlebar_restore_label), "%s",
           window->titlebar_restore_label);
  snprintf(config.titlebar_close_label,
           sizeof(config.titlebar_close_label), "%s",
           window->titlebar_close_label);
  config.defer_presentation = 1;
  return proton_engine_window_create(runtime, &config, &window->backend,
                                     error, error_len);
}

int32_t proton_platform_window_destroy_shell(
    proton_platform_window_t *window, char *error, size_t error_len) {
  if (window == NULL || window->backend == NULL) {
    return PROTON_OK;
  }
  int32_t status =
      proton_engine_window_destroy(window->backend, error, error_len);
  if (status == PROTON_OK) {
    window->backend = NULL;
  }
  return status;
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


static int32_t proton_platform_window_require_backend(
    proton_platform_window_t *window) {
  return window != NULL && window->backend != NULL
             ? PROTON_OK
             : PROTON_ERR_UNSUPPORTED;
}

int32_t proton_platform_window_set_minimum_size(
    proton_platform_window_t *window, int32_t width, int32_t height,
    char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_minimum_size(window->backend, width, height,
                                               error, error_len);
}
int32_t proton_platform_window_set_maximum_size(
    proton_platform_window_t *window, int32_t width, int32_t height,
    char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_maximum_size(window->backend, width, height,
                                               error, error_len);
}
int32_t proton_platform_window_set_aspect_ratio(
    proton_platform_window_t *window, double aspect_ratio, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_aspect_ratio(window->backend, aspect_ratio,
                                               error, error_len);
}
int32_t proton_platform_window_set_movable(
    proton_platform_window_t *window, int32_t movable, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_movable(window->backend, movable, error,
                                          error_len);
}
int32_t proton_platform_window_set_opacity(
    proton_platform_window_t *window, double opacity, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_opacity(window->backend, opacity, error,
                                          error_len);
}
int32_t proton_platform_window_set_skip_taskbar(
    proton_platform_window_t *window, int32_t skip, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_skip_taskbar(window->backend, skip, error,
                                               error_len);
}
int32_t proton_platform_window_set_content_protection(
    proton_platform_window_t *window, int32_t enabled, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_content_protection(window->backend, enabled,
                                                     error, error_len);
}
int32_t proton_platform_window_set_minimizable(
    proton_platform_window_t *window, int32_t minimizable, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_minimizable(window->backend, minimizable,
                                              error, error_len);
}
int32_t proton_platform_window_set_maximizable(
    proton_platform_window_t *window, int32_t maximizable, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_maximizable(window->backend, maximizable,
                                              error, error_len);
}
int32_t proton_platform_window_set_closable(
    proton_platform_window_t *window, int32_t closable, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_closable(window->backend, closable, error,
                                           error_len);
}
int32_t proton_platform_window_set_button_position(
    proton_platform_window_t *window, int32_t custom, int32_t x, int32_t y,
    char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_button_position(window->backend, custom, x, y,
                                                  error, error_len);
}
int32_t proton_platform_window_get_button_position(
    proton_platform_window_t *window, int32_t *custom, int32_t *x, int32_t *y,
    char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_get_button_position(window->backend, custom, x, y,
                                                  error, error_len);
}
int32_t proton_platform_window_set_button_visibility(
    proton_platform_window_t *window, int32_t visible, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_button_visibility(window->backend, visible,
                                                    error, error_len);
}
int32_t proton_platform_window_set_focusable(
    proton_platform_window_t *window, int32_t focusable, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_focusable(window->backend, focusable, error,
                                            error_len);
}
int32_t proton_platform_window_set_fullscreenable(
    proton_platform_window_t *window, int32_t fullscreenable, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_fullscreenable(window->backend,
                                                 fullscreenable, error,
                                                 error_len);
}
int32_t proton_platform_window_set_has_shadow(
    proton_platform_window_t *window, int32_t has_shadow, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_has_shadow(window->backend, has_shadow, error,
                                             error_len);
}
int32_t proton_platform_window_set_ignore_mouse_events(
    proton_platform_window_t *window, int32_t ignore, int32_t forward,
    char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_ignore_mouse_events(window->backend, ignore,
                                                      forward, error, error_len);
}
int32_t proton_platform_window_set_background_color(
    proton_platform_window_t *window, uint32_t color, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_background_color(window->backend, color,
                                                   error, error_len);
}
int32_t proton_platform_window_set_theme(
    proton_platform_window_t *window,
    proton_window_theme_preference_t theme_preference, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_theme(window->backend, theme_preference,
                                        error, error_len);
}
int32_t proton_platform_window_set_visible_on_all_workspaces(
    proton_platform_window_t *window, int32_t visible, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_visible_on_all_workspaces(
      window->backend, visible, error, error_len);
}
int32_t proton_platform_window_set_enabled(
    proton_platform_window_t *window, int32_t enabled, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_enabled(window->backend, enabled, error,
                                          error_len);
}
int32_t proton_platform_window_set_progress_bar(
    proton_platform_window_t *window, double progress, int32_t mode,
    char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_progress_bar(window->backend, progress, mode,
                                               error, error_len);
}
int32_t proton_platform_window_set_overlay_icon(
    proton_platform_window_t *window, proton_engine_image_t *overlay,
    const char *description, char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_overlay_icon(window->backend, overlay,
                                               description, error, error_len);
}
int32_t proton_platform_window_set_thumbnail_tooltip(
    proton_platform_window_t *window, const char *tooltip, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_thumbnail_tooltip(window->backend, tooltip,
                                                    error, error_len);
}
int32_t proton_platform_window_set_thumbar_buttons(
    proton_platform_window_t *window,
    const proton_engine_thumbar_button_t *buttons, int32_t button_count,
    int32_t *out_applied, char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_thumbar_buttons(
      window->backend, buttons, button_count, out_applied, error, error_len);
}
int32_t proton_platform_window_flash_frame(
    proton_platform_window_t *window, int32_t flash, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_flash_frame(window->backend, flash, error,
                                          error_len);
}


int32_t proton_platform_window_popup_menu(
    proton_platform_window_t *window, int32_t x, int32_t y,
    const proton_menu_bar_t *menu_bar, char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_popup_menu(window->backend, x, y, menu_bar,
                                         error, error_len);
}
int32_t proton_platform_window_close(
    proton_platform_window_t *window, char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_close(window->backend, error, error_len);
}
int32_t proton_platform_window_set_close_interception(
    proton_platform_window_t *window, int32_t enabled, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_set_close_interception(window->backend, enabled,
                                                     error, error_len);
}
int32_t proton_platform_window_respond_close_request(
    proton_platform_window_t *window, uint64_t request_id, int32_t allow,
    char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_respond_close_request(window->backend, request_id,
                                                    allow, error, error_len);
}
int32_t proton_platform_window_begin_message_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *message_utf8, int32_t message_len,
    int32_t level, int64_t *out_dialog, char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_begin_message_dialog(
      window->backend, title_utf8, title_len, message_utf8, message_len, level,
      out_dialog, error, error_len);
}
int32_t proton_platform_window_begin_confirm_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *message_utf8, int32_t message_len,
    int32_t level, int64_t *out_dialog, char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_begin_confirm_dialog(
      window->backend, title_utf8, title_len, message_utf8, message_len, level,
      out_dialog, error, error_len);
}
int32_t proton_platform_window_begin_open_file_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *path_utf8, int32_t path_len,
    int64_t *out_dialog, char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_begin_open_file_dialog(
      window->backend, title_utf8, title_len, path_utf8, path_len, out_dialog,
      error, error_len);
}
int32_t proton_platform_window_begin_save_file_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *path_utf8, int32_t path_len,
    int64_t *out_dialog, char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_begin_save_file_dialog(
      window->backend, title_utf8, title_len, path_utf8, path_len, out_dialog,
      error, error_len);
}
int32_t proton_platform_window_begin_choose_directory_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *path_utf8, int32_t path_len,
    int64_t *out_dialog, char *error, size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_begin_choose_directory_dialog(
      window->backend, title_utf8, title_len, path_utf8, path_len, out_dialog,
      error, error_len);
}
int32_t proton_platform_window_cancel_dialog(
    proton_platform_window_t *window, int64_t dialog, char *error,
    size_t error_len) {
  if (proton_platform_window_require_backend(window) != PROTON_OK)
    return PROTON_ERR_UNSUPPORTED;
  return proton_engine_window_cancel_dialog(window->backend, dialog, error,
                                             error_len);
}
