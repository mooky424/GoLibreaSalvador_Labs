#include<iostream>
#include <cstdlib> 
using namespace std;

struct Point3D {
  int x, y, z;
};

int calcDistance(int test_cases) {
  while (test_cases--){
    int n;
    cin >> n;
    Point3D point[n];

    // Get all points
    for (int i = 1; i <= n; i++) {
      cin >> point[i].x >> point[i].y >> point[i].z;
    }

    // Calculate Manhattan distance between adjacent points
    for (int i = 1; i <= n - 1; i++) {
      int distance = abs(point[i].x - point[i + 1].x) +
                     abs(point[i].y - point[i + 1].y) +
                     abs(point[i].z - point[i + 1].z);
      cout << distance << endl;
    }

    if (test_cases > 0) {
      cout << endl;
    }
  }
  return 0;
}

int main() {
  int test_cases;
  cin >> test_cases;
  calcDistance(test_cases);
  return 0;
}