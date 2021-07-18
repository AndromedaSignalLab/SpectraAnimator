/*
 * PhysicsUtil.cpp
 *
 *  Created on: Jul 17, 2021
 *      Author: Volkan Orhan
 */

#include "PhysicsUtil.hpp"

namespace PhysicsUtil {
	double calculateVelocity(double lastVelocity, double acceleration, double timePassed) {
		return lastVelocity + acceleration * timePassed;
	}

	double calculateDisplacement(double velocity, double timePassed) {
		return velocity * timePassed;
	}

	double calculateDisplacement(double lastVelocity, double acceleration, double timePassed) {
		return lastVelocity*timePassed + 0.5 * acceleration * timePassed * timePassed;
	}
}
