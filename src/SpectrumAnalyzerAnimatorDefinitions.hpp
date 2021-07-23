/*
 * SpectrumAnalyzerAnimatorDefinitions.hpp
 *
 *  Created on: Jul 17, 2021
 *      Author: Volkan Orhan
 */

#pragma once

#include "SpectrumAnalyzerAnimator.hpp"
#include "PhysicsUtil"

template<typename T>
T SpectrumAnalyzerAnimator<T>::getMaxValue() const {
	return maxValue;
}

template<typename T>
void SpectrumAnalyzerAnimator<T>::setMaxValue(T maxValue) {
	this->maxValue = maxValue;
}

template<typename T>
T SpectrumAnalyzerAnimator<T>::getMinValue() const {
	return minValue;
}

template<typename T>
void SpectrumAnalyzerAnimator<T>::setMinValue(T minValue) {
	this->minValue = minValue;
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::setFallingMotionProperties(
		MotionProperties fallingMotionProperties) {
	this->fallingMotionProperties = fallingMotionProperties;
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::setRaisingMotionProperties(
		MotionProperties raisingMotionProperties) {
	this->raisingMotionProperties = raisingMotionProperties;
}

template<typename T>
PeakIndicatorType SpectrumAnalyzerAnimator<T>::getPeakIndicatorType() const {
	return peakIndicatorType;
}

template<typename T>
void SpectrumAnalyzerAnimator<T>::setPeakIndicatorType(PeakIndicatorType peakIndicatorType) {
	this->peakIndicatorType = peakIndicatorType;
}

template<typename T>
inline SpectrumAnalyzerAnimator<T>::SpectrumAnalyzerAnimator(size_t bandAmount,
		T minValue, T maxValue) {
	this->bandAmount = bandAmount;
	this->motions = new Motion<T>[bandAmount];
	this->minValue = minValue;
	this->maxValue = maxValue;
	fallingMotionProperties.motionType = MotionType::ConstantVelocity;
	raisingMotionProperties.motionType = MotionType::ConstantVelocity;
	this->lastDuration = 0.0;
	this->peakIndicatorType = PeakIndicatorType::NoPeakIndicator;
	this->running = false;
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::setBandAmount(size_t bandAmount) {
	bool wasRunning = running;
	if(wasRunning) {
		stop();
	}
	delete[] motions;
	motions = new Motion<T>[bandAmount];
	this->bandAmount = bandAmount;
	if(wasRunning){
		start();
	}
}

template<typename T>
inline size_t SpectrumAnalyzerAnimator<T>::getBandAmount() const {
	return this->bandAmount;
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::start() {
	if(!running) {
		updateTimePoints();
		running = true;
	}
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::stop() {
	if(running) {
		running = false;
	}
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::setValues(T values[]) {
	valueSettingMutex.lock();

	for(size_t i=0; i<bandAmount; i++) {
		Motion<T> &motion = motions[i];
		T &valueToBeSet = values[i];

		/*
		 * Cases:
		 * 1 - Bar is raising to a higher or equal value
		 *   -> Do nothing
		 * 2 - Bar is raising to a lower value
		 *   -> Start a new movement from its current value
		 *      Set target displacement to the new displacement value
		 *      If movement has constant acceleration, set velocity to new calculated value using calculateInitialVelocity method
		 *      If movement has constant velocity, do nothing
		 * 3 - Bar is falling and currently has higher or equal value
		 *   -> Do nothing
		 * 4 - Bar is falling and currently has a lower value
		 *   -> Start a new movement from its current value
		 *      Set target displacement to the new displacement value
		 *      If movement has constant acceleration, set velocity to 0
		 *      If movement has constant velocity, do nothing
		 * 5 - Bar is stationary
		 *   -> Start a new movement from position 0
		 */

		switch(motion.motionRotation) {
			case MotionRotation::Raising: {
				if(motion.targetDisplacement >= valueToBeSet) // Case 1
					continue;
				// Case 2:
				startMotion(motion, valueToBeSet);
				break;
			}
			case MotionRotation::Falling: {
				if(motion.displacement >= valueToBeSet) // Case 3
					continue;
				// Case 4
				startMotion(motion, valueToBeSet);
				break;
			}
			case MotionRotation::Stationary: {
				// Case 5
				motion.displacement = minValue;
				startMotion(motion, valueToBeSet);
				break;
			}
		}

		if(motion.motionRotation == MotionRotation::Raising) { //Case 1 and 2
			// Case 1:
			if(motion.targetDisplacement >= valueToBeSet)
				continue;

			// Case 2:
			if(motion.targetDisplacement < valueToBeSet){

			}
		}


		if(valueToBeSet > motion.targetDisplacement) { //higher value to be set
			motion.motionRotation = MotionRotation::Raising;
			motion.targetDisplacement = valueToBeSet;
		}
	}
	valueSettingMutex.unlock();
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::getValues(T values[]) {
	valueSettingMutex.lock();
	updateMotions();
	for(size_t i=0; i<bandAmount; i++)
		values[i] = motions[i].displacement;
	valueSettingMutex.unlock();
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::updateTimePoints() {
	previousTimePoint = currentTimePoint;
	currentTimePoint = Clock::now();
	Duration duration = currentTimePoint - previousTimePoint;
	lastDuration = duration.count();
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::startFalling(Motion<T> &motion) {
	motion.targetDisplacement = minValue;
	motion.motionRotation = MotionRotation::Falling;
	switch(fallingMotionProperties.motionType) {
		case MotionType::ConstantVelocity:
			break;
		case MotionType::ConstantAcceleration:
			motion.velocityWithAcceleration = 0;
			break;
		case MotionType::Instant:
			break;
	}
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::startMotion(Motion<T> &motion, T targetDisplacement) {
	motion.targetDisplacement = targetDisplacement;
	motion.motionRotation = MotionRotation::Raising;
	T totalDistance = motion.targetDisplacement - motion.displacement;
	switch(raisingMotionProperties.motionType) {
		case MotionType::ConstantVelocity:
			break;
		case MotionType::ConstantAcceleration:
			motion.velocityWithAcceleration = PhysicsUtil<double>::calculateInitialVelocity(totalDistance, raisingMotionProperties.acceleration);
			break;
		case MotionType::Instant:
			break;
	}
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::updateMotions() {
	updateTimePoints();
	for(size_t i=0; i<bandAmount; i++) {
		Motion<T> &motion = motions[i];
		if(motion.motionRotation == MotionRotation::Raising) {
			switch(raisingMotionProperties.motionType) {
				case MotionType::ConstantVelocity: {
					motion.displacement += PhysicsUtil<double>::calculateDistance(raisingMotionProperties.initialVelocity, lastDuration);
					if(motion.displacement >= motion.targetDisplacement) {
						motion.displacement = motion.targetDisplacement;
						startFalling(motion);
					}
					break;
				}
				case MotionType::ConstantAcceleration: {
					double previousVelocity = motion.velocityWithAcceleration;
					motion.velocityWithAcceleration = PhysicsUtil<double>::calculateVelocity(motion.velocityWithAcceleration, raisingMotionProperties.acceleration, lastDuration);
					motion.displacement += PhysicsUtil<double>::calculateDistance(previousVelocity, raisingMotionProperties.acceleration, lastDuration);
					if(motion.displacement >= motion.targetDisplacement) {
						motion.displacement = motion.targetDisplacement;
						startFalling(motion);
					}
					break;
				}
				case MotionType::Instant:
					//Do nothing
					break;
			}
		}
		else if(motion.motionRotation == MotionRotation::Falling) {
			switch(fallingMotionProperties.motionType) {
				case MotionType::ConstantVelocity: {
					motion.displacement += PhysicsUtil<double>::calculateDistance(fallingMotionProperties.initialVelocity, lastDuration);
					if(motion.displacement <= motion.targetDisplacement) {
						motion.displacement = motion.targetDisplacement;
						motion.motionRotation = MotionRotation::Stationary;

					}
					break;
				}
				case MotionType::ConstantAcceleration: {
					double previousVelocity = motion.velocityWithAcceleration;
					motion.velocityWithAcceleration = PhysicsUtil<double>::calculateVelocity(motion.velocityWithAcceleration, fallingMotionProperties.acceleration, lastDuration);
					motion.displacement += PhysicsUtil<double>::calculateDistance(previousVelocity, fallingMotionProperties.acceleration, lastDuration);
					if(motion.displacement <= motion.targetDisplacement) {
						motion.displacement = motion.targetDisplacement;
						motion.motionRotation = MotionRotation::Stationary;
					}
					break;
				}
				case MotionType::Instant:
					//Do nothing
					break;
			}
		}
		else { //Stationary
			//Do nothing
		}
	}
}
