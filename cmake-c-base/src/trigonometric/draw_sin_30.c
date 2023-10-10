#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "set xrange [0:360]\n");
    fprintf(gnuplotPipe, "plot sin(x*%f)\n", PI / 180.0 * 30.0);
    fflush(gnuplotPipe);
    getchar();
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);

    return 0;
}
