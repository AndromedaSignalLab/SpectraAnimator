/*
 * PhysicsUtil.hpp
 *
 *  Created on: Jul 17, 2021
 *      Author: Volkan Orhan
 */

#pragma once
#include <cstddef>

template<typename T>
class PhysicsUtil {
public:
	static T calculateVelocity(T lastVelocity, T acceleration, T timePassed);
	static T calculateDisplacementDelta(T velocity, T timePassed);
	static T calculateDisplacementDelta(T lastVelocity, T acceleration, T timePassed);
	static T calculateInitialVelocity(T distance, T acceleration);
};
