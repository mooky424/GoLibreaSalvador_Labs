#include <cstdlib>
#include <iostream>

using namespace std;

struct Point3D {
    int x, y, z;
};

int calcDistance(Point3D *a, Point3D *b) {
    // M( p​1​, p​2​ ) = | x​1​ - ­ x​2​ | +
    // | y​1​ - ­y​2​ | + | z​1​ -­ z​2​ |
    return abs((*a).x - (*b).x) + abs((*a).y - (*b).y) + abs((*a).z - (*b).z);
}

int main() {
    int test_cases, points;

    // no. of test cases from input
    cin >> test_cases;

    // if invalid no. of test cases end program
    if (test_cases < 0) {
        return -1;
    }

    // while test cases > 0
    while (test_cases--) {

        // get no. of points
        cin >> points;

        // if less than 2 points end program 
        if (points < 2) {
            return -2;
        }

        // init Point3D array
        Point3D p[points];

        // for no. of points get coordinates
        for (int i = 0; i < points; i++) {
            cin >> p[i].x >> p[i].y >> p[i].z;
        }

        // for each pair of points calculate Manhattan Distance
        for (int i = 0; i < points - 1; i++) {
            cout << calcDistance(&p[i], &p[i + 1]) << endl;
        }
    }
    return 0;
}