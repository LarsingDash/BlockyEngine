#include <memory>

#include "BlockyEngine.hpp"

#define TEST 1

int main() {
#if TEST
//	return RUN_ALL_TESTS();
	return 0;
#endif

    BlockyEngine engine;
    engine.Run();
}