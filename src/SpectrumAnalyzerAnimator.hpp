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

	void setFallingMotionProperties(MotionProperties fallingMotionProperties);
	void setRaisingMotionProperties(MotionProperties raisingMotionProperties);

private:
	void updateMotions();
	void updateTimePoints();
	void startFalling(Motion<T> &movement);
	void startMovement(Motion<T> &movement, T targetDisplacement);
	size_t bandAmount;
	MotionProperties raisingMotionProperties, fallingMotionProperties;
	PeakIndicatorType peakIndicatorType;
	TimePoint previousTimePoint, currentTimePoint;
	double lastDuration;
	T minValue, maxValue;
	Motion<T> * motions;
	bool running;
	std::mutex valueSettingMutex;
};
