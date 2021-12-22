/*
Test file for Spectrum Analyzer Animator
Better tests using a unit test library will be designed.
Copyright (C) Jul 15, 2021 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <iostream>

#include "../src/SpectrumAnalyzerAnimator"
#include <thread>
#include <chrono>

using namespace std;

void printArray(int len, double values[]) {
	std::cout<<"[";
	for(int i=0; i<len-1; i++) {
		std::cout<<values[i]<<", ";
	}
	std::cout<<values[len-1]<<"]"<<std::endl;
}

int main(int argc, char **argv) {
	SpectrumAnalyzerAnimator<double> animator(5,0,1);

	MotionProperties r, f;
	r.acceleration = 0;
	r.initialVelocity = 0.1;
	r.motionType = MotionType::ConstantVelocity;

	f.acceleration = -0.3;
	f.motionType = MotionType::ConstantAcceleration;
	//f.initialVelocity = -0.3;

	animator.setFallingMotionProperties(f);
	animator.setRaisingMotionProperties(r);
	animator.start();
	double values[] = {1, 0.5, 0.3, 0.2, 0.7};
	printArray(5, values);
	animator.setValues(values);

	int i=0;
	double returnValues[5];
	while(true) {
		//std::cout<<i<<std::endl;
		i++;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		animator.getValues(returnValues);
		printArray(5, returnValues);
		if(returnValues[0] == animator.getMinValue() && returnValues[1] == animator.getMinValue() &&
		   returnValues[2] == animator.getMinValue() && returnValues[3] == animator.getMinValue() &&
		   returnValues[4] == animator.getMinValue())
			break;
	}


	return 0;
}
