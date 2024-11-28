#include <memory>

#include "BlockyEngine.hpp"

#define TEST 0

int main(int argc, char** argv) {
#if TEST
	//	return RUN_ALL_TESTS();
		return 0;
#endif

	BlockyEngine engine;
	engine.Run();
}