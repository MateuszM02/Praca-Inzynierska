#pragma once

#include "../NthElementTestFixture.hpp"
#include "../../../src/Structures/PointsImpl.hpp"

using namespace src::Structures;

namespace tests::NthElement
{

struct PointsArgs : public NthElementTestStruct<Point2D>
{
    PointsArgs(
        Findable<Point2D> (*fun)(const unsigned int),
        const unsigned int n,
        const unsigned int vectorSize)
    : NthElementTestStruct<Point2D>(
        NthElementPoints,
        std::move(std::make_shared<NthFinder<Point2D>>(
            NthElementTestFixture<Point2D>::initTestData(fun, n, vectorSize))))
    { }
};

class PointsFixture : public NthElementTestFixture<Point2D>
{
public:
    static Findable<Point2D> fmod3i3_mod7i64(const unsigned int i)
    {
        return { { 3*i + (i % 3), 7*i % 64 },
                 Point2DImpl::equal,
                 Point2DImpl::less,
                 Point2DImpl::copyAssign };
    }

    static Findable<Point2D> f3i_mod9i64(const unsigned int i)
    {
        return { { 3*i, 9*i % 64 },
                 Point2DImpl::equal,
                 Point2DImpl::less,
                 Point2DImpl::copyAssign };
    }

    void VerifyTest(const auto& args)
    {
        std::ostringstream os; // Uzycie ostringstream do wypisywania wynikow testow

        const std::vector<Findable<Point2D>>& stlResult = args.ref_->call(src::MethodType::STL, os);
        const std::vector<Findable<Point2D>>& boostResult = args.ref_->call(src::MethodType::Boost, os);
        const std::vector<Findable<Point2D>>& simpleResult = args.ref_->call(src::MethodType::Simple, os);

        EXPECT_EQ(stlResult.size(), simpleResult.size()) << "Rozmiar wyniku STL rozni sie od oczekiwanego."; 
        EXPECT_EQ(boostResult.size(), simpleResult.size()) << "Rozmiar wyniku Boost rozni sie od oczekiwanego.";

        // Zapisywanie wynikow testu do pliku
        std::ofstream outFile(args.filePath_, std::ios::out | std::ios::trunc);
        if (outFile.is_open())
        {
            if (::testing::Test::HasFailure()) 
            {
                outFile << "Rozmiary wynikow nie zgadzaja sie z oczekiwanymi.\n";
                outFile << ::testing::internal::GetCapturedStdout();
                outFile << ::testing::internal::GetCapturedStderr();
                outFile.close();
                return;
            }
            
            n_ = args.ref_->n_;
            verifyElementEqualities(stlResult, boostResult, simpleResult, os);

            outFile << os.str();
            outFile.close();
        }
        else
        {
            std::cerr << "Nie udalo sie zapisac wynikow testu do pliku: " << args.filePath_ << "\n";
        }
    }

    void verifyElementEqualities(
        const std::vector<Findable<Point2D>>& stlResult,
        const std::vector<Findable<Point2D>>& boostResult,
        const std::vector<Findable<Point2D>>& simpleResult,
        std::ostringstream& os)
    {
        // Petla for do porownywania wynikow, jesli rozmiary sa rowne
        auto stlIter = stlResult.begin();
        auto boostIter = boostResult.begin();
        auto simpleIter = simpleResult.begin();
        unsigned int i = 0;
        
        auto stlNthIter = stlResult.begin();
        auto boostNthIter = boostResult.begin();
        auto simpleNthIter = simpleResult.begin();
        std::advance(stlNthIter, n_);
        std::advance(boostNthIter, n_);
        std::advance(simpleNthIter, n_);

        while (simpleIter != simpleNthIter)
        {
            EXPECT_LT(*stlIter, *stlNthIter) << "Wynik STL rozni sie na indeksie " << i;
            EXPECT_LT(*boostIter, *boostNthIter) << "Wynik Boost rozni sie na indeksie " << i;
            EXPECT_LT(*simpleIter, *simpleNthIter) << "Wynik Boost rozni sie na indeksie " << i;
            
            ++i;
            ++stlIter;
            ++boostIter;
            ++simpleIter;
        }

        EXPECT_EQ_OS(*stlIter, *stlNthIter, os) << "Wynik STL rozni sie na indeksie " << i;
        EXPECT_EQ_OS(*boostIter, *boostNthIter, os) << "Wynik Boost rozni sie na indeksie " << i;
        EXPECT_EQ_OS(*simpleIter, *simpleNthIter, os) << "Wynik Boost rozni sie na indeksie " << i;
        
        ++i;
        ++stlIter;
        ++boostIter;
        ++simpleIter;

        while (simpleIter != simpleResult.end())
        {
            EXPECT_LT(*stlNthIter, *stlIter) << "Wynik STL rozni sie na indeksie " << i;
            EXPECT_LT(*boostNthIter, *boostIter) << "Wynik Boost rozni sie na indeksie " << i;
            EXPECT_LT(*simpleNthIter, *simpleIter) << "Wynik Boost rozni sie na indeksie " << i;
            
            ++i;
            ++stlIter;
            ++boostIter;
            ++simpleIter;
        }
    }

    unsigned int n_;
};

TEST_P(PointsFixture, PointsNthElementTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::NthElement
