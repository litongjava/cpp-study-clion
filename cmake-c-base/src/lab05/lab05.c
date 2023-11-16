#include <stdio.h>
#include <string.h>

//
// Created by Tong Li on 11/15/2023.
//
int main() {
  printf("start\n");
  char str[101];
  printf("Please enter a real number:");
  scanf("%s", str);

  char *ptr = strchr(str, '.');
  if (ptr != NULL) {
    *ptr = '\0';
  }

  int i = 0;
  while (str[i] == '0' && str[i + 1] != '\0') {
    i++;
  }

  printf(" the integer part of which is: %s\n", str + i);

  return 0;
}
