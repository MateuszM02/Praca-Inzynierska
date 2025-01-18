#pragma once

#include "../TransformTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"
#include "../../../src/Structures/MatrixImpl.hpp"

using namespace src::Structures;

namespace tests::Transform
{

using Base = BaseTestStruct<std::vector<std::vector<NonCopyableIntVector>>>;
using Parent = TransformTestStruct<NonCopyableMatrix<int>, std::vector<NonCopyableIntVector>>;

struct MatrixToIntVectorTransformArgs final : public Parent
{
    explicit MatrixToIntVectorTransformArgs(
        NonCopyableMatrix<int> (*dataCreator)(const unsigned int),
        const unsigned int n)
    : Parent(TestType::TransformMatrixToIntVector,
        [dataCreator, n]()
        {
            std::vector<NonCopyableMatrix<int>> inData =
                initTestData<std::vector<NonCopyableMatrix<int>>>(dataCreator, n);
            return std::make_shared<Transformer<NonCopyableMatrix<int>, std::vector<NonCopyableIntVector>>>(
                std::move(inData),
                &transformer);
        })
    { }

    static std::vector<NonCopyableIntVector> transformer(const NonCopyableMatrix<int>& matrix)
    {
        const std::size_t mSize = matrix.size();
        std::vector<NonCopyableIntVector> vector;
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

class MatrixToIntVectorTransformFixture : public TransformTestFixture<std::vector<NonCopyableIntVector>>
{
public:
    // macierz rozmiaru n * n z samymi jedynkami
    static NonCopyableMatrix<int> sortedFirstElementGenerator(const unsigned int n)
    {
        std::vector<std::vector<int>> values(n, std::vector<int>(n, 1));
        return NonCopyableMatrix<int>(std::move(values));
    }
};

TEST_P(MatrixToIntVectorTransformFixture, MatrixToIntVectorTransformTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Transform
