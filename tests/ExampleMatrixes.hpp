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

    static CopyableMatrix<int> a1()
    {
        std::vector<std::vector<int>> values{
            { 1, 1, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 } };
        CopyableMatrix<int> instance(std::move(values));
        return instance;
    }

    // Przyklad 2. Po podniesieniu macierzy do potegi i dokladnie 4 liczby beda rowne 2^i

    static CopyableMatrix<double> b1(const unsigned int n)
    {
        std::vector<std::vector<double>> matrix_values(n, std::vector<double>(n, 0.0));
        matrix_values[0][1] = 1.0;
        matrix_values[1][0] = 1.0;

        for (size_t i = 0; i < n; ++i)
        {
            matrix_values[i][i] = 1.0;
        }

        return CopyableMatrix<double>(std::move(matrix_values));
    }

    // Przyklad 3. Po podniesieniu macierzy rozmiaru n x n 
    // do potegi i dokladnie 1 liczba bedzie rowna i (1 rzad, 2 kolumna)
    static CopyableMatrix<int> c1(const unsigned int n)
    {
        std::vector<std::vector<int>> matrix_values(n, std::vector<int>(n, 0));
        matrix_values[0][1] = 1;

        for (size_t i = 0; i < n; ++i)
        {
            matrix_values[i][i] = 1;
        }

        return CopyableMatrix<int>(std::move(matrix_values));
    }

    static CopyableMatrix<int> randomIntMatrix()
    {
        static constexpr std::size_t MATRIX_SIZE{100};
        std::vector<std::vector<int>> matrix_values(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 0));
        static std::mt19937 gen(0);
        static std::uniform_int_distribution<> dis(1, 10);

        for (size_t i = 0; i < MATRIX_SIZE; ++i)
        {
            for (size_t j = 0; j < MATRIX_SIZE; ++j)
            {
                matrix_values[i][j] = dis(gen);
            }
        }
        return CopyableMatrix<int>(std::move(matrix_values));
    }

    static CopyableMatrix<double> randomDoubleMatrix()
    {
        static constexpr std::size_t MATRIX_SIZE{100};
        std::vector<std::vector<double>> matrix_values(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE, 0.0));
        static std::mt19937 gen(0);
        static std::uniform_real_distribution<> dis(1.0, 10.0);

        for (size_t i = 0; i < MATRIX_SIZE; ++i)
        {
            for (size_t j = 0; j < MATRIX_SIZE; ++j)
            {
                matrix_values[i][j] = dis(gen);
            }
        }
        return CopyableMatrix<double>(std::move(matrix_values));
    }
};

} // namespace tests
