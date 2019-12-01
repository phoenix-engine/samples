#include <atomic>
#include <iostream>
#include <thread>
#include <variant>

#include "sample.hpp"

namespace sample {

    template <typename Phoenix>
    void run(Phoenix& p) {
	std::atomic_bool done = false;

	std::thread render([&] {
	    while (!done.load()) {
		try {
		    p.render(nullptr);
		} catch (phx_err::Retry& e) {
		    std::cerr << "Renderer threw " << e.what()
		              << ", so retry." << std::endl;
		    continue;
		} catch (std::exception& e) {
		    std::cerr << "Renderer threw " << e.what()
		              << std::endl;
		    done = true;
		    return;
		}
	    }
	});

	while (true) {
	    event::Event evt = p.input_handle().queue_handle().await();
	    if (std::holds_alternative<event::EventWantsQuit>(evt)) {
		done = true;
		break;
	    }
	}

	render.join();
    }

    template void
    run<phx::Phoenix<input::Simple, phx_sdl::VKRenderer<false>>>(
      phx::Phoenix<input::Simple, phx_sdl::VKRenderer<false>>& p);

    template void
    run<phx::Phoenix<input::Simple, phx_sdl::VKRenderer<true>>>(
      phx::Phoenix<input::Simple, phx_sdl::VKRenderer<true>>& p);

} // namespace sample
