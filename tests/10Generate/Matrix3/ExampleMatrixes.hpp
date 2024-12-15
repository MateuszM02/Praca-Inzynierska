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

    static std::vector<Matrix<int>> A(const unsigned int power)
    {
        std::vector<Matrix<int>> matrices;
        matrices.reserve(power);
        
        for (int i = 2; i <= power+1; ++i) // pomin pierwsza macierz
        {
            Matrix<int> matrix({ { 1, i, 0 }, { 0, 1, 0 }, { 0, 0, 1 } });
            matrices.push_back(matrix);
        }
        return matrices;
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

    static std::vector<Matrix<double>> B(const unsigned int n, const unsigned int power)
    {
        std::vector<Matrix<double>> matrices;
        matrices.reserve(power);

        double current = 2.0; // pomin pierwsza macierz
        for (int i = 1; i <= power; ++i)
        {
            std::vector<std::vector<double>> matrix_values(n, std::vector<double>(n, 0.0));
            for (size_t i = 0; i < n; ++i)
            {
                matrix_values[i][i] = 1.0;
            }

            matrix_values[0][0] = current;
            matrix_values[1][1] = current;
            matrix_values[0][1] = current;
            matrix_values[1][0] = current;

            Matrix<double> matrix(matrix_values);
            matrices.push_back(matrix);
            current *= 2.0;
        }
        return matrices;
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

    static std::vector<Matrix<int>> C(const unsigned int n, const unsigned int power)
    {
        std::vector<Matrix<int>> matrices;

        matrices.reserve(power);
        for (unsigned int i = 2; i <= power+1; ++i)
        {
            std::vector<std::vector<int>> matrix_values(n, std::vector<int>(n, 0));
            matrix_values[0][1] = i;

            for (size_t j = 0; j < n; ++j)
            {
                matrix_values[j][j] = 1;
            }

            Matrix<int> matrix(matrix_values);
            matrices.push_back(matrix);
        }
        return matrices;
    }
};

} // namespace tests::Generate