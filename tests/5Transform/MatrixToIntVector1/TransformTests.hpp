#pragma once

#include "../TransformTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"
#include "../../../src/Structures/MatrixImpl.hpp"

using namespace src::Structures;

namespace tests::Transform
{

using InType = NonCopyableMatrix<int>;
using ReturnType = std::vector<NonCopyableIntVector>;
using Base = BaseTestStruct<std::vector<ReturnType>>;
using Parent = TransformTestStruct<InType, ReturnType>;

struct MatrixToIntVectorTransformArgs final : public Parent
{
    explicit MatrixToIntVectorTransformArgs(
        InType (*dataCreator)(const unsigned int),
        const unsigned int n)
    : Parent(TestType::TransformMatrixToIntVector,
        [dataCreator, n]()
        {
            std::vector<InType> inData =
                initTestData<std::vector<InType>>(dataCreator, n);
            return std::make_shared<Transformer<InType, ReturnType>>(
                std::move(inData),
                &transformer);
        })
    { }

    static ReturnType transformer(const InType& matrix)
    {
        const std::size_t mSize = matrix.size();
        ReturnType vector;
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

class MatrixToIntVectorTransformFixture : public TransformTestFixture<ReturnType>
{
public:
    // macierz rozmiaru n * n z samymi jedynkami
    static InType sortedFirstElementGenerator(const unsigned int n)
    {
        std::vector<std::vector<int>> values(n, std::vector<int>(n, 1));
        return InType(std::move(values));
    }
};

TEST_P(MatrixToIntVectorTransformFixture, MatrixToIntVectorTransformTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Transform
