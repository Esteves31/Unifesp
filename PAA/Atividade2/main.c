#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double distance_between (const double point_a[][2], const double point_b[][2]);
double closest (const double points[][2], const int size);
void merge_sort (double points[][2], const int min, const int max);
void merge (double points[][2], const int min, const int mid, const int max);

int main () {
    int N;
    double min_path;

    scanf("%d", &N);

    double points_matrix[N][2];

    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &points_matrix[i][0], &points_matrix[i][1]);   
    }

    merge_sort(points_matrix, 0, N);
    min_path = closest(points_matrix, N);

    printf("%.10lf\n", min_path);
    
    return EXIT_SUCCESS;
}

double distance_between (const double point_a[][2], const double point_b[][2]) {
    double dx = point_a[0][0] - point_b[0][0];
    double dy = point_a[0][1] - point_b[0][1];
    return sqrt(dx * dx + dy * dy);
}

double closest (const double points[][2], const int size) {
    if (size <= 3) {
        double min_dist = INFINITY;
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                double dist = sqrt(pow(points[i][0] - points[j][0], 2) +
                                  pow(points[i][1] - points[j][1], 2));
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
        }
        return min_dist;
    }

    int mid = size / 2;

    double left_min = closest(points, mid);
    double right_min = closest(points + mid, size - mid);

    double d = fmin(left_min, right_min);

    double strip[size][2];
    int strip_size = 0;
    for (int i = 0; i < size; i++) {
        if (fabs(points[i][0] - points[mid][0]) < d) {
            strip[strip_size][0] = points[i][0];
            strip[strip_size][1] = points[i][1];
            strip_size++;
        }
    }

    for (int i = 1; i < strip_size; i++) {
        double key_x = strip[i][0], key_y = strip[i][1];
        int j = i - 1;
        while (j >= 0 && strip[j][1] > key_y) {
            strip[j + 1][0] = strip[j][0];
            strip[j + 1][1] = strip[j][1];
            j--;
        }
        strip[j + 1][0] = key_x;
        strip[j + 1][1] = key_y;
    }

    for (int i = 0; i < strip_size; i++) {
        for (int j = i + 1; j < strip_size && (strip[j][1] - strip[i][1]) < d; j++) {
            double dist = sqrt(pow(strip[i][0] - strip[j][0], 2) +
                              pow(strip[i][1] - strip[j][1], 2));
            if (dist < d) {
                d = dist;
            }
        }
    }

    return d;
}

void merge_sort (double points[][2], const int min, const int max) {
    if (min < max - 1) {
        int mid = (min + max) / 2;
        merge_sort(points, min, mid);
        merge_sort(points, mid + 1, max);
        merge(points, min, mid, max);
    }
}

void merge(double points[][2], const int min, const int mid, const int max) {
    int i = min, j = mid, k = 0;
    double (*temp)[2] = malloc((max - min) * sizeof(double[2]));

    while (i < mid && j < max) {
        if (points[i][0] <= points[j][0]) {
            temp[k][0] = points[i][0];
            temp[k][1] = points[i][1];
            i++;
        } else {
            temp[k][0] = points[j][0];
            temp[k][1] = points[j][1];
            j++;
        }
        k++;
    }

    while (i < mid) {
        temp[k][0] = points[i][0];
        temp[k][1] = points[i][1];
        i++;
        k++;
    }

    while (j < max) {
        temp[k][0] = points[j][0];
        temp[k][1] = points[j][1];
        j++;
        k++;
    }

    for (i = min, k = 0; i < max; i++, k++) {
        points[i][0] = temp[k][0];
        points[i][1] = temp[k][1];
    }

    free(temp); 
}
