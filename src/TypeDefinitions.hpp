/*
 * TypeDefinitions.hpp
 *
 *  Created on: Jul 15, 2021
 *      Author: Volkan Orhan
 */

#pragma once

#include <cstddef>
#include <chrono>

//if mac
typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;
//else
//typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
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

/**
 * Velocity unit is 1 bar height per second.
 * For example, 0.5 means bar goes to its half height from zero in a second.
 * -0.5 means velocity has opposite direction (from up to bottom direction)
 */
struct MovementProperties {
	double acceleration;
	double velocity;
};

template<typename T>
struct Movement {
	//MovementType movementType;
	T velocity;
	T displacement;
	T targetDisplacement;
};
