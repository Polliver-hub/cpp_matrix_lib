#include "s21_matrix_oop.h"
/*____________________________________________________________*/
void S21Matrix::AllocateMemory() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{0};
  }
}

void S21Matrix::CopyValue(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) = other(i, j);
    }
  }
}

void S21Matrix::Remove() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
  cols_ = 0;
  rows_ = 0;
}

/*____________________________________________________________*/
void S21Matrix::SetColumns(int cols) { Set(rows_, cols); }
int S21Matrix::GetColumns() const { return cols_; }
int S21Matrix::GetRows() const { return rows_; }
void S21Matrix::SetRows(int rows) { Set(rows, cols_); }

void S21Matrix::Set(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Incorrect input, need rows, cols > 0");
  }
  S21Matrix buf(*this);
  Remove();
  rows_ = rows;
  cols_ = cols;
  AllocateMemory();
  for (int i = 0; i < std::min(rows_, buf.rows_); i++) {
    for (int j = 0; j < std::min(cols_, buf.cols_); j++) {
      matrix_[i][j] = buf.matrix_[i][j];
    }
  }
}

/*____________________________________________________________*/
S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  AllocateMemory();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory();
  CopyValue(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = std::exchange(other.rows_, 0);
  cols_ = std::exchange(other.cols_, 0);
  matrix_ = std::exchange(other.matrix_, nullptr);
}

S21Matrix::~S21Matrix() { Remove(); }
/*____________________________________________________________*/
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool res = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          res = false;
        }
      }
    }
  }
  return res;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(double num) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "the number of columns of the first matrix is not "
        "equal to the number of rows of the second matrix");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k)
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
    }
  }
  Remove();
  *this = std::move(res);
}

/*____________________________________________________________*/
double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[row][col];
}

const double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix operator*(double num, const S21Matrix &other) {
  S21Matrix res(other);
  res.MulNumber(num);
  return res;
}

S21Matrix operator*(const S21Matrix &other, double num) {
  S21Matrix res(other);
  res.MulNumber(num);
  return res;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    Remove();
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory();
    CopyValue(other);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    Remove();
    rows_ = std::exchange(other.rows_, 0);
    cols_ = std::exchange(other.cols_, 0);
    matrix_ = std::exchange(other.matrix_, nullptr);
  }
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix &other) const {
  return !EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  this->MulNumber(num);
  return *this;
}

/*____________________________________________________________*/
S21Matrix S21Matrix::Transpose() const {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) res.matrix_[j][i] = matrix_[i][j];
  return res;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::invalid_argument("matrix is not square");
  return AlgDop();
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) throw std::invalid_argument("matrix is not square");
  return Det(rows_);
}

S21Matrix S21Matrix::InverseMatrix() const {
  double determinant = Determinant();
  if (fabs(determinant) < 1e-6) {
    throw std::invalid_argument("Determinant is 0");
  }
  S21Matrix res(rows_, cols_);
  S21Matrix tmp = CalcComplements().Transpose();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      res.matrix_[i][j] = tmp.matrix_[i][j] / determinant;
    }
  }
  return res;
}

/*____________________________________________________________*/
double S21Matrix::Det(int size) const {
  double res = 0;
  int sign = 1;
  S21Matrix tmp;
  if (size == 0) {
    res = 1;
  } else if (size == 1) {
    res = matrix_[0][0];
  } else {
    for (int i = 0; i < size; ++i) {
      tmp = MinorMatrix(0, i, size);
      res += sign * matrix_[0][i] * tmp.Det(size - 1);
      sign = -sign;
    }
  }
  tmp.Remove();
  return res;
}

S21Matrix S21Matrix::MinorMatrix(int skip_row, int skip_col, int size) const {
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0, rows = 0; rows < size; ++rows) {
    for (int j = 0, cols = 0; cols < size; ++cols) {
      if (rows != skip_row && cols != skip_col) {
        tmp.matrix_[i][j] = matrix_[rows][cols];
        ++j;
        j == size - 1 ? j = 0, ++i : 0;
      }
    }
  }
  return tmp;
}

S21Matrix S21Matrix::AlgDop() const {
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = 0;
  } else {
    S21Matrix tmp;
    for (int i = 0, sign = 1; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp = MinorMatrix(i, j, rows_);
        sign = ((i + j) % 2 == 0) ? 1 : -1;
        res.matrix_[i][j] = sign * tmp.Det(rows_ - 1);
        if (res.matrix_[i][j] == -0) {
          res.matrix_[i][j] = 0;
        }
      }
    }
  }
  return res;
}
