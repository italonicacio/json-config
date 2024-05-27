#include <iostream>

#include "environment.hpp"

int main(int argc, char* argv[]) {
	Environment* env = Environment::GetInstance();

	std::cout << "epsilon: " << env->epsilon << "\n";
	std::cout << "max_size: " << env->max_size << "\n";
	std::cout << "path: " << env->path << "\n";
	std::cout << "runtime_mode: " << env->runtime_mode << "\n";
	std::cout << "size: " << env->size << "\n";


	return 0;
}
