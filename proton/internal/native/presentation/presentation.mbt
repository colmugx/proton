///|
/// Backend lifecycle attached to a platform runtime.  This deliberately owns
/// no platform handle and carries no browser configuration.
pub(all) struct Runtime {
  begin_destroy : () -> Int
  destroy_ready : (Ref[Int]) -> Int
  finish_destroy : () -> Int
}

///|
/// Presentation content attached to a platform window.  Backend-specific
/// state stays captured by the implementation rather than leaking through the
/// generic contract.
pub(all) struct Surface {
  destroy : () -> Int
}

///|
pub fn Runtime::begin_destroy(self : Runtime) -> Int { (self.begin_destroy)() }

///|
pub fn Runtime::destroy_ready(self : Runtime, out_ready : Ref[Int]) -> Int {
  (self.destroy_ready)(out_ready)
}

///|
pub fn Runtime::finish_destroy(self : Runtime) -> Int { (self.finish_destroy)() }

///|
pub fn Surface::destroy(self : Surface) -> Int { (self.destroy)() }
