#pragma once

#include "../TransformTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"
#include "../../../src/Structures/MatrixImpl.hpp"

using namespace src::Structures;

namespace tests::Transform
{

struct MatrixToIntVectorTransformArgs final : public TransformTestStruct<Matrix<int>, std::vector<IntVector>>
{
    explicit MatrixToIntVectorTransformArgs(
        Matrix<int> (*dataCreator)(const unsigned int),
        const unsigned int n)
    : TransformTestStruct<Matrix<int>, std::vector<IntVector>>(
        TestType::TransformMatrixToIntVector,
        [dataCreator, n]()
        {
            std::vector<Matrix<int>> inData =
                initTestData<std::vector<Matrix<int>>>(dataCreator, n);
            return std::make_shared<Transformer<Matrix<int>, std::vector<IntVector>>>(
                std::move(inData),
                &transformer);
        })
    { }

    static std::vector<IntVector> transformer(const Matrix<int>& matrix)
    {
        const std::size_t mSize = matrix.size();
        std::vector<IntVector> vector;
        vector.reserve(mSize);

        std::vector<int> values;
        values.reserve(mSize);
        for (std::size_t row = 0; row < mSize; row++)
        {
            values = {};
            for (std::size_t col = 0; col < mSize; col++)
            {
                values.emplace_back(matrix.get(row, col));
            }
            vector.emplace_back(values);
        }
        return vector;
    }
};

class MatrixToIntVectorTransformFixture : public TransformTestFixture<std::vector<IntVector>>
{
public:
    // macierz rozmiaru n * n z samymi jedynkami
    static Matrix<int> sortedFirstElementGenerator(const unsigned int n)
    {
        std::vector<std::vector<int>> values(n, std::vector<int>(n, 1));
        return Matrix<int>(std::move(values));
    }
};

TEST_P(MatrixToIntVectorTransformFixture, MatrixToIntVectorTransformTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Transform
