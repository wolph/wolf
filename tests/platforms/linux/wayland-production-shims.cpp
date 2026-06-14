/**
 * Test-only scaffolding for the LINK_RUST_WAYLAND=ON build.
 *
 * Production Wolf always uses the GStreamer wayland plugin path
 * (gst-wayland-display.cpp), so wolf_core's default build provides the
 * gst-signature entry points below. The [WAYLAND] test suite instead builds
 * wolf_core against the Rust C-bindings impl (wayland-display.cpp), which does
 * NOT provide these entry points -- but moonlight-server (libwolf_runner, linked
 * into wolftests) still references them. These no-op stubs satisfy that link in
 * the test binary so the gst-signature symbols never leak into production code.
 *
 * Compiled into wolftests only when LINK_RUST_WAYLAND=ON (see tests/CMakeLists.txt).
 */

#include <core/virtual-display.hpp>
#include <helpers/logger.hpp>

namespace wolf::core::virtual_display {

wl_state_ptr create_wayland_display(gstreamer::gst_element_ptr /*wayland_plugin*/,
                                    const std::string & /*wayland_socket_name*/) {
  logs::log(logs::warning,
            "[WAYLAND] gst-signature create_wayland_display invoked in a LINK_RUST_WAYLAND=ON "
            "test build; this path is gst-only, returning nullptr");
  return nullptr;
}

std::string get_wayland_socket_name(WaylandState & /*w_state*/) {
  logs::log(logs::warning,
            "[WAYLAND] get_wayland_socket_name invoked in a LINK_RUST_WAYLAND=ON test build; "
            "this path is gst-only, returning empty string");
  return {};
}

} // namespace wolf::core::virtual_display
