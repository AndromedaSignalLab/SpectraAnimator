/*
 * TypeDefinitions.hpp
 *
 *  Created on: Jul 15, 2021
 *      Author: volkan
 */

#pragma once

#include <cstddef>
#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
typedef std::chrono::duration<double> Duration;

enum class AnimationType {
	NoAnimation,
	ConstantAcceleration,
	ConstantVelocity
};

enum class PeakIndicatorType {
	NoPeakIndicator,
	Vanishing,
	WithAnimation
};

/*
enum class MovementType {
	Falling,
	Raising
};*/

struct MovementProperties {
	double acceleration;
	double velocity;
};

template<typename T>
struct Movement {
	//MovementType movementType;
	double velocity;
	T displacement;
};
