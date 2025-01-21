#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

double distance(const Point &p1, const Point &p2);
bool compareByX(const Point &a, const Point &b);
bool compareByY(const Point &a, const Point &b);
double stripClosest(vector<Point> &strip, double d);
double closestPair(vector<Point> &points, int left, int right);

int main() {
    int N;
    cin >> N;

    vector<Point> points(N);
    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    sort(points.begin(), points.end(), compareByX);

    // Calcula a menor distância
    double result = closestPair(points, 0, N);

    // Imprime o resultado com 10 casas decimais
    cout << fixed << setprecision(10) << result << endl;

    return 0;
}

double distance(const Point &p1, const Point &p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool compareByX(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool compareByY(const Point &a, const Point &b) {
    return a.y < b.y;
}

double stripClosest(vector<Point> &strip, double d) {
    double minDist = d;
    sort(strip.begin(), strip.end(), compareByY); 

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = min(minDist, distance(strip[i], strip[j]));
        }
    }

    return minDist;
}

double closestPair(vector<Point> &points, int left, int right) {
    if (right - left <= 3) {
        double minDist = numeric_limits<double>::max();
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                minDist = min(minDist, distance(points[i], points[j]));
            }
        }
        return minDist;
    }

    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    double dl = closestPair(points, left, mid);
    double dr = closestPair(points, mid, right);

    double d = min(dl, dr);

    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    return min(d, stripClosest(strip, d));
}