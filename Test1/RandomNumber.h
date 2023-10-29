#include <iostream>

inline float RandomNumberBetween0and1() {
	return (float)rand() / RAND_MAX;
}

inline float AddTextureNumber(float number, float multiplier) {
	return (number - 0.5) * multiplier;
}

inline float NumberBettween0and1(float number) {
	if (number > 1) {
		return 1;
	}
	else if (number < 0) {
		return 0;
	}
	else {
		return number;
	}
}
