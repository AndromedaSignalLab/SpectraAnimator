/*
 * SpectrumAnalyzerAnimatorDefinitions.hpp
 *
 *  Created on: Jul 17, 2021
 *      Author: Volkan Orhan
 */

#pragma once

#include "SpectrumAnalyzerAnimator.hpp"
#include "PhysicsUtil.hpp"

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
AnimationType SpectrumAnalyzerAnimator<T>::getFallingAnimationType() const {
	return fallingAnimationType;
}

template<typename T>
void SpectrumAnalyzerAnimator<T>::setFallingAnimationType(AnimationType fallingAnimationType) {
	this->fallingAnimationType = fallingAnimationType;
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
AnimationType SpectrumAnalyzerAnimator<T>::getRaisingAnimationType() const {
	return raisingAnimationType;
}

template<typename T>
inline SpectrumAnalyzerAnimator<T>::SpectrumAnalyzerAnimator(size_t bandAmount,
		T minValue, T maxValue) {
	this->bandAmount = bandAmount;
	this->minValue = minValue;
	this->maxValue = maxValue;
	setFallingAnimationType(AnimationType::ConstantVelocity);
	setRaisingAnimationType(AnimationType::ConstantVelocity);
	//this->timePoint = 0;
	this->running = false;
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::setBandAmount(size_t bandAmount) {
	bool wasRunning = running;
	if(wasRunning) {
		stop();
	}
	delete[] movements;
	movements = new Movement<T>[bandAmount];
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
		Movement<T> &movement = movements[i];
		T valueToBeSet = values[i];

		if(valueToBeSet > movement.targetDisplacement) { //higher value to be set
			movement.targetDisplacement = valueToBeSet;
		}
	}
	valueSettingMutex.unlock();
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::getValues(T values[]) {
	valueSettingMutex.lock();
	updateMovements();
	for(size_t i=0; i<bandAmount; i++)
		values[i] = movements[i].displacement;
	valueSettingMutex.unlock();
}

template<typename T>
void SpectrumAnalyzerAnimator<T>::setRaisingAnimationType(AnimationType raisingAnimationType) {
	this->raisingAnimationType = raisingAnimationType;
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::updateTimePoints() {
	previousTimePoint = currentTimePoint;
	currentTimePoint = Clock::now();
	Duration duration = currentTimePoint - previousTimePoint;
	lastDuration = duration.count();
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::startFalling(Movement<T> &movement) {
	movement.targetDisplacement = 0;
	switch(fallingAnimationType) {
		case AnimationType::ConstantVelocity:
			movement.velocity = fallingMovementProperties.velocity;
			break;
		case AnimationType::ConstantAcceleration:
			movement.velocity = 0;
			break;
		case AnimationType::NoAnimation:
			break;
	}
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::updateMovements() {
	updateTimePoints();
	for(int i=0; i<bandAmount; i++) {
		Movement<T> &movement = movements[i];
		if(movement.velocity > 0) {//Raising
			switch(raisingAnimationType) {
				case AnimationType::ConstantVelocity: {
					movement.displacement = PhysicsUtil::calculateDisplacementDelta(raisingMovementProperties.velocity, lastDuration);
					if(movement.displacement >= movement.targetDisplacement) {
						movement.displacement = movement.targetDisplacement;
						startFalling(movement);
					}
					break;
				}
				case AnimationType::ConstantAcceleration: {
					double previousVelocity = movement.velocity;
					movement.velocity = PhysicsUtil::calculateVelocity(movement.velocity, raisingMovementProperties.acceleration, lastDuration);
					movement.displacement = PhysicsUtil::calculateDisplacementDelta(previousVelocity, raisingMovementProperties.acceleration, lastDuration);
					if(movement.displacement >= movement.targetDisplacement) {
						movement.displacement = movement.targetDisplacement;
						startFalling(movement);
					}
					break;
				}
				case AnimationType::NoAnimation:
					//Do nothing
					break;
			}
		}
		else if(movement.velocity < 0){//Falling
			switch(fallingAnimationType) {
				case AnimationType::ConstantVelocity: {
					movement.displacement += PhysicsUtil::calculateDisplacementDelta(fallingMovementProperties.velocity, lastDuration);
					if(movement.displacement >= movement.targetDisplacement) {
						movement.displacement = movement.targetDisplacement;
						startFalling(movement);
					}
					break;
				}
				case AnimationType::ConstantAcceleration: {
					double previousVelocity = movement.velocity;
					movement.velocity = PhysicsUtil::calculateVelocity(movement.velocity, raisingMovementProperties.acceleration, lastDuration);
					movement.displacement += PhysicsUtil::calculateDisplacementDelta(previousVelocity, raisingMovementProperties.acceleration, lastDuration);
					if(movement.displacement <= movement.targetDisplacement) {
						movement.displacement = movement.targetDisplacement;
					}
					break;
				}
				case AnimationType::NoAnimation:
					//Do nothing
					break;
			}
		}
		else {//Movement Finished
			//Do nothing
		}
	}
}
