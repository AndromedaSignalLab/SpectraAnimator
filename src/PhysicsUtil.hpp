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
	double calculateDisplacement(double velocity, double timePassed);
	double calculateDisplacement(double lastVelocity, double acceleration, double timePassed);
};
