#pragma once

// boost::accumulators::accumulators uzywa przestarzalych metod,
// wiec dla tego pliku wylaczymy warning [-Werror=deprecated-copy]
#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wdeprecated-copy"
#elif defined(_MSC_VER)
    #pragma warning(disable : 4996)
#endif

#include "Base.hpp"
#include "../Concepts/DataTypeConcepts.hpp"

#include <bits/stl_numeric.h> // std::accumulate
#include <optional>

// boost::accumulators::accumulators wraz z metodami min, max, sum, mean
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/sum.hpp>

using namespace src::Concepts;

namespace src::Algorithms
{

enum AccType
{
    SumOnly,
    SumAndMean,
    SumAndExtremes,
    DoItAll
};

template <typename DataType>
struct AccResults
{
    explicit AccResults()
    : sum(DataType())
    , minimum(std::nullopt)
    , maximum(std::nullopt)
    , mean(std::nullopt)
    { }

    DataType sum;
    std::optional<DataType> minimum;
    std::optional<DataType> maximum;
    std::optional<DataType> mean;
};

template <IsAccumulable DataType>
class Accumulator final : public BaseClass<DataType, AccResults<DataType>>
{
public:
    explicit Accumulator(const std::vector<DataType>& data, AccType accType)
    : data_(std::move(data))
    , accType_(accType)
    { }

private:
    void resetData() const override { }

    void FOR_ITER(const std::function<void(DataType)>& f) const
    {
        for (auto it = data_.begin(); it != data_.end(); ++it)
        {
            f(*it);
        }
    }

    template <typename AccumulatorSet>
    void FOR_ITER_ON_ACC(AccumulatorSet& acc) const
    {
        FOR_ITER([&acc](const DataType& wrapper) { acc(wrapper); });
    }

    AccResults<DataType> executeSTL() const override
    {
        AccResults<DataType> results;
        results.sum = std::accumulate(data_.begin(), data_.end(), DataType());

        if (accType_ == SumAndExtremes || accType_ == DoItAll)
        {
            results.minimum = *std::min_element(data_.begin(), data_.end());
            results.maximum = *std::max_element(data_.begin(), data_.end());
        }
        if (accType_ == SumAndMean || accType_ == DoItAll)
        {
            results.mean = (results.sum / data_.size());
        }
        return results;
    }

    AccResults<DataType> executeBoost() const override
    {
        using namespace boost::accumulators;
        AccResults<DataType> results;
        
        switch (accType_)
        {
            case SumOnly:
            {
                accumulator_set<DataType, stats<tag::sum>> acc1;
                FOR_ITER_ON_ACC(acc1);
                results.sum = sum(acc1);
                return results;
            }
            case SumAndExtremes:
            {
                accumulator_set<DataType,
                    stats<tag::sum, tag::min, tag::max>> acc2;
                FOR_ITER_ON_ACC(acc2);
                results.sum = sum(acc2);
                results.minimum = min(acc2);
                results.maximum = max(acc2);
                return results;
            }
            case SumAndMean:
            {
                accumulator_set<DataType,
                    stats<tag::sum, tag::mean>> acc3;
                FOR_ITER_ON_ACC(acc3);
                results.sum = sum(acc3);
                results.mean = mean(acc3);
                return results;
            }
            case DoItAll:
            {
                accumulator_set<DataType,
                    stats<tag::sum, tag::min, tag::max, tag::mean>> acc4;
                FOR_ITER_ON_ACC(acc4);
                results.sum = sum(acc4);
                results.minimum = min(acc4);
                results.maximum = max(acc4);
                results.mean = mean(acc4);
                return results;
            }
            default:
                throw std::invalid_argument("Zly typ enuma AccType!");
        }
        return results;
    }

    AccResults<DataType> executeSimple() const override
    {
        AccResults<DataType> results;

        if (accType_ == SumOnly || accType_ == SumAndMean)
        {
            FOR_ITER([&results](const DataType& wrapper) { results.sum += wrapper; });
        }
        else // SumAndExtremes, DoItAll
        {
            results.minimum = *data_.begin();
            results.maximum = *data_.begin();
            FOR_ITER([&results](const DataType& wrapper)
            {
                results.sum += wrapper;
                if (wrapper < results.minimum)
                    results.minimum = wrapper;
                else if (wrapper > results.maximum)
                    results.maximum = wrapper;
            });
        }

        if (accType_ == SumAndMean || accType_ == DoItAll)
        {
            results.mean = (results.sum / data_.size());
        }
        return results;
    }

private:
    const std::vector<DataType> data_;
    const AccType accType_;
};

} // namespace src::Algorithms
