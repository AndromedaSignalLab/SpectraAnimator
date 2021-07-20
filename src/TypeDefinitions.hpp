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

enum class MotionType {
	Instant,//Jumpy
	ConstantAcceleration,
	ConstantVelocity
};

enum class PeakIndicatorType {
	NoPeakIndicator,
	Vanishing,
	WithMotion
};

enum class MotionRotation {
	Stationary,
	Raising,
	Falling
};

/**
 * Velocity unit is 1 bar height per second.
 * For example, 0.5 means bar goes to its half height from zero in a second.
 * -0.5 means velocity has opposite direction (from up to bottom direction)
 */
struct MotionProperties {
	MotionType motionType;
	double acceleration = 0.0;
	double initialVelocity = 0.0;
};

template<typename T>
struct Motion {
	MotionRotation motionRotation = MotionRotation::Stationary;
	T velocityWithAcceleration = 0; //ignored for constant velocity
	T displacement = 0;
	T targetDisplacement = 0;
};
