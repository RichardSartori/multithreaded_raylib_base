#include <getopt.h>
#include <iostream>

#include "app.hpp"
#include "configuration.hpp"
#include "raylib.h"

app::Args::Args(void)
	: fullscreen(false)
	, gravity(false)
{}

static void usage(char const* app_name) {
	std::cerr
		<< "Usage: " << app_name << " [OPTION]..."         << '\n'
		<< "A simple application using Raylib"             << '\n'
		<< "	-f, --fullscreen start in fullscreen mode" << '\n'
		<< "	-g, --gravity    apply gravity"            << '\n'
		<< "	-h, --help       display this help"        << '\n'
	;
}

static inline constexpr char SHORT_OPTIONS[] = "fgh";

static inline constexpr struct option LONG_OPTIONS[] = {
	{ "fullscreen", no_argument, 0, 'f' },
	{ "gravity",    no_argument, 0, 'g' },
	{ "help",       no_argument, 0, 'h' },
	{ 0, 0, 0, 0 }, // sentinel
};

std::optional<app::Args> app::Args::parse(int argc, char** argv) {
	char const* app_name = (argc != 0) ? argv[0] : "";
	app::Args retval;
	int opt;
	while (true) {
		opt = getopt_long(argc, argv, SHORT_OPTIONS, LONG_OPTIONS, nullptr);
		if (opt == -1) break;
		switch (opt) {
			case 'f': {
				retval.fullscreen = true;
				break;
			}
			case 'g': {
				retval.gravity = true;
				break;
			}
			case 'h': {
				usage(app_name);
				return std::nullopt;
			}
			case '?': {
				std::cerr << "unknown option\n";
				return std::nullopt;
			}
		}
	}
	return std::make_optional<app::Args>(retval);
}

// FIXME: use random values
app::Entity::Entity(void) {
	position.x = static_cast<float>(app::window::WIDTH / 2);
	position.y = static_cast<float>(app::window::HEIGHT / 2);
	speed.x = 0.0f;
	speed.y = 0.0f;
}

app::State::State(void)
	: exit_requested(false)
	, exit(false)
	, entities()
{}

app::ProtectedState::ProtectedState(app::State _state)
	: state(_state)
{
	// pthread_mutex_init always return 0
	(void) pthread_mutex_init(&lock, nullptr);
}

app::ProtectedState::~ProtectedState(void) noexcept {
	// lock should not be busy when reaching here
	(void) pthread_mutex_destroy(&lock);
}

app::ProtectedState::ProtectedState(app::ProtectedState&& other)
	: ProtectedState(other.state)
{}

int app::ProtectedState::get(app::State* retval) {
	if (pthread_mutex_lock(&lock) != 0)
		return app::err::MUTEX;
	*retval = state;
	if (pthread_mutex_unlock(&lock) != 0)
		return app::err::MUTEX;
	return app::err::NONE;
}

int app::ProtectedState::set(app::State const* new_state) {
	if (pthread_mutex_lock(&lock) != 0)
		return app::err::MUTEX;
	state = *new_state;
	if (pthread_mutex_unlock(&lock) != 0)
		return app::err::MUTEX;
	return app::err::NONE;
}

std::optional<app::ProtectedState> app::startup(app::Args args) {
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(
		app::window::WIDTH,
		app::window::HEIGHT,
		app::window::NAME
	);
	if (args.fullscreen) {
		int monitor = GetCurrentMonitor();
		int width = GetMonitorWidth(monitor);
		int height = GetMonitorHeight(monitor);
		SetWindowSize(width, height);
		ToggleFullscreen();
	}
	SetExitKey(app::EXIT_KEY);
	SetTargetFPS(app::TARGET_FPS);
	State initial_state;
	return std::make_optional<app::ProtectedState>(initial_state);
}

void app::shutdown(app::ProtectedState* ps) {
	(void) ps;
	CloseWindow();
}
