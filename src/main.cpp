#include <pthread.h>

#include "app.hpp"
#include "audio.hpp"
#include "configuration.hpp"
#include "render.hpp"
#include "update.hpp"

int main(int argc, char** argv) {

	auto __args = app::Args::parse(argc, argv);
	if (!__args) return app::err::PARSING;
	app::Args args = std::move(*__args);

	auto __state = app::startup(args);
	if (!__state) return app::err::STARTING;
	app::ProtectedState state = std::move(*__state);

	auto __update_thread = update::thread(&state);
	if (!__update_thread) return app::err::UPDATING;
	pthread_t update_thread = std::move(*__update_thread);

	// TODO: start audio thread

	if (int err = render::routine(&state))
		return err;

	// TODO: join audio thread

	void* update_retval;
	if (pthread_join(update_thread, &update_retval))
		return app::err::UPDATING;
	if (int err = app::err::from_ptr(update_retval))
		return err;

	app::shutdown(&state);

	return app::err::NONE;
}
