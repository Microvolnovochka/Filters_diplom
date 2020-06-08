#ifndef MATRIX_H
#define MATRIX_H

#define PI 3.14159265

#include <math.h>

typedef struct {
  int rows;
  int cols;

  double** data;
} Matrix;

Matrix alloc_matrix(int rows, int cols);

void free_matrix(Matrix m);

void set_matrix(Matrix m, ...);

void set_identity_matrix(Matrix m);

void copy_matrix(Matrix source, Matrix destination);

void print_matrix(Matrix m);

void add_matrix(Matrix a, Matrix b, Matrix c);

void subtract_matrix(Matrix a, Matrix b, Matrix c);

void subtract_from_identity_matrix(Matrix a);

void multiply_matrix(Matrix a, Matrix b, Matrix c);

void multiply_by_transpose_matrix(Matrix a, Matrix b, Matrix c);

void transpose_matrix(Matrix input, Matrix output);

int equal_matrix(Matrix a, Matrix b, double tolerance);

void scale_matrix(Matrix m, double scalar);

void swap_rows(Matrix m, int r1, int r2);

void scale_row(Matrix m, int r, double scalar);


void shear_row(Matrix m, int r1, int r2, double scalar);

int destructive_invert_matrix(Matrix input, Matrix output);

#endif // MATRIX_H
