/*
 * PhysicsUtil.cpp
 *
 *  Created on: Jul 17, 2021
 *      Author: Volkan Orhan
 */

#include "PhysicsUtil.hpp"
#include <cmath>

template<typename T>
T PhysicsUtil<T>::calculateVelocity(T lastVelocity, T acceleration, T timePassed) {
	return lastVelocity + acceleration * timePassed;
}

template<typename T>
T PhysicsUtil<T>::calculateDistance(T velocity, T timePassed) {
	return velocity * timePassed;
}

template<typename T>
T PhysicsUtil<T>::calculateDistance(T lastVelocity, T acceleration, T timePassed) {
	return lastVelocity*timePassed + 0.5 * acceleration * timePassed * timePassed;
}

template<typename T>
T PhysicsUtil<T>::calculateInitialVelocity(T distance, T acceleration) {
	//V₀ = √(2Xa)
	return std::sqrt(std::abs(distance*acceleration*2.0));
}
