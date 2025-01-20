#pragma once

#include "../TransformTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"
#include "../../../src/Structures/MatrixImpl.hpp"

using namespace src::Structures;

namespace tests::Transform
{

using InType1 = NonCopyableMatrix<int>;
using ReturnType1 = std::vector<NonCopyableIntVector>;
using Base1 = BaseTestStruct<std::vector<ReturnType1>>;
using Parent1 = TransformTestStruct<InType1, ReturnType1>;

struct MatrixToIntVectorTransformArgs final : public Parent1
{
    explicit MatrixToIntVectorTransformArgs(
        InType1 (*dataCreator)(const unsigned int),
        const unsigned int n)
    : Parent1(TestType::TransformMatrixToIntVector,
        [dataCreator, n]()
        {
            std::vector<InType1> inData =
                initTestData<std::vector<InType1>>(dataCreator, n);
            return std::make_shared<Transformer<InType1, ReturnType1>>(
                std::move(inData),
                &transformer);
        })
    { }

    static ReturnType1 transformer(const InType1& matrix)
    {
        const std::size_t mSize = matrix.size();
        ReturnType1 vector;
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

class MatrixToIntVectorTransformFixture : public TransformTestFixture<ReturnType1>
{
public:
    // macierz rozmiaru n * n z samymi jedynkami
    static InType1 sortedFirstElementGenerator(const unsigned int n)
    {
        std::vector<std::vector<int>> values(n, std::vector<int>(n, 1));
        return InType1(std::move(values));
    }
};

} // namespace tests::Transform
