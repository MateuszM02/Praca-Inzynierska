#pragma once
#include "../../../src/Structures/Matrix.hpp"

namespace tests::Generate
{

class Examples final
{
public:
    Examples() = delete;

    // Przyklad 1. Po podniesieniu macierzy do potegi i dokladnie 1 liczba bedzie rowna i

    static const Matrix<int>& a1()
    {
        static const Matrix<int> instance({ { 1, 1, 0 }, { 0, 1, 0 }, { 0, 0, 1 } });
        return instance;
    }

    // Przyklad 2. Po podniesieniu macierzy do potegi i dokladnie 4 liczby beda rowne 2^i

    static Matrix<double> b1(const unsigned int n) 
    {
        std::vector<std::vector<double>> matrix_values(n, std::vector<double>(n, 0.0));
        matrix_values[0][1] = 1.0;
        matrix_values[1][0] = 1.0;
        
        for (size_t i = 0; i < n; ++i)
        {
            matrix_values[i][i] = 1.0;
        }

        return Matrix<double>(matrix_values);
    }

    // Przyklad 3. Po podniesieniu macierzy rozmiaru n x n 
    // do potegi i dokladnie 1 liczba bedzie rowna i (1 rzad, 2 kolumna)
    static Matrix<int> c1(const unsigned int n) 
    {
        std::vector<std::vector<int>> matrix_values(n, std::vector<int>(n, 0));
        matrix_values[0][1] = 1;

        for (size_t i = 0; i < n; ++i)
        {
            matrix_values[i][i] = 1;
        }

        return Matrix<int>(matrix_values);
    }
};

} // namespace tests::Generate
