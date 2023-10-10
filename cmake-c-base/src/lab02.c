#include <stdio.h>

int main() {
    double r, s, v;
    double pi = 3.14;
    printf("input r:\n");
    scanf("%lf", &r);
    s = 4 * pi * r * r; // 计算球体的表面积
    v = (4.0 / 3.0) * pi * r * r * r; // 计算球体的体积
    printf("r=%lf\n", r);
    printf("s=%lf v=%lf\n", s, v);
    getchar();
    return 0;
}
