#ifndef PROTON_PLATFORM_WINDOW_H
#define PROTON_PLATFORM_WINDOW_H

#include "proton_engine.h"

/*
 * Ownership boundary between a logical Proton window and its presentation.
 *
 * The backend pointer is deliberately private to this translation unit's
 * callers: facade code reaches native-window operations through this object,
 * while browser operations continue to use proton_engine_window_t directly.
 * This is the migration seam used while the per-OS native handles are moved
 * out of the historical engine structures.
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

#endif
