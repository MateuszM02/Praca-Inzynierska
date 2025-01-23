#pragma once

// boost::accumulators::accumulators uzywa przestarzalych metod,
// wiec dla tego pliku wylaczymy warning [-Werror=deprecated-copy]
#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wdeprecated-copy"
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

enum class AccType : unsigned char
{
    SumOnly,
    SumAndMean,
    SumAndExtremes,
    DoItAll
};

template <typename DataType>
requires std::is_default_constructible_v<DataType>
struct AccResults final
{
    explicit AccResults()
    : sum{DataType()}
    , minimum{std::nullopt}
    , maximum{std::nullopt}
    , mean{std::nullopt}
    { }

    DataType sum;
    std::optional<DataType> minimum;
    std::optional<DataType> maximum;
    std::optional<DataType> mean;
};

template <IsAccumulable DataType>
requires std::is_copy_constructible_v<DataType>
class Accumulator final : public BaseClass<AccResults<DataType>>
{
public:
    explicit Accumulator(std::vector<DataType>&& data, AccType accType)
    : data_{std::move(data)}
    , accType_{accType}
    { }

private:
    void resetData() const override { }

    void FOR_ITER(const std::function<void(const DataType&)>& dataCallback) const
    {
        for (const DataType& item : data_)
        {
            dataCallback(item);
        }
    }

    template <typename AccumulatorSet>
    void FOR_ITER_ON_ACC(AccumulatorSet& acc) const
    {
        FOR_ITER([&acc](const DataType& value) { acc(value); });
    }

    AccResults<DataType> executeSTL() const override
    {
        AccResults<DataType> results;
        results.sum = std::accumulate(
            std::make_move_iterator(data_.begin()),
            std::make_move_iterator(data_.end()),
            std::move(results.sum),
            [](DataType&& sum, const DataType& value)
            {
                sum += value;
                return std::move(sum);
            });

        if (accType_ == AccType::SumAndExtremes || accType_ == AccType::DoItAll)
        {
            results.minimum = *std::min_element(data_.begin(), data_.end());
            results.maximum = *std::max_element(data_.begin(), data_.end());
        }
        if (accType_ == AccType::SumAndMean || accType_ == AccType::DoItAll)
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
            case AccType::SumOnly:
            {
                accumulator_set<DataType, stats<tag::sum>> acc1;
                FOR_ITER_ON_ACC(acc1);
                results.sum = sum(acc1);
                return results;
            }
            case AccType::SumAndExtremes:
            {
                accumulator_set<DataType,
                    stats<tag::sum, tag::min, tag::max>> acc2;
                FOR_ITER_ON_ACC(acc2);
                results.sum = sum(acc2);
                results.minimum = min(acc2);
                results.maximum = max(acc2);
                return results;
            }
            case AccType::SumAndMean:
            {
                accumulator_set<DataType,
                    stats<tag::sum, tag::mean>> acc3;
                FOR_ITER_ON_ACC(acc3);
                results.sum = sum(acc3);
                results.mean = mean(acc3);
                return results;
            }
            case AccType::DoItAll:
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

        if (accType_ == AccType::SumOnly || accType_ == AccType::SumAndMean)
        {
            FOR_ITER([&results](const DataType& value) { results.sum += value; });
        }
        else // AccType::SumAndExtremes, AccType::DoItAll
        {
            results.minimum = *data_.begin();
            results.maximum = *data_.begin();
            FOR_ITER([&results](const DataType& value)
            {
                results.sum += value;
                if (value < results.minimum)
                    results.minimum = value;
                else if (value > results.maximum)
                    results.maximum = value;
            });
        }

        if (accType_ == AccType::SumAndMean || accType_ == AccType::DoItAll)
        {
            results.mean = (results.sum / data_.size());
        }
        return results;
    }

    const std::vector<DataType> data_;
    const AccType accType_;
};

} // namespace src::Algorithms
