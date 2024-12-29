/*
Type Definitions of Spectrum Analyzer Animator
Copyright (C) Jul 15, 2021 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
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
	Stationary = 0,
	Raising = 1,
	Falling = -1
};

/**
 * Velocity unit is 1 bar height per second.
 * For example, 0.5 means bar goes to its half height from zero in a second.
 * -0.5 means velocity has opposite direction (from up to bottom direction)
 */
template<typename T>
struct MotionProperties {
	MotionType motionType;
    T acceleration = 0.0;
    T initialVelocity = 0.0;
};

template<typename T>
struct Motion {
	MotionRotation motionRotation = MotionRotation::Stationary;
    T velocityWithAcceleration = T(0); //ignored for constant velocity
    T displacement = T(0);
    T targetDisplacement = T(0);
};
