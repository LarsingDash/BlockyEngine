#include "./engine/logging/Logging.hpp"


int main() {
	Logging logger("logfile.txt"); // Create logger instance

	logger.Log(DEBUG, "Debugging information.");

	// Example usage of the logger
	for (int i = 0; i < 5; i++) {
		logger.Log(INFO, "Program update: " + std::to_string(i));

		//delay
		for (int j = 0; j < 1000000; j++) { if (i == j) { j = i; } }
	}

	logger.Log(ERR, "An error occurred.");

	return 0;
}
