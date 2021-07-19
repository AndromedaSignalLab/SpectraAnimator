/*
 * PhysicsUtil.hpp
 *
 *  Created on: Jul 17, 2021
 *      Author: Volkan Orhan
 */

#pragma once
#include <cstddef>

namespace PhysicsUtil {
	double calculateVelocity(double lastVelocity, double acceleration, double timePassed);
	double calculateDisplacementDelta(double velocity, double timePassed);
	double calculateDisplacementDelta(double lastVelocity, double acceleration, double timePassed);
};
