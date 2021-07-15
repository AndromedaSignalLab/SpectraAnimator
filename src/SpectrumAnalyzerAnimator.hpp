/*
 * SpectrumAnalyzerAnimator.hpp
 *
 *  Created on: Jul 15, 2021
 *      Author: Volkan Orhan
 */
#pragma once

#include "TypeDefinitions.hpp"

template<typename T> class SpectrumAnalyzerAnimator {
public:
	SpectrumAnalyzerAnimator(size_t bandAmount, T minValue, T maxValue);
	void setBandAmount(size_t bandAmount);
	size_t getBandAmount() const;

	void start();
	void stop();
	void setValues(T values[]);
	void getValues(T values[]);

	T getMinValue() const;
	T getMaxValue() const;

	void setMinValue(T minValue);
	void setMaxValue(T maxValue);

	PeakIndicatorType getPeakIndicatorType() const;
	void setPeakIndicatorType(PeakIndicatorType peakIndicatorType);

	AnimationType getFallingAnimationType() const;
	AnimationType getRaisingAnimationType() const;

	void setFallingAnimationType(AnimationType fallingAnimationType);
	void setRaisingAnimationType(AnimationType raisingAnimationType);

private:
	size_t bandAmount;
	AnimationType raisingAnimationType, fallingAnimationType;
	MovementProperties raisingMovementProperties, fallingMovementProperties;
	PeakIndicatorType peakIndicatorType;
	TimePoint timePoint;
	T minValue, maxValue;
	Movement<T> * movements;
};

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
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::setBandAmount(size_t bandAmount) {
}

template<typename T>
inline size_t SpectrumAnalyzerAnimator<T>::getBandAmount() const {
	return this->bandAmount;
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::start() {
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::stop() {
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::setValues(T values[]) {
	for(size_t i=0; i<bandAmount; i++) {
		if(values[i] > movements[i].displacement) { //higher value is set
			movements[i].velocity = raisingMovementProperties.velocity;
		}
	}
}

template<typename T>
inline void SpectrumAnalyzerAnimator<T>::getValues(T values[]) {
}

template<typename T>
void SpectrumAnalyzerAnimator<T>::setRaisingAnimationType(AnimationType raisingAnimationType) {
	this->raisingAnimationType = raisingAnimationType;
}
