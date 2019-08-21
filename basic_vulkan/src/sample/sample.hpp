#ifndef SMP_BASIC_VULKAN
#define SMP_BASIC_VULKAN

#include <errors.hpp>
#include <input.hpp>
#include <phoenix.hpp>
#include <phx_sdl/sdl_input.hpp>
#include <phx_sdl/vk_renderer.hpp>
#include <phx_sdl/window.hpp>

namespace sample {

    template <typename Phoenix =
                phx::Phoenix<input::Simple, phx_sdl::VKRenderer<false>>>
    void run(Phoenix& p);

} // namespace sample

#endif // SMP_BASIC_VULKAN
