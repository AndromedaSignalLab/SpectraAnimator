// Simple Hello World program
#include <iostream>

#include "SpectrumAnalyzerAnimator"

using namespace std;

int main(int argc, char **argv) {
	SpectrumAnalyzerAnimator<double> animator(1,0,100);
	animator.start();
	cout<<"Hello World";
	return 0;
}
