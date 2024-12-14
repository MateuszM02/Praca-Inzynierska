#include "FibonacciTests.hpp"

namespace tests::Generate
{

template <Addable DataType>
FibonacciArgs<DataType>::FibonacciArgs(
    const std::string& path,
    const std::pair<DataType, DataType>& initialPair,
    unsigned int n,
    const std::vector<DataType>& expectedResult)
: GenerateTestStruct<DataType, std::pair<DataType, DataType>>(
    path,
    std::move(src::Algorithms::FunctorImpl::createFibonacciFunctor(initialPair)), 
    n, expectedResult)
{ }

INSTANTIATE_TEST_SUITE_P(
    FibonacciIntPrefix,
    FibonacciIntFixture,
    ::testing::Values(
        FibonacciArgs<int>(
            Path::Create(GenerateFibonacci, 1),
            std::make_pair(1, 1),
            45u,
            std::vector<int>{
                                        1, 2, 3, 5, 8, 
                                        13, 21, 34, 55, 89, 
                                        144, 233, 377, 610, 987,
                                        1597, 2584, 4181, 6765, 10946,
                                        17711, 28657, 46368, 75025, 121393,
                                        196418, 317811, 514229, 832040, 1346269,
                                        2178309, 3524578, 5702887, 9227465, 14930352,
                                        24157817, 39088169, 63245986, 102334155, 165580141,
                                        267914296, 433494437, 701408733, 1134903170, 1836311903}),
        FibonacciArgs<int>(
            Path::Create(GenerateFibonacci, 2),
            std::make_pair(2, 2),
            40u,
            std::vector<int>{
                                        2, 4, 6, 10, 16,
                                        26, 42, 68, 110, 178,
                                        288, 466, 754, 1220, 1974,
                                        3194, 5168, 8362, 13530, 21892,
                                        35422, 57314, 92736, 150050, 242786,
                                        392836, 635622, 1028458, 1664080, 2692538,
                                        4356618, 7049156, 11405774, 18454930, 29860704,
                                        48315634, 78176338, 126491972, 204668310, 331160282})
    ));

INSTANTIATE_TEST_SUITE_P(
    FibonacciDoublePrefix, 
    FibonacciDoubleFixture,
    ::testing::Values(
        FibonacciArgs<double>(
            Path::Create(GenerateFibonacci, 3),
            std::make_pair(1.0, 1.0),
            80u,
            std::vector<double>{ 
                                                1.0, 2.0, 3.0, 5.0, 8.0, 
                                                13.0, 21.0, 34.0, 55.0, 89.0,
                                                144.0, 233.0, 377.0, 610.0, 987.0,
                                                1597.0, 2584.0, 4181.0, 6765.0, 10946.0,
                                                17711.0, 28657.0, 46368.0, 75025.0, 121393.0,
                                                196418.0, 317811.0, 514229.0, 832040.0, 1346269.0,
                                                2178309.0, 3524578.0, 5702887.0, 9227465.0, 14930352.0,
                                                24157817.0, 39088169.0, 63245986.0, 102334155.0, 165580141.0,
                                                267914296.0, 433494437.0, 701408733.0, 1134903170.0, 1836311903.0,
                                                2971215073.0, 4807526976.0, 7778742049.0, 12586269025.0, 20365011074.0,
                                                32951280099.0, 53316291173.0, 86267571272.0, 139583862445.0, 225851433717.0,
                                                365435296162.0, 591286729879.0, 956722026041.0, 1548008755920.0, 2504730781961.0,
                                                4052739537881.0, 6557470319842.0, 10610209857723.0, 17167680177565.0, 27777890035288.0,
                                                44945570212853.0, 72723460248141.0, 117669030460994.0, 190392490709135.0, 308061521170129.0,
                                                498454011879264.0, 806515533049393.0, 1304969544928657.0, 2111485077978050.0, 3416454622906707.0,
                                                5527939700884757.0, 8944394323791464.0, 14472334024676221.0, 23416728348467685.0, 37889062373143906.0 }),

        FibonacciArgs<double>(
            Path::Create(GenerateFibonacci, 4),
            std::make_pair(1.5, 2.5),
            60u,
            std::vector<double>{ 
                                                2.5, 4.0, 6.5, 10.5, 17.0, 
                                                27.5, 44.5, 72.0, 116.5, 188.5,
                                                305.0, 493.5, 798.5, 1292.0, 2090.5,
                                                3382.5, 5473.0, 8855.5, 14328.5, 23184.0,
                                                37512.5, 60696.5, 98209.0, 158905.5, 257114.5,
                                                416020.0, 673134.5, 1089154.5, 1762289.0, 2851443.5,
                                                4613732.5, 7465176.0, 12078908.5, 19544084.5, 31622993.0,
                                                51167077.5, 82790070.5, 133957148.0, 216747218.5, 350704366.5,
                                                567451585.0, 918155951.5, 1485607536.5, 2403763488.0, 3889371024.5,
                                                6293134512.5, 10182505537.0, 16475640049.5, 26658145586.5, 43133785636.0,
                                                69791931222.5, 112925716858.5, 182717648081.0, 295643364939.5, 478361013020.5,
                                                774004377960.0, 1252365390980.5, 2026369768940.5, 3278735159921.0, 5305104928861.5 })
    ));

} // namespace tests::Generate
