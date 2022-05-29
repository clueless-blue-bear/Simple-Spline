// Simple Spline implementation
// Made By: Bartosz Mazur
// Github: clueless-blue-bear
// Free to use and modify
#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <exception>
#include <fstream>

using namespace std;
// Function being interpolated
template<typename E> E hyperbole (E x) {
    return 1.0/(1 + x*x);
}

// Function below takes a sorted STL container Iterators
// Returns iterator of element lower and closest
// To the inputed value
template<typename Iter, typename E>
Iter closest_lower (Iter beg, Iter End, E val) {
    Iter flag = beg;
    if (val < *beg) return beg;
    ++beg;

    while (beg != End) {
        if (*beg >= val) {
            //cout << "flag value: " << *flag << endl;
            return flag;
        }
        ++beg;
        ++flag;
    }
    return End;
}
// Function below takes a sorted STL container Iterators
// Returns iterator to the first element bigger to the value
// If no element is bigger returns end of the Search Range
template<typename Iter, typename E>
Iter closest_bigger (Iter beg, Iter End, E val) {
    if (val > *(End-1)) return End;
    while (beg != End) {
        if (*beg > val) {
            return beg;
        }
        ++beg;
    }
    if (*beg == val) return beg;
    return End;
}

// Class that takes two vectors: points and values, on which based are the results
// It has a function to output results to a file
// Also it can print out the results.

class Simple_Spline {
    vector<double> pts;
    vector<double> vals;
public:
    Simple_Spline(vector<double> p, vector<double> v)
        : pts{p}, vals{v} {};
    
    void print_results(const double lb, const double rb, const double step);
    void output_results (const double lb, const double rb, const double step, string filename);

};
// Takes left boundary, right boundary, step and a filename
// Interpolates the function based on points and values in the boundaries
void Simple_Spline::output_results(const double lb, const double rb, const double step, string filename)
{
    ofstream ofs {filename};
    if (!ofs) throw runtime_error("Couldn't open the file");

    double tmp_val {0};
    vector<double>::iterator bigger;
    vector<double>::iterator lower;

    for (double x = lb; x <= rb; x += step) {
        ofs << x;
        ofs << ": ";

        bigger = closest_bigger(pts.begin(),pts.end(),x);
        lower = closest_lower(pts.begin(),pts.end(),x);
        // Calculating the interpolation value at a point x using formula
        // Bigger and lower are Iterators pointing to the values of a points between which x resides
        tmp_val = ((x - *bigger)/(*lower - *bigger))*hyperbole(*lower);
        tmp_val += ((x - *lower)/(*bigger - *lower))*hyperbole(*bigger);

        ofs << tmp_val;
        ofs << '\n';
    }
}

int main()
{
    try {
        vector<double> Points;
        vector<double> Values;

        for (double d = -5.0; d <= 5.0; d += 1.0) {
            Points.push_back(d);
            Values.push_back(hyperbole(d));
            //cout << "Point: " << d << ", value: " << hyperbole(d) << endl;
        }
        Simple_Spline SS {Points,Values};
        SS.output_results(-5.0,5.0,0.1,"output.txt"); 
    }

    catch (exception& e) {
        cerr << "Error occured: " << e.what() << endl;
        return 1;
    }

    catch(...) {
        cerr << "Unknown exception! \n";
        return 2;
    }
}
