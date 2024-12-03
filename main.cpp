#include <memory>

#include "BlockyEngine.hpp"

void force_memleak() {
	int* p_int = new int;
}

int main(int argc, char** argv) {
	force_memleak();
	BlockyEngine engine;
	engine.Run();
}