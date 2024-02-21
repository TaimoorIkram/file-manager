#include "command_line.hpp"

namespace fs {
	FSCommandLine::FSCommandLine() {
		fsKernel = new FSKernel();
		fsKernel->startKernel();
	}
}