/*
 * SpectrumAnalyzerAnimator.hpp
 *
 *  Created on: Jul 15, 2021
 *      Author: Volkan Orhan
 */
#pragma once

#include "TypeDefinitions.hpp"
#include <mutex>

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

	void setFallingMovementProperties(MovementProperties fallingMovementProperties);
	void setRaisingMovementProperties(MovementProperties raisingMovementProperties);

private:
	void updateMovements();
	void updateTimePoints();
	void startFalling(Movement<T> &movement);
	size_t bandAmount;
	AnimationType raisingAnimationType, fallingAnimationType;
	MovementProperties raisingMovementProperties, fallingMovementProperties;
	PeakIndicatorType peakIndicatorType;
	TimePoint previousTimePoint, currentTimePoint;
	double lastDuration;
	T minValue, maxValue;
	Movement<T> * movements;
	bool running;
	std::mutex valueSettingMutex;
};
