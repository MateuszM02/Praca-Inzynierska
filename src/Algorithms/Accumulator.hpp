#pragma once

#include "Base.hpp"
#include "../Wrappers/MixedWrappers.hpp"

#include <numeric>
#include <optional>

// boost::accumulators::accumulators wraz z metodami min, max, sum, mean
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/sum.hpp>

using namespace src::Wrappers;

namespace src::Algorithms
{

enum AccType
{
    SumOnly,
    SumAndMean,
    SumAndExtremes,
    DoItAll
};

struct AccResults
{
    unsigned int sum;
    std::optional<unsigned int> minimum;
    std::optional<unsigned int> maximum;
    std::optional<double> mean;
};

template <typename DataType>
class Accumulator final : public BaseClass<DataType, AccResults>
{

using DataVector = std::vector<AccumulableWrapper<DataType>>;

public:
    Accumulator(DataVector data, AccType accType)
    : data_(std::move(data))
    , accType_(accType)
    { }

private:
    void resetData() override { }

    void FOR_ITER(const std::function<void(AccumulableWrapper<DataType>)>& f)
    {
        for (auto it = data_.begin(); it != data_.end(); ++it)
        {
            f(*it);
        }
    }

    template <typename StatsTags>
    void FOR_ITER_ON_ACC(boost::accumulators::accumulator_set<AccumulableWrapper<DataType>, StatsTags>& acc)
    {
        FOR_ITER([&acc](const AccumulableWrapper<DataType>& wrapper) { acc(wrapper); });
    }

    AccResults executeSTL() override
    {
        AccResults results;
        AccumulableWrapper<DataType> accSum =
            std::accumulate(data_.begin(), data_.end(), AccumulableWrapper<DataType>());
        results.sum = accSum.getValue();

        if (accType_ == SumAndExtremes || accType_ == DoItAll)
        {
            results.minimum = std::min_element(data_.begin(), data_.end())->getValue();
            results.maximum = std::max_element(data_.begin(), data_.end())->getValue();
        }
        if (accType_ == SumAndMean || accType_ == DoItAll)
        {
            results.mean = (accSum / data_.size()).getValue();
        }
        return results;
    }

    AccResults executeBoost() override
    {
        using namespace boost::accumulators;
        AccResults results;
        
        switch (accType_)
        {
            case SumOnly:
            {
                accumulator_set<AccumulableWrapper<DataType>, stats<tag::sum>> acc1;
                FOR_ITER_ON_ACC(acc1);
                results.sum = sum(acc1).getValue();
                return results;
            }
            case SumAndExtremes:
            {
                accumulator_set<AccumulableWrapper<DataType>,
                    stats<tag::sum, tag::min, tag::max>> acc2;
                FOR_ITER_ON_ACC(acc2);
                results.sum = sum(acc2).getValue();
                results.minimum = min(acc2).getValue();
                results.maximum = max(acc2).getValue();
                return results;
            }
            case SumAndMean:
            {
                accumulator_set<AccumulableWrapper<DataType>,
                    stats<tag::sum, tag::mean>> acc3;
                FOR_ITER_ON_ACC(acc3);
                results.sum = sum(acc3).getValue();
                results.mean = mean(acc3).getValue();
                return results;
            }
            case DoItAll:
            {
                accumulator_set<AccumulableWrapper<DataType>,
                    stats<tag::sum, tag::min, tag::max, tag::mean>> acc4;
                FOR_ITER_ON_ACC(acc4);
                results.sum = sum(acc4).getValue();
                results.minimum = min(acc4).getValue();
                results.maximum = max(acc4).getValue();
                results.mean = mean(acc4).getValue();
                return results;
            }
            default:
                throw std::invalid_argument("Zly typ enuma AccType!");
        }
        return results;
    }

    AccResults executeSimple() override
    {
        AccResults results;
        AccumulableWrapper<DataType> accSum = AccumulableWrapper<DataType>();

        if (accType_ == SumOnly || accType_ == SumAndMean)
        {
            FOR_ITER([&accSum](const AccumulableWrapper<DataType>& wrapper) { accSum += wrapper; });
        }
        else // SumAndExtremes, DoItAll
        {
            results.minimum = data_.begin()->getValue();
            results.maximum = data_.begin()->getValue();
            FOR_ITER([&results, &accSum](const AccumulableWrapper<DataType>& wrapper)
            {
                accSum += wrapper;
                const unsigned int value = static_cast<unsigned int>(wrapper.getValue());
                if (value < results.minimum)
                    results.minimum = value;
                else if (value > results.maximum)
                    results.maximum = value;
            });
        }
        results.sum = accSum.getValue();

        if (accType_ == SumAndMean || accType_ == DoItAll)
        {
            results.mean = (accSum / data_.size()).getValue();
        }
        return results;
    }

public:
    const DataVector data_;
    const AccType accType_;
};

} // namespace src::Algorithms
