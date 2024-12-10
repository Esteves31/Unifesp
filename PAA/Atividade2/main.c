#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double closest(double points[][2], int size);
double distance_between(const double point_a[][2], const double point_b[][2]);
int compare_points(const void *a, const void *b);

int main () {
    int N;
    double min_path;

    scanf("%d", &N);

    double points[N][2];

    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &points[i][0], &points[i][1]);   
    }

    qsort(points, N, sizeof(points[0]), compare_points);
    min_path = closest(points, N);

    printf("%.10lf\n", min_path);
    
    return 0;
}

double distance_between(const double point_a[][2], const double point_b[][2]) {
    double dx = point_a[0][0] - point_b[0][0];
    double dy = point_a[0][1] - point_b[0][1];
    return sqrt(dx * dx + dy * dy);
}

int compare_points(const void *a, const void *b) {
    const double *point_a = (const double *)a;
    const double *point_b = (const double *)b;

    if (point_a[0] < point_b[0])
        return -1;
    else if (point_a[0] > point_b[0])
        return 1;
    return 0;
}

double closest(double points[][2], int size) {
    if (size <= 3) {
        double min_dist = INFINITY;
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                double dist = distance_between(&points[i], &points[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
        }
        return min_dist;
    }

    int mid = size / 2;
    double d_left = closest(points, mid);
    double d_right = closest(points + mid, size - mid);

    double d = fmin(d_left, d_right);

    double strip[size][2];
    int strip_size = 0;
    
    for (int i = 0; i < size; i++) {
        if (fabs(points[i][0] - points[mid][0]) < d) {
            strip[strip_size][0] = points[i][0];
            strip[strip_size][1] = points[i][1];
            strip_size++;
        }
    }

    for (int i = 0; i < strip_size; i++) {
        for (int j = i + 1; j < strip_size && j <= i + 7; j++) {
            double dist = distance_between(&strip[i], &strip[j]);
            if (dist < d) {
                d = dist;
            }
        }
    }

    return d;
}
