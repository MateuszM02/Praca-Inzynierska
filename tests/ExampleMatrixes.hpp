#pragma once

#include <random>

#include "../src/Structures/Matrix.hpp"

namespace tests
{

class Examples final
{
public:
    Examples() = delete;

    // Przyklad 1. Po podniesieniu macierzy do potegi i dokladnie 1 liczba bedzie rowna i

    static CopyableMatrix<int> a1(const int i = 1)
    {
        std::vector<std::vector<int>> values{
            { 1, i, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 } };
        CopyableMatrix<int> instance(std::move(values));
        return instance;
    }

    // Przyklad 2. Po podniesieniu macierzy rozmiaru n x n
    // do potegi i dokladnie 1 liczba bedzie rowna i (1 rzad, 2 kolumna)
    static CopyableMatrix<int> b1(const unsigned int n)
    {
        std::vector<std::vector<int>> matrix_values(n, std::vector<int>(n, 0));
        matrix_values[0][1] = 1;

        for (size_t i = 0; i < n; ++i)
        {
            matrix_values[i][i] = 1;
        }

        return CopyableMatrix<int>(std::move(matrix_values));
    }

    static CopyableMatrix<int> randomIntMatrix(const unsigned int matrixSize)
    {
        std::vector<std::vector<int>> matrix_values(matrixSize, std::vector<int>(matrixSize, 0));
        static std::mt19937 gen(0);
        static std::uniform_int_distribution<> dis(1, 10);

        for (size_t i = 0; i < matrixSize; ++i)
        {
            for (size_t j = 0; j < matrixSize; ++j)
            {
                matrix_values[i][j] = dis(gen);
            }
        }
        return CopyableMatrix<int>(std::move(matrix_values));
    }

    static CopyableMatrix<double> randomDoubleMatrix(const unsigned int matrixSize)
    {
        std::vector<std::vector<double>> matrix_values(matrixSize, std::vector<double>(matrixSize, 0.0));
        static std::mt19937 gen(0);
        static std::uniform_real_distribution<> dis(1.0, 10.0);

        for (size_t i = 0; i < matrixSize; ++i)
        {
            for (size_t j = 0; j < matrixSize; ++j)
            {
                matrix_values[i][j] = dis(gen);
            }
        }
        return CopyableMatrix<double>(std::move(matrix_values));
    }
};

} // namespace tests
