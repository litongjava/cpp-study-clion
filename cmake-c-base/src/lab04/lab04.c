//
// Created by Tong Li on 11/15/2023.
//
#include <stdio.h>

void inputArray(int n, int matrix[][100]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &matrix[i][j]);
    }
  }
}

int isParity(int n, int matrix[][100]) {
  int rowSum, colSum;

  // Check each row
  for (int i = 0; i < n; i++) {
    rowSum = 0;
    for (int j = 0; j < n; j++) {
      rowSum += matrix[i][j];
    }
    if (rowSum % 2 != 0) return 0; // Not a parity matrix
  }

  // Check each column
  for (int j = 0; j < n; j++) {
    colSum = 0;
    for (int i = 0; i < n; i++) {
      colSum += matrix[i][j];
    }
    if (colSum % 2 != 0) return 0; // Not a parity matrix
  }

  return 1; // Is a parity matrix
}

int main() {
  int n;
  int matrix[100][100];

  printf("Enter the size of the matrix: ");
  scanf("%d", &n);

  printf("Enter the matrix values (each row on a new line):\n");
  inputArray(n, matrix);

  if (isParity(n, matrix)) {
    printf("yes\\n");
  } else {
    printf("no\\n");
  }

  return 0;
}
