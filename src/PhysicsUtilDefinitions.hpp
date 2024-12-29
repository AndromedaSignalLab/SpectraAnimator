/*
Physical calculations utilization set
Copyright (C) Jul 17, 2021 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
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
    return lastVelocity*timePassed + T(0.5) * acceleration * timePassed * timePassed;
}

template<typename T>
T PhysicsUtil<T>::calculateInitialVelocity(T distance, T acceleration) {
	//V₀ = √(2Xa)
	return std::sqrt(std::abs(distance*acceleration*2.0));
}
