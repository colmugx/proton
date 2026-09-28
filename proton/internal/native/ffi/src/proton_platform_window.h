#ifndef PROTON_PLATFORM_WINDOW_H
#define PROTON_PLATFORM_WINDOW_H

#include "proton_engine.h"

/*
 * Ownership boundary between a logical Proton window and its presentation.
 *
 * Presentation state may be attached while CEF is active, but callers performing
 * native-window operations go through this type rather than reaching into the
 * presentation slot directly. That keeps the C ABI stable while the concrete
 * HWND/GtkWindow/NSWindow ownership is extracted behind this boundary.
 */
typedef struct proton_platform_window {
  proton_engine_window_t *backend;
  void *native_window;
  void *content_host;
  int32_t release_pending;
  char title[512];
  int32_t width;
  int32_t height;
  int32_t size_hint;
  int32_t titlebar_overlay;
  proton_window_theme_preference_t theme_preference;
  int32_t button_position_custom;
  int32_t button_position_x;
  int32_t button_position_y;
  char titlebar_minimize_label[PROTON_ENGINE_MAX_LABEL_BYTES];
  char titlebar_maximize_label[PROTON_ENGINE_MAX_LABEL_BYTES];
  char titlebar_restore_label[PROTON_ENGINE_MAX_LABEL_BYTES];
  char titlebar_close_label[PROTON_ENGINE_MAX_LABEL_BYTES];
} proton_platform_window_t;

