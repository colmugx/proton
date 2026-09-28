#include "../../src/proton_platform_window.h"

#include <stdint.h>
#include <string.h>

#define CHECK(condition)                                                       \
  do {                                                                         \
    if (!(condition)) {                                                        \
      result = __LINE__;                                                       \
      goto cleanup;                                                            \
    }                                                                          \
  } while (0)

int32_t proton_test_platform_window_cross_platform_canary(void) {
  int32_t result = 0;
  char error[512] = {0};
  proton_platform_window_t *platform = proton_platform_window_alloc();

  CHECK(platform != NULL);
  CHECK(proton_platform_window_configure(
            platform, "Platform-only canary", 480, 320, 0, 0,
            PROTON_WINDOW_THEME_PREFERENCE_SYSTEM, 0, 0, 0,
            "", "", "", "") == PROTON_OK);

  /* The architectural contract under test: no presentation runtime exists. */
  CHECK(proton_platform_window_materialize(platform, NULL, 0x51A7, error,
                                           sizeof(error)) == PROTON_OK);
  CHECK(platform->backend != NULL);
  CHECK(proton_platform_window_native_handle(platform) != NULL);
  CHECK(proton_platform_window_content_host(platform) != NULL);

  CHECK(proton_platform_window_set_title(
            platform, "Platform-only renamed", error, sizeof(error)) ==
        PROTON_OK);
  CHECK(proton_platform_window_set_size(platform, 520, 360, error,
                                        sizeof(error)) == PROTON_OK);
  CHECK(proton_platform_window_hide(platform, error, sizeof(error)) ==
        PROTON_OK);
  CHECK(proton_platform_window_show(platform, error, sizeof(error)) ==
        PROTON_OK);
  CHECK(proton_platform_window_focus(platform, error, sizeof(error)) ==
        PROTON_OK);

cleanup:
  if (platform != NULL) {
    if (platform->backend != NULL) {
      (void)proton_platform_window_destroy_shell(platform, error,
                                                 sizeof(error));
    }
    proton_platform_window_free(platform);
  }
  return result;
}
