#pragma once

#include <cstddef>
#include <cstdint>

#include "raylib.h"

namespace app {

	inline constexpr int EXIT_KEY = KEY_Q;
	inline constexpr int TARGET_FPS = 120;
	inline constexpr Color BACKGROUND = GREEN;

	namespace entity {
		inline constexpr size_t COUNT = 5;
		inline constexpr float RADIUS = 10.0f;
		inline constexpr Color COLOR = RED;
		// TODO: inline constexpr Sound COLLISION_SOUND = _;
	}

	namespace window {
		inline constexpr char const NAME[] = "TEST";
		inline constexpr int WIDTH = 800;
		inline constexpr int HEIGHT = 600;
	}

	namespace err {
		inline constexpr int NONE = 0;
		inline constexpr int PARSING = 1;
		inline constexpr int MUTEX = 2;
		inline constexpr int STARTING = 3;
		inline constexpr int UPDATING = 4;
		inline constexpr int RENDERING = 5;

		inline constexpr void* to_ptr(int code) {
			return reinterpret_cast<void*>(static_cast<uintptr_t>(code));
		}

		inline constexpr int from_ptr(void* ptr) {
			return static_cast<int>(reinterpret_cast<uintptr_t>(ptr));
		}
	}
}
