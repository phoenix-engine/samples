#include <iostream>
#include <thread>

#include <phx_sdl/scene.hpp>

#include "pushconst.hpp"

using namespace phx_sdl;

#ifdef NDEBUG
constexpr const bool debugging = false;
#else
constexpr const bool debugging = true;
#endif

auto setup_phoenix() {
    VKRenderer<debugging> r(
      Window("BasicWorld2D", SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED, 1024, 768,
             VKRenderer<debugging>::window_flags()),
      DefaultScenes::pushconstants);

    auto e = r.extent();

    return phx::Phoenix(gfx::Graphics(std::move(r), e.width, e.height),
                        input::Input(&input::simple));
}

int main(int argc, char* argv[]) {
    try {
	auto  p = setup_phoenix();
	Input pinp(p.input_handle());

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
