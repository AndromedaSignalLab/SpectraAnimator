// Simple Hello World program
#include <iostream>

#include "SpectrumAnalyzerAnimator"
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
	animator.setFallingAnimationType(AnimationType::ConstantVelocity);
	animator.setRaisingAnimationType(AnimationType::ConstantVelocity);

	MovementProperties r, f;
	r.acceleration = 0;
	r.velocity = 0.1;

	f.acceleration = 0;
	f.velocity = -0.1;

	animator.setFallingMovementProperties(f);
	animator.setRaisingMovementProperties(r);
	animator.start();
	double values[] = {1, 0.5, 0.3, 0.2, 0.7};
	printArray(5, values);
	animator.setValues(values);

	int i=0;
	double returnValues[5];
	while(true) {
		std::cout<<i<<std::endl;
		i++;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));

		animator.getValues(returnValues);
		printArray(5, returnValues);
		if(!(returnValues[0] || returnValues[1] || returnValues[2] || returnValues[3] || returnValues[4]))
			break;
	}


	return 0;
}
