///|
/// Ensures the CEF implementation and its platform adapter are linked.
fn ensure_linked() -> Unit {
  @mac_engine.ensure_linked()
  @cef_loader.ensure_linked()
}

///|
fn execute_process(
  config : @presentation.RuntimeConfig,
  out_exit_code : Ref[Int],
) -> Int {
  ensure_linked()
  @native_ffi.execute_process(
    config.use_bundled,
    config.runtime_root,
    config.helper_path,
    config.resources_dir,
    config.locales_dir,
    config.cache_dir,
    config.locale,
    config.accept_languages,
    config.dialog_ok_label,
    config.dialog_cancel_label,
    config.remote_debugging_port,
    config.headless,
    config.persist_session_cookies,
    out_exit_code,
  )
}

///|
fn create(
  config : @presentation.RuntimeConfig,
  out_status : Ref[Int],
) -> @presentation.Runtime {
  ensure_linked()
  let out_runtime = Ref(@native_ffi.runtime_null())
  out_status.val = @native_ffi.runtime_create(
    config.use_bundled,
    config.runtime_root,
    config.helper_path,
    config.resources_dir,
    config.locales_dir,
    config.cache_dir,
    config.locale,
    config.accept_languages,
    config.proxy_server,
    config.proxy_bypass,
    config.dialog_ok_label,
    config.dialog_cancel_label,
    config.remote_debugging_port,
    config.headless,
    config.accessibility_mode,
    config.persist_session_cookies,
    out_runtime,
  )
  let handle = out_runtime.val
  @presentation.Runtime::{
    handle,
    begin_destroy: fn() {
      @native_ffi.proton_runtime_begin_destroy_ffi(handle)
    },
    destroy_ready: fn(out_ready) {
      @native_ffi.proton_runtime_destroy_ready_ffi(handle, out_ready)
    },
    finish_destroy: fn() {
      @native_ffi.proton_runtime_finish_destroy_ffi(handle)
    },
    create_surface: fn(config, out_status) {
      create_surface(handle, config, out_status)
    },
  }
}

///|
fn create_surface(
  runtime : @native_ffi.RuntimeHandle,
  config : @presentation.SurfaceConfig,
  out_status : Ref[Int],
) -> @presentation.Surface {
  let out_window = Ref(@native_ffi.window_null())
  out_status.val = @native_ffi.window_create(
    runtime,
    config.title,
    config.width,
    config.height,
    config.initial_url,
    config.size_hint,
    config.titlebar_overlay,
    config.theme_preference,
    config.button_position_custom,
    config.button_position_x,
    config.button_position_y,
    config.navigation_policy,
    config.titlebar_minimize_label,
    config.titlebar_maximize_label,
    config.titlebar_restore_label,
    config.titlebar_close_label,
    config.new_window_policy,
    config.download_policy,
    config.certificate_policy,
    config.media_policy,
    config.devtools,
    config.bridge_config,
    config.web_request_config,
    out_window,
  )
  let handle = out_window.val
  @presentation.Surface::{
    handle,
    destroy: fn() { @native_ffi.proton_window_destroy_ffi(handle) },
  }
}

///|
pub fn driver() -> @presentation.Driver {
  @presentation.Driver::{ execute_process, create, }
}
