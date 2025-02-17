#include "configuration.hpp"
#include "raylib.h"
#include "update.hpp"

static void* routine(void* arg) {
	app::ProtectedState* ps = (app::ProtectedState*) arg;
	app::State state;
	int monitor = GetCurrentMonitor();
	int screen_width = GetMonitorWidth(monitor);
	int screen_height = GetMonitorHeight(monitor);
	while (!state.exit) {

		if (int err = ps->get(&state))
			return app::err::to_ptr(err);

		if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
			state.exit_requested = true;
		}

		if (state.exit_requested) {
			if (IsKeyPressed(KEY_Y)) state.exit = true;
			if (IsKeyPressed(KEY_N)) state.exit_requested = false;
		}

		if (IsKeyPressed(KEY_F)) {
			if (IsWindowFullscreen()) {
				SetWindowSize(app::window::WIDTH, app::window::HEIGHT);
			} else {
				SetWindowSize(screen_width, screen_height);
			}
			ToggleFullscreen();
		}

		if (int err = ps->set(&state))
			return app::err::to_ptr(err);
	}
	return app::err::to_ptr(app::err::NONE);
}

std::optional<pthread_t> update::thread(app::ProtectedState* ps) {
	pthread_t retval;
	if (int err = pthread_create(&retval, nullptr, routine, ps))
		return std::nullopt;
	return std::make_optional<pthread_t>(retval);
}
