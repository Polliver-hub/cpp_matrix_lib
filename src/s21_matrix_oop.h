#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <utility>

class S21Matrix {
 private:
  /*____________________________________________________________*/
  // Attributes
  /*____________________________________________________________*/
  int rows_, cols_;  // rows and columns attributes
  double **matrix_;  // pointer to the memory where the matrix will be allocated

 public:
  /*____________________________________________________________*/
  // Constructors
  /*____________________________________________________________*/
  S21Matrix();                            // default constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix &other);      // copy constructor
  S21Matrix(S21Matrix &&other) noexcept;  // move constructor
  ~S21Matrix();                           // destructor
  /*____________________________________________________________*/
  // Getters and Setters.
  /*____________________________________________________________*/
  void SetColumns(int cols);
  int GetColumns() const;
  void SetRows(int rows);
  int GetRows() const;
  void Set(int rows, int cols);
  /*____________________________________________________________*/
  //   operators overloads
  /*____________________________________________________________*/
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  friend S21Matrix operator*(double num, const S21Matrix &other);
  friend S21Matrix operator*(const S21Matrix &other, double num);

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  double &operator()(int row, int col);
  const double &operator()(int row, int col) const;

  bool operator==(const S21Matrix &other) const;
  bool operator!=(const S21Matrix &other) const;

  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);
  /*____________________________________________________________*/
  // public methods
  /*____________________________________________________________*/
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  /*____________________________________________________________*/
  // private helper methods
  /*____________________________________________________________*/
 private:
  void AllocateMemory();
  void CopyValue(const S21Matrix &other);
  void Remove();
  S21Matrix MinorMatrix(int skip_row, int skip_col, int size) const;
  double Det(int size) const;
  S21Matrix AlgDop() const;
};

#endif
