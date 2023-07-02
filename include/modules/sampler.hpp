#ifndef D2533A66_36D1_4A39_8AF2_270F9AB90142
#define D2533A66_36D1_4A39_8AF2_270F9AB90142

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include <mkl.h>
namespace Moru
{
    enum class DistributionType
    {
        NORMAL,
        BETA,
        LOGNORMAL,
        UNIFORM,
        WEIBULL,
        MANUAL,
        NONE,
    };

    class Distribution
    {
    public:
        std::string name_;
        DistributionType type_ = DistributionType::NONE;

        std::size_t samples_ = 0;
        std::uint32_t seed_ = 0;

        VSLStreamStatePtr stream_;
        int status_ = 0;

        double a_ = 0.0;
        double b_ = 0.0;
        double p_ = 0.0;
        double q_ = 0.0;
        double alpha_ = 0.0;
        double beta_ = 0.0;
        double sigma_ = 0.0;

        std::vector<double> values_;

        void generate()
        {
            // int status = vslNewStream( &stream_, VSL_BRNG_PHILOX4X32X10, seed_ );
            int status = vslNewStreamEx( &stream_, VSL_BRNG_PHILOX4X32X10, 2, &seed_ );

            values_.resize( samples_ );

            if( seed_ == 0 )
            {
                const auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
                seed_ = ( ( timestamp >> 32 ) & 0xffffffff ) ^ ( timestamp & 0xffffffff );
                spdlog::info( "set_rng_seed(): Time-based RNG seed is set to {}", seed_ );
            }

            switch( type_ )
            {
            case DistributionType::NORMAL:
                status_ = vdRngGaussian( VSL_RNG_METHOD_UNIFORM_STD, stream_, samples_, values_.data(), a_, sigma_ );
                break;

            case DistributionType::BETA:
                status_ = vdRngBeta( VSL_RNG_METHOD_UNIFORM_STD, stream_, samples_, values_.data(), p_, q_, a_, beta_ );
                break;

            case DistributionType::LOGNORMAL:
                status_ = vdRngLognormal( VSL_RNG_METHOD_UNIFORM_STD, stream_, samples_, values_.data(), a_, sigma_, b_, beta_ );
                break;

            case DistributionType::UNIFORM:
                status_ = vdRngUniform( VSL_RNG_METHOD_UNIFORM_STD_ACCURATE, stream_, samples_, values_.data(), a_, b_ );
                break;

            case DistributionType::WEIBULL:
                status_ = vdRngWeibull( VSL_RNG_METHOD_UNIFORM_STD, stream_, samples_, values_.data(), alpha_, a_, beta_ );
                break;

            case DistributionType::MANUAL:
                break;

            default:
                break;
            }
        }
    };

    class Sampler
    {
    public:
        std::size_t samples_ = 0;
        std::uint64_t seed_ = 0;
        std::vector<Distribution> distributions_;

        Sampler() = default;
        ~Sampler() = default;

        Sampler( const Sampler& sampler )
            : samples_{ sampler.samples_ },
              seed_{ sampler.seed_ },
              distributions_{ sampler.distributions_ }
        {
            spdlog::debug( "Sampler( const Sampler& sampler )" );
        }

        Sampler( Sampler&& sampler )
            : samples_{ sampler.samples_ },
              seed_{ sampler.seed_ },
              distributions_{ sampler.distributions_ }
        {
            spdlog::debug( "Sampler( Sampler&& sampler )" );
        }

        void setup()
        {
            for( auto&& distribution : distributions_ )
            {
                distribution.samples_ = samples_;
                distribution.seed_ = seed_;
            }
        }

        std::string log()
        {
            return "";
        };
    };

    inline void to_json( nlohmann::json& j, const Distribution& distribution )
    {
    }

    inline void from_json( const nlohmann::json& j, Distribution& distribution )
    {
        if( j.contains( "name" ) )
            j.at( "name" ).get_to( distribution.name_ );

        if( j.contains( "distribution" ) )
        {
            std::string dist_str = j.at( "distribution" ).template get<std::string>();

            if( dist_str == "normal" )
                distribution.type_ = DistributionType::NORMAL;
            else if( dist_str == "beta" )
                distribution.type_ = DistributionType::BETA;
            else if( dist_str == "lognormal" )
                distribution.type_ = DistributionType::LOGNORMAL;
            else if( dist_str == "uniform" )
                distribution.type_ = DistributionType::UNIFORM;
            else if( dist_str == "weibull" )
                distribution.type_ = DistributionType::WEIBULL;
            else if( dist_str == "manual" )
                distribution.type_ = DistributionType::MANUAL;
            else
                spdlog::error( "error" );
        }

        if( j.contains( "a" ) )
            j.at( "a" ).get_to( distribution.a_ );

        if( j.contains( "b" ) )
            j.at( "b" ).get_to( distribution.b_ );

        if( j.contains( "p" ) )
            j.at( "p" ).get_to( distribution.p_ );

        if( j.contains( "q" ) )
            j.at( "q" ).get_to( distribution.q_ );

        if( j.contains( "alpha" ) )
            j.at( "alpha" ).get_to( distribution.alpha_ );

        if( j.contains( "beta" ) )
            j.at( "beta" ).get_to( distribution.beta_ );

        if( j.contains( "sigma" ) )
            j.at( "sigma" ).get_to( distribution.sigma_ );

        if( j.contains( "values" ) )
            j.at( "values" ).get_to( distribution.values_ );
    }

    inline void to_json( nlohmann::json& j, const Sampler& sampler )
    {
    }

    inline void from_json( const nlohmann::json& j, Sampler& sampler )
    {
        if( j.contains( "samples" ) )
            j.at( "samples" ).get_to( sampler.samples_ );

        if( j.contains( "seed" ) )
            j.at( "seed" ).get_to( sampler.seed_ );

        if( j.contains( "distributions" ) )
            j.at( "distributions" ).get_to<std::vector<Distribution>>( sampler.distributions_ );

        sampler.setup();
    }
} // namespace Moru

#endif /* D2533A66_36D1_4A39_8AF2_270F9AB90142 */
