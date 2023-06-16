#ifndef D2533A66_36D1_4A39_8AF2_270F9AB90142
#define D2533A66_36D1_4A39_8AF2_270F9AB90142

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <mkl.h>

namespace Moru
{
    enum class Distribution
    {
        NORMAL,
        BETA,
        LOGNORMAL,
        UNIFORM,
        WEIBULL,
        NONE,
    };

    class Sampler
    {
    public:
        VSLStreamStatePtr stream_;
        std::vector<double> elems_;
        int status_ = 0;

        std::size_t samples_ = 0;
        std::uint64_t seed_ = 0;
        Distribution dist_ = Distribution::NONE;

        double a_ = 0.0;
        double b_ = 0.0;
        double p_ = 0.0;
        double q_ = 0.0;
        double alpha_ = 0.0;
        double beta_ = 0.0;
        double sigma_ = 0.0;

        void generate()
        {
            if( seed_ == 0 )
            {
                const auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
                seed_ = ( ( timestamp >> 32 ) & 0xffffffff ) ^ ( timestamp & 0xffffffff );
                spdlog::info( "set_rng_seed(): Time-based RNG seed is set to {}", seed_ );
            }

            int status = vslNewStream( &stream_, VSL_BRNG_MT19937, seed_ );
            elems_.reserve( samples_ );

            switch( dist_ )
            {
            case Distribution::NORMAL:
                status_ = vdRngGaussian( VSL_RNG_METHOD_UNIFORM_STD, stream_, samples_, elems_.data(), a_, sigma_ );
                break;

            case Distribution::BETA:
                status_ = vdRngBeta( VSL_RNG_METHOD_UNIFORM_STD, stream_, samples_, elems_.data(), p_, q_, a_, beta_ );
                break;

            case Distribution::LOGNORMAL:
                status_ = vdRngLognormal( VSL_RNG_METHOD_UNIFORM_STD, stream_, samples_, elems_.data(), a_, sigma_, b_, beta_ );
                break;

            case Distribution::UNIFORM:
                status_ = vdRngUniform( VSL_RNG_METHOD_UNIFORM_STD, stream_, samples_, elems_.data(), a_, b_ );
                break;

            case Distribution::WEIBULL:
                status_ = vdRngWeibull( VSL_RNG_METHOD_UNIFORM_STD, stream_, samples_, elems_.data(), alpha_, a_, beta_ );
                break;

            default:
                break;
            }
        }

        std::string log()
        {
            return "";
        };
    };

    inline void to_json( nlohmann::json& j, const Sampler& sampler )
    {
    }

    inline void from_json( const nlohmann::json& j, Sampler& sampler )
    {
        if( j.contains( "samples" ) )
            j.at( "samples" ).get_to( sampler.samples_ );

        if( j.contains( "seed" ) )
            j.at( "seed" ).get_to( sampler.seed_ );

        if( j.contains( "distribution" ) )
        {
            std::string dist_str = j.at( "distribution" ).template get<std::string>();

            if( dist_str.compare( "normal" ) )
                sampler.dist_ = Distribution::NORMAL;
            else if( dist_str.compare( "beta" ) )
                sampler.dist_ = Distribution::BETA;
            else if( dist_str.compare( "lognormal" ) )
                sampler.dist_ = Distribution::LOGNORMAL;
            else if( dist_str.compare( "uniform" ) )
                sampler.dist_ = Distribution::UNIFORM;
            else if( dist_str.compare( "weibull" ) )
                sampler.dist_ = Distribution::WEIBULL;
            else
                spdlog::error( "error" );
        }

        if( j.contains( "a" ) )
            j.at( "a" ).get_to( sampler.a_ );

        if( j.contains( "b" ) )
            j.at( "b" ).get_to( sampler.b_ );

        if( j.contains( "p" ) )
            j.at( "p" ).get_to( sampler.p_ );

        if( j.contains( "q" ) )
            j.at( "q" ).get_to( sampler.q_ );

        if( j.contains( "alpha" ) )
            j.at( "alpha" ).get_to( sampler.alpha_ );

        if( j.contains( "beta" ) )
            j.at( "beta" ).get_to( sampler.beta_ );

        if( j.contains( "sigma" ) )
            j.at( "sigma" ).get_to( sampler.sigma_ );
    }
} // namespace Moru

#endif /* D2533A66_36D1_4A39_8AF2_270F9AB90142 */
