class Matrix {
private:
    int rows_;
    int cols_;
    double** data_;
    
    // Вспомогательные методы
    void allocate_memory();
    void deallocate_memory();
    void copy_data(const Matrix& other);
    
public:
    // Конструкторы
    Matrix(int n);  // Единичная матрица n x n
    Matrix(int m, int n, double fill_value = 0);  // Матрица m x n с fill_value
    Matrix(const Matrix& other);  // Конструктор копирования
    
    // Деструктор
    ~Matrix();
    
    // Методы доступа
    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const { return rows_; }
    int get_width() const { return cols_; }
    
    // Операции с матрицами
    void negate();  // -A
    void add_in_place(Matrix& other);     // this += other
    Matrix multiply(Matrix& other) const; // A * B
    
    // Дополнительные методы
    void print() const;
    bool is_square() const { return rows_ == cols_; }
    
    // Проверка индексов
    void check_index(int i, int j) const;
    
    // Оператор присваивания
    Matrix& operator=(const Matrix& other);
};