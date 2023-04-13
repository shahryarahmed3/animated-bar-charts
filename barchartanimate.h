// barchartanimate.h
// ****************************************************************************
//
// Project: Animated Bar Chart
// Author: Shahryar Ahmed
//
// ****************************************************************************
//
// The BarChartAnimate class uses BarChart class to save an instance of a
// barchart into frames. This class has animation functionality to produce a
// visual of animation.
//
// ****************************************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used by graders, do not remove
#include "barchart.h"
  
using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    string title;
    string xlabel;
    string source;

 public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
        barcharts = new BarChart[4];
        size = 0;
        capacity = 4;
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        
        if(barcharts != nullptr){
            delete[] barcharts;
        }
        
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
        
        string year;
        string name;
        string country;
        int value;
        string s;
        string category;
        
        if(!file.is_open()){
            cout << "File is not open!" << endl;
            exit(1);
        }
        
        string blank;
        string line;
        string num;
        
        int limit = 0;
        
        getline(file, line);
        getline(file, line);
        
        if(isdigit(line[0])){
            limit = stoi(line); //how many bars are in one frame
        }
        
        BarChart a(limit); //allocating memory for num of bars in one frame
        
        int j = 0;
        
        for(int i = 0; i < limit; i++){

            getline(file, line);

            stringstream ss(line);
            
            getline(ss, year, ',');
            a.setFrame(year);
            
            getline(ss, name, ',');
            
            getline(ss, country, ',');
            
            getline(ss, s, ',');
            value = stoi(s);
            
            getline(ss, category, '\n');

            a.addBar(name, value, category);
            
            if(!colorMap.count(category)){
                colorMap[category] =  COLORS[j%7]; // i modulo 7 "wraps" the color around
                j++;
            }
            
        }

        if (size == capacity){
            
            int newCapacity = capacity *2;
            BarChart* newbarcharts = new BarChart[newCapacity];
        
        
            for (int i = 0; i < size; ++i){
                newbarcharts[i] = barcharts[i];
            }
            
            delete[] barcharts;
            barcharts = newbarcharts;
            capacity = newCapacity;
        }

        if(limit != 0){ 
            barcharts[size] = a;
            size++;
        }
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
        
        if(endIter == -1){
            endIter = size;
        }

        for (int i = 0; i < endIter; i++){
            usleep(3 * microsecond);
            output << CLEARCONSOLE;
            output << RESET << title << endl;
            output << RESET << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << RESET << xlabel << endl;
            output << RESET << "Frame: " << barcharts[i].getFrame() << endl;
        }

	}
    
    // ***************************************************************************
    // CREATIVE COMPONENT: animate (overloaded function):
    // This function plays each frame in the barcharts array. The function is
    // adapted from the original animate function that is required for this
    // project. Additionally, this function has the ability to modify the playback
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
    void animate(ostream &output, int top, int endIter, int playBackSpeed) {
        unsigned int microsecond = 50000;
        
        if(endIter == -1){
            endIter = size;
        }

        for (int i = 0; i < endIter; i++){
            usleep(playBackSpeed * microsecond);
            output << CLEARCONSOLE;
            output << RESET << title << endl;
            output << RESET << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << RESET << xlabel << endl;
            output << RESET << "Frame: " << barcharts[i].getFrame() << endl;
        }

    }

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize(){
        return size;
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i){
        //BarChart bc;
        
        if (i < 0 || i >= size){
            throw out_of_range("BarChartAnimate: i out of bounds");
            return barcharts[i];
        }
        return barcharts[i];
    }


};
