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
} proton_platform_window_t;

PROTON_INTERNAL proton_platform_window_t *proton_platform_window_alloc(void);
PROTON_INTERNAL void proton_platform_window_free(
    proton_platform_window_t *window);
PROTON_INTERNAL void proton_platform_window_attach_backend(
    proton_platform_window_t *window, proton_engine_window_t *backend);
PROTON_INTERNAL proton_engine_window_t *proton_platform_window_backend(
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

#endif
