#include <stdio.h>

int main() {
    int n = 0;  // 鸡兔的总数
    int m = 0;  // 鸡兔的总腿数
    int a = 0;  // 鸡的数量
    int b = 1;  // 标志，用来表示是否找到答案

    printf("请输入鸡兔的总数目: ");
    scanf("%d", &n);
    printf("请输入鸡兔的总腿数: ");
    scanf("%d", &m);

    for (a = 0; a <= n; a++) {
        if (a * 2 + (n - a) * 4 == m) {
            printf("有%d只鸡, %d只兔子\n", a, n - a);
            b = 0;  // 找到答案，设置标志为0
            break;  // 跳出循环
        }
    }

    if (b == 1) {
        printf("无解，no answer\n");
    }

    return 0;
}
