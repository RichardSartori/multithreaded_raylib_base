#include "configuration.hpp"
#include "render.hpp"
#include "raylib.h"

int render::routine(app::ProtectedState* ps) {
	app::State state;
	while (!state.exit) {

		if (int err = ps->get(&state))
			return err;

		BeginDrawing();

		if (state.exit_requested) {
			ClearBackground(RED);
			DrawText("REALLY? (y/n)", 10, 250, 100, BLACK);
		} else {
			ClearBackground(app::BACKGROUND);
		}

		EndDrawing();
	}
	return app::err::NONE;
}
