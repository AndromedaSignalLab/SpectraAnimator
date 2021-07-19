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
//typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;
//else
//typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
typedef std::chrono::duration<double> Duration;
typedef std::chrono::high_resolution_clock Clock;

typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

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


enum class MovementType {
	Stationary,
	Raising,
	Falling
};

/**
 * Velocity unit is 1 bar height per second.
 * For example, 0.5 means bar goes to its half height from zero in a second.
 * -0.5 means velocity has opposite direction (from up to bottom direction)
 */
struct MovementProperties {
	double acceleration;
	double initialVelocity;
};

template<typename T>
struct Movement {
	MovementType movementType = MovementType::Stationary;
	T velocityWithAcceleration = 0; //ignored for constant velocity
	T displacement = 0;
	T targetDisplacement = 0;
};
