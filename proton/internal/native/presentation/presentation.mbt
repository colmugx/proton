///|
/// The private application-lifetime boundary implemented by a presentation
/// backend. Platform code may retain `handle` for operating-system services;
/// presentation lifecycle operations remain owned by this value.
pub(all) struct Runtime {
  handle : @native_ffi.RuntimeHandle
  begin_destroy : () -> Int
  destroy_ready : (Ref[Int]) -> Int
  finish_destroy : () -> Int
  create_surface : (SurfaceConfig, Ref[Int]) -> Surface
}

///|
/// Presentation content attached to a platform window.
pub(all) struct Surface {
  handle : @native_ffi.WindowHandle
  destroy : () -> Int
}

///|
/// The process and application lifetime entry points supplied by one backend.
pub(all) struct Driver {
  execute_process : (RuntimeConfig, Ref[Int]) -> Int
  create : (RuntimeConfig, Ref[Int]) -> Runtime
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
  title : Bytes
  width : Int
  height : Int
  initial_url : Bytes
  size_hint : Int
  titlebar_overlay : Int
  theme_preference : Int
  button_position_custom : Int
  button_position_x : Int
  button_position_y : Int
  navigation_policy : Int
  titlebar_minimize_label : Bytes
  titlebar_maximize_label : Bytes
  titlebar_restore_label : Bytes
  titlebar_close_label : Bytes
  new_window_policy : Int
  download_policy : Int
  certificate_policy : Int
  media_policy : Int
  devtools : Int
  bridge_config : @native_ffi.BridgeConfigHandle
  web_request_config : @native_ffi.WebRequestConfigHandle
}

///|
pub fn Driver::execute_process(
  self : Driver,
  config : RuntimeConfig,
  out_exit_code : Ref[Int],
) -> Int {
  (self.execute_process)(config, out_exit_code)
}

///|
pub fn Driver::create(
  self : Driver,
  config : RuntimeConfig,
  out_status : Ref[Int],
) -> Runtime {
  (self.create)(config, out_status)
}

///|
pub fn Runtime::begin_destroy(self : Runtime) -> Int {
  (self.begin_destroy)()
}

///|
pub fn Runtime::destroy_ready(self : Runtime, out_ready : Ref[Int]) -> Int {
  (self.destroy_ready)(out_ready)
}

///|
pub fn Runtime::finish_destroy(self : Runtime) -> Int {
  (self.finish_destroy)()
}

///|
pub fn Runtime::create_surface(
  self : Runtime,
  config : SurfaceConfig,
  out_status : Ref[Int],
) -> Surface {
  (self.create_surface)(config, out_status)
}

///|
pub fn Surface::destroy(self : Surface) -> Int {
  (self.destroy)()
}
