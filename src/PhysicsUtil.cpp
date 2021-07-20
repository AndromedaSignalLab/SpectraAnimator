/*
 * PhysicsUtil.cpp
 *
 *  Created on: Jul 17, 2021
 *      Author: Volkan Orhan
 */

#include "PhysicsUtil.hpp"
#include <cmath>

namespace PhysicsUtil {
	double calculateVelocity(double lastVelocity, double acceleration, double timePassed) {
		return lastVelocity + acceleration * timePassed;
	}

	double calculateDisplacementDelta(double velocity, double timePassed) {
		return velocity * timePassed;
	}

	double calculateDisplacementDelta(double lastVelocity, double acceleration, double timePassed) {
		return lastVelocity*timePassed + 0.5 * acceleration * timePassed * timePassed;
	}

	double calculateInitialVelocity(double totalDisplacementDelta, double acceleration) {
		//V₀ = √(2Xa)
		return std::sqrt(totalDisplacementDelta*acceleration*2.0);
	}
}
