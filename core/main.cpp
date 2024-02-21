#include "kernel.hpp"

int main(int argc, const char** argv) {
    fs::FSKernel krnl;
    try {
        krnl.startKernel();
    }
    catch (fs::FSException e) {
        std::cout << e.what() << std::endl;
    }
    std::getchar();
}