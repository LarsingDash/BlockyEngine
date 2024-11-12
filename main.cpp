#include "engine/TestClass.hpp"
#include "./engine/logging/BLogger.hpp"


int main() {
	BLOCKY_ENGINE_DEBUG("Debugging information.");
	// Example usage of the logger
	for (int i = 0; i < 5; i++) {
		BLOCKY_ENGINE_INFO("Program update: " + std::to_string(i));

		//delay
		for (int j = 0; j < 1000000; j++) { if (i == j) { j = i; } }
	}

	BLOCKY_ENGINE_ERROR("An error occurred.");
	BLOCKY_ENGINE_WARNING("An warning occurred.");

	TestClass::DoTestAndLog();
}
