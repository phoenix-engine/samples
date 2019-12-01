 #include <iostream>
#include <thread>

#include "sample.hpp"

int main(int argc, char* argv[]) {
#ifdef NDEBUG
    constexpr const bool debugging = false;
#else
    constexpr const bool debugging = true;
#endif

    try {
	using namespace phx_sdl;
	auto w = Window("BasicVulkan", SDL_WINDOWPOS_CENTERED,
	                SDL_WINDOWPOS_CENTERED, 1024, 768,
	                VKRenderer<debugging>::window_flags());

	// TODO: Move width and height into renderer API?
	// TODO: Make error API visible to non-dev users.
	VKRenderer<debugging> r(std::move(w));
	gfx::extent           e = r.extent();
	gfx::Graphics         g(std::move(r), e.width, e.height);
	input::Input          inp(&input::simple);
	phx::Phoenix          p(std::move(g), std::move(inp));
	Input                 pinp(p.input_handle());

	// Launch game logic in its own thread.
	std::thread t([&] { sample::run(p); });

	// Block the main thread on input loop.
	pinp.poll();
	t.join();

    } catch (std::exception& e) {
	std::cerr << "Exception during Phoenix initialization: "
	          << e.what();
	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
