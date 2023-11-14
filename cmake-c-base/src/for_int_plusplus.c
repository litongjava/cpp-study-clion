#include <printf.h>

//
// Created by Ping Lee on 2023/11/13.
//
int main(int argc, char **argv) {
  int size = 10;
  for (int i = 0; i < size; i++) {
    printf("i %d\n", i);
  }
  printf("========\n");

  int length = 10;
  for (int i = 0; i < length; ++i) {
    printf("i %d\n", i);
  }
  return 0;
}