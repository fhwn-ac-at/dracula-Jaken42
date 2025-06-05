#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct point{
    float x;
    float y;
} point;

point rand_point(){
    return (point){
        .x = 1 - 2 * drand48(),
        .y = 1 - 2 * drand48(),
    };
}

int is_point_in_circle(point p){
    if (p.x*p.x + p.y*p.y <= 1){
        return 1;
    }
    return 0;
}

point random_point_in_unit_circle() {
    point p;
    do {
        p = rand_point();
    } while (!is_point_in_circle(p));
    return p;
}

float approximate_pi(int const num_samples){
    int inside = 0;

    for (int i = 0; i < num_samples; ++i){
        point const p = rand_point();
        if (is_point_in_circle(p)) ++inside;
    }

    return 4.0f * (float) inside / (float) num_samples;
}

int main(void){
    printf("Hello world\n");
    srand48(time(0));
    point myPoint = rand_point();
    is_point_in_circle(myPoint) ? printf("Its on the circle!\n") : printf("Its not on the circle!\n");

    printf("Approximate pi: %.4f\n", approximate_pi(10000));

    return 0;
}
