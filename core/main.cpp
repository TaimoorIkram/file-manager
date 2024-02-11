#include "kernel.hpp"

int main(int argc, const char** argv) {
    fs::FSKernel krnl;
    try {
        krnl.startKernel();
    }
    catch (std::exception e) {
        e.what();
    }
    std::getchar();
}