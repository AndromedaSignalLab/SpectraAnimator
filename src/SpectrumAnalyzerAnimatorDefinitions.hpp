/*
 * SpectrumAnalyzerAnimatorDefinitions.hpp
 *
 *  Created on: Jul 17, 2021
 *      Author: Volkan Orhan
 */

#pragma once

#include "SpectrumAnalyzerAnimator.hpp"

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
		this->timePoint = std::chrono::system_clock::now();
		running = true;
	}
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::stop() {
	if(running) {
		this->timePoint = 0;
		running = false;
	}
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::setValues(T values[]) {
	valueSettingMutex.lock();
	for(size_t i=0; i<bandAmount; i++) {
		if(values[i] > movements[i].displacement) { //higher value is set
			movements[i].velocity = raisingMovementProperties.velocity;
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
inline void SpectrumAnalyzerAnimator<T>::updateMovements() {

}
