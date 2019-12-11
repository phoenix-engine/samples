#include <atomic>
#include <iomanip>
#include <iostream>
#include <thread>
#include <variant>

#include "event.hpp"
#include "pushconst.hpp"

namespace sample {

    template <typename Phoenix>
    void run(Phoenix& p) {
	std::atomic_bool done = false;

	bool     input_done = false;
	uint64_t i = 0, frame_count = 0;

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

		if (frame_count % 100 == 0) {
		    const auto mets = p.get_metrics().gfx.renderer;
		    using mt        = decltype(mets);

		    std::cerr << "Frame time: " << std::setprecision(3)
		              << std::chrono::duration_cast<mt::ms>(
		                   mets.avg_frame_time)
		                   .count()
		              << "ms" << std::endl;
		    frame_count = 0;
		}

		frame_count++;
	    }
	});

	while (!input_done) {
	    using namespace event;
	    using namespace event::helpers;

	    const auto& evt = p.input_handle().queue_handle().await();

	    std::visit(
	      event_cases{
	        [&](EventWantsQuit q) { done = input_done = true; },
	        [&](EventIntent in) {
		    if (i++ % 25 == 0) {
		        std::cerr << "Intent: (" << in.x << ", " << in.y
		                  << ")" << std::endl;
		    }
		    p.update(in);
	        },
	        [&](auto e) {
		    std::cerr
		      << "Unhandled event type: " << typeid(e).name()
		      << std::endl;
	        } },
	      evt);
	}

	render.join();
    } // namespace sample

    template void
    run<phx::Phoenix<input::Simple, phx_sdl::VKRenderer<false>>>(
      phx::Phoenix<input::Simple, phx_sdl::VKRenderer<false>>& p);

    template void
    run<phx::Phoenix<input::Simple, phx_sdl::VKRenderer<true>>>(
      phx::Phoenix<input::Simple, phx_sdl::VKRenderer<true>>& p);

} // namespace sample
