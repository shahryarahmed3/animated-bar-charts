// Bar Chart Animation
//
// This application uses BarChartAnimate (which uses BarChart, which uses Bar)
// to produce an animated bar chart.
//
// Once your three class/abstraction files are completed and tested, run with
// this application to see your final creation.
//
// TO DO: Nothing for the standard application, just compile and run! However,
// before submitting you need to add your creative component.
//
// Adam Koehler
// U. of Illinois, Chicago
// Fall 2022
//
// Original iteration of program developed by:
// Shanon Reckinger
// U. of Illinois, Chicago

// ****************************************************************************
// 
// Project: Animated Bar Chart
// Author: Shahryar Ahmed
//
// ****************************************************************************
//
// CREATIVE COMPONENT: animate (overloaded function):
// This function plays each frame in the barcharts array. The function is
// adapted from the original animate function that is required for this
// project. Additionally, the function has the ability to modify the playback
// speed based on user input. The usefulness of this component is to help
// slow down or speed up animations for small file vs. large file respectively.
// It could also be useful to serve the purposes of user preference of speed.
// The functionality of playback speed is implemented through an overloaded
// function animate in which it takes in an extra parameter of integer,
// playBackSpeed. This playBackSpeed variable will be determined by the user
// input when the function is called. The playBackSpeed is a multiplying
// factor with the microsecond. The larger the playBackSpeed factor is
// the slower the animation will play. The smaller the playBackSpeed factor
// is the faster the animation will play.
//
// HOW TO RUN:
// 1. Set playBackSpeed from (1 to 10) 1 is slowest speed, 10 is highest speed
// 2. Uncomment the line: bca.animate(cout, 12, -1, playBackSpeed); (see below)
//
// ****************************************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;


int main() {

	string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);

	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}

	bca.animate(cout, 12, -1);

//******************************[CREATIVE COMPONENT]******************************

    // 1. Set playBackSpeed from (1 to 10) 1 is slowest speed, 10 is highest speed
    int playBackSpeed = 3; //3 is default speed

    // 2. Uncomment the line below:
    // bca.animate(cout, 12, -1, playBackSpeed);

//******************************[CREATIVE COMPONENT]******************************

    return 0;
}
