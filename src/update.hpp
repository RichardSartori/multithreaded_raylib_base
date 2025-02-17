#pragma once

#include <optional>
#include <pthread.h>

#include "app.hpp"

namespace update {

	std::optional<pthread_t> thread(app::ProtectedState* ps);

}
