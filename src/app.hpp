#pragma once

#include <array>
#include <optional>
#include <pthread.h>

#include "configuration.hpp"

namespace app {

	struct Args {
		bool fullscreen; // should the application start in fullscreen mode?
		bool gravity; // should the application apply gravity to entities?

		Args(void);

		static std::optional<Args> parse(int argc, char** argv);
	};

	struct Entity {
		Vector2 position;
		Vector2 speed;

		Entity(void);

		// TODO:
		// void draw(void) const;

		// TODO:
		// // return true if e1 collided with e2
		// static bool resolve_collision(Entity& e1, Entity& e2);
		// see CPP/*/RICO/examples/gravity.cpp : Body::force
		// set state.play_sound to true every time a collision is detected

		// TODO:
		// static void apply_gravity(Entity& e);
	};

	struct State {
		bool exit_requested;
		bool exit;
		bool gravity;
		bool play_sound;
		std::array<Entity, entity::COUNT> entities;

		State(void);

		State(State const&) = default;
		State& operator=(State const&) = default;
	};

	class ProtectedState {
	public:

		ProtectedState(State state);
		~ProtectedState(void) noexcept;
		ProtectedState(ProtectedState&& other);

		ProtectedState(ProtectedState const&) = delete;
		ProtectedState& operator=(ProtectedState const&) = delete;

		int get(State* retval);
		int set(State const* new_state);

	private:
		pthread_mutex_t lock;
		State state;
	};

	std::optional<ProtectedState> startup(Args args);
	void shutdown(ProtectedState* ps);
}
