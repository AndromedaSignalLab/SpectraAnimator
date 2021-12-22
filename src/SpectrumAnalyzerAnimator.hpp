/*
Spectrum Analyzer Animator
Copyright (C) Jul 15, 2021 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
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
	void startFalling(Motion<T> &motion);
	void startMotion(Motion<T> &motion, T targetDisplacement);
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
