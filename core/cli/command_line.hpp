#include "../kernel.hpp"

namespace fs {
	/**
	* @brief A representation of the file system kernel overlay, 
	* responsible for taking in the commands from the user and
	* then performing them through the file system kernel.
	*/
	class FSCommandLine {
	public:
		FSCommandLine();
		~FSCommandLine();
	
	private:
		FSKernel *fsKernel;

	};
}