#include <memory>

#include "BlockyEngine.hpp"

int main() {
	std::unique_ptr<BlockyEngine> blockyEngine = std::make_unique<BlockyEngine>();
	blockyEngine->Run();
}