PROTON_INTERNAL proton_platform_window_t *proton_platform_window_alloc(void);
PROTON_INTERNAL int32_t proton_platform_window_materialize(
    proton_platform_window_t *window, proton_engine_runtime_t *runtime,
    proton_window_id_t public_window, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_destroy_shell(
    proton_platform_window_t *window, char *error, size_t error_len);

PROTON_INTERNAL int32_t proton_platform_window_configure(
    proton_platform_window_t *window, const char *title, int32_t width,
    int32_t height, int32_t size_hint, int32_t titlebar_overlay,
    int32_t theme_preference, int32_t button_position_custom,
    int32_t button_position_x, int32_t button_position_y,
    const char *titlebar_minimize_label, const char *titlebar_maximize_label,
    const char *titlebar_restore_label, const char *titlebar_close_label);

PROTON_INTERNAL void proton_platform_window_free(
    proton_platform_window_t *window);
PROTON_INTERNAL void proton_platform_window_attach_backend(
    proton_platform_window_t *window, proton_engine_window_t *backend);
PROTON_INTERNAL void proton_platform_window_backend_finalized(
    proton_platform_window_t *window, proton_engine_window_t *backend);
PROTON_INTERNAL proton_engine_window_t *proton_platform_window_backend(
    proton_platform_window_t *window);
PROTON_INTERNAL void *proton_platform_window_native_handle(
    proton_platform_window_t *window);
PROTON_INTERNAL void *proton_platform_window_content_host(
    proton_platform_window_t *window);

PROTON_INTERNAL int32_t proton_platform_window_show(
    proton_platform_window_t *window, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_show_inactive(
    proton_platform_window_t *window, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_hide(
    proton_platform_window_t *window, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_focus(
    proton_platform_window_t *window, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_title(
    proton_platform_window_t *window, const char *title, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_size(
    proton_platform_window_t *window, int32_t width, int32_t height,
    char *error, size_t error_len);

PROTON_INTERNAL int32_t proton_platform_window_set_icon(
    proton_platform_window_t *window, const char *path, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_parent(
    proton_platform_window_t *window, proton_platform_window_t *parent,
    int32_t modal, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_content_size(
    proton_platform_window_t *window, int32_t width, int32_t height,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_get_content_size(
    proton_platform_window_t *window, int32_t *out_width, int32_t *out_height,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_get_titlebar_area(
    proton_platform_window_t *window, int32_t *out_x, int32_t *out_y,
    int32_t *out_width, int32_t *out_height, int32_t *out_zoom_percent,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_apply(
    proton_platform_window_t *window,
    const proton_engine_window_action_t *action, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_get_state(
    proton_platform_window_t *window, proton_engine_window_state_t *out_state,
    char *error, size_t error_len);

PROTON_INTERNAL int32_t proton_platform_window_set_minimum_size(
    proton_platform_window_t *window, int32_t width, int32_t height,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_maximum_size(
    proton_platform_window_t *window, int32_t width, int32_t height,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_aspect_ratio(
    proton_platform_window_t *window, double aspect_ratio, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_movable(
    proton_platform_window_t *window, int32_t movable, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_opacity(
    proton_platform_window_t *window, double opacity, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_skip_taskbar(
    proton_platform_window_t *window, int32_t skip, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_content_protection(
    proton_platform_window_t *window, int32_t enabled, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_minimizable(
    proton_platform_window_t *window, int32_t minimizable, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_maximizable(
    proton_platform_window_t *window, int32_t maximizable, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_closable(
    proton_platform_window_t *window, int32_t closable, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_button_position(
    proton_platform_window_t *window, int32_t custom, int32_t x, int32_t y,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_get_button_position(
    proton_platform_window_t *window, int32_t *custom, int32_t *x, int32_t *y,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_button_visibility(
    proton_platform_window_t *window, int32_t visible, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_focusable(
    proton_platform_window_t *window, int32_t focusable, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_fullscreenable(
    proton_platform_window_t *window, int32_t fullscreenable, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_has_shadow(
    proton_platform_window_t *window, int32_t has_shadow, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_ignore_mouse_events(
    proton_platform_window_t *window, int32_t ignore, int32_t forward,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_background_color(
    proton_platform_window_t *window, uint32_t color, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_theme(
    proton_platform_window_t *window,
    proton_window_theme_preference_t theme_preference, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_visible_on_all_workspaces(
    proton_platform_window_t *window, int32_t visible, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_enabled(
    proton_platform_window_t *window, int32_t enabled, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_progress_bar(
    proton_platform_window_t *window, double progress, int32_t mode,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_overlay_icon(
    proton_platform_window_t *window, proton_engine_image_t *overlay,
    const char *description, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_thumbnail_tooltip(
    proton_platform_window_t *window, const char *tooltip, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_thumbar_buttons(
    proton_platform_window_t *window,
    const proton_engine_thumbar_button_t *buttons, int32_t button_count,
    int32_t *out_applied, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_flash_frame(
    proton_platform_window_t *window, int32_t flash, char *error,
    size_t error_len);

PROTON_INTERNAL int32_t proton_platform_window_popup_menu(
    proton_platform_window_t *window, int32_t x, int32_t y,
    const proton_menu_bar_t *menu_bar, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_close(
    proton_platform_window_t *window, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_set_close_interception(
    proton_platform_window_t *window, int32_t enabled, char *error,
    size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_respond_close_request(
    proton_platform_window_t *window, uint64_t request_id, int32_t allow,
    char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_begin_message_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *message_utf8, int32_t message_len,
    int32_t level, int64_t *out_dialog, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_begin_confirm_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *message_utf8, int32_t message_len,
    int32_t level, int64_t *out_dialog, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_begin_open_file_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *path_utf8, int32_t path_len,
    int64_t *out_dialog, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_begin_save_file_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *path_utf8, int32_t path_len,
    int64_t *out_dialog, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_begin_choose_directory_dialog(
    proton_platform_window_t *window, const char *title_utf8,
    int32_t title_len, const char *path_utf8, int32_t path_len,
    int64_t *out_dialog, char *error, size_t error_len);
PROTON_INTERNAL int32_t proton_platform_window_cancel_dialog(
    proton_platform_window_t *window, int64_t dialog, char *error,
    size_t error_len);

#endif
