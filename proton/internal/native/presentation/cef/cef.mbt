///|
/// Ensures the CEF implementation and its platform adapter are linked.
fn ensure_linked() -> Unit {
  @mac_engine.ensure_linked()
  @cef_loader.ensure_linked()
}

///|
pub(all) struct RuntimeConfig {
  use_bundled : Int
  runtime_root : Bytes
  helper_path : Bytes
  resources_dir : Bytes
  locales_dir : Bytes
  cache_dir : Bytes
  locale : Bytes
  accept_languages : Bytes
  proxy_server : Bytes
  proxy_bypass : Bytes
  dialog_ok_label : Bytes
  dialog_cancel_label : Bytes
  remote_debugging_port : Int
  headless : Int
  accessibility_mode : Int
  persist_session_cookies : Int
}

///|
pub(all) struct SurfaceConfig {
  initial_url : Bytes
  navigation_policy : Int
  new_window_policy : Int
  download_policy : Int
  certificate_policy : Int
  media_policy : Int
  devtools : Int
  bridge_config : @native_ffi.BridgeConfigHandle
  web_request_config : @native_ffi.WebRequestConfigHandle
}

///|
pub fn execute_process(
  config : RuntimeConfig,
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
pub fn attach_runtime(
  platform : @native_ffi.RuntimeHandle,
  config : RuntimeConfig,
  out_status : Ref[Int],
) -> @presentation.Runtime {
  ensure_linked()
  out_status.val = @native_ffi.cef_runtime_attach(
    platform,
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
  )
  let handle = platform
  @presentation.Runtime::{
    begin_destroy: fn() {
      @native_ffi.proton_runtime_begin_destroy_ffi(handle)
    },
    destroy_ready: fn(out_ready) {
      @native_ffi.proton_runtime_destroy_ready_ffi(handle, out_ready)
    },
    finish_destroy: fn() {
      @native_ffi.proton_runtime_finish_destroy_ffi(handle)
    },
  }
}

///|
pub fn attach_surface(
  platform : @native_ffi.WindowHandle,
  config : SurfaceConfig,
  out_status : Ref[Int],
) -> @presentation.Surface {
  out_status.val = @native_ffi.cef_surface_attach(
    platform,
    config.initial_url,
    config.navigation_policy,
    config.new_window_policy,
    config.download_policy,
    config.certificate_policy,
    config.media_policy,
    config.devtools,
    config.bridge_config,
    config.web_request_config,
  )
  @presentation.Surface::{
    destroy: fn() { @native_ffi.cef_surface_detach(platform) },
  }
}
