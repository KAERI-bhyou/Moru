#ifndef E677928D_DCF2_438D_8A2B_F0C62188B82C
#define E677928D_DCF2_438D_8A2B_F0C62188B82C

#include <atomic>
#include <random>
#include <vector>
#include <thread>
#include <string>
#include <execution>

#include <oneapi/tbb/parallel_for_each.h>
#include <oneapi/tbb/task_arena.h>
#include <oneapi/tbb/task_group.h>

#include "modules/sampler.hpp"
#include "utils/config.hpp"
#include "utils/job.hpp"

namespace Moru
{
    class Worker
    {
    public:
        std::vector<Job> jobs;

    public:
        void uncertainty_quantification( Config& config )
        {
            for( auto& distribution : config.sampler.distributions_ )
            {
                distribution.generate();
            }

            std::vector<std::string> params;
            for( auto& generator : config.generators )
            {
                params.push_back( generator.name_ );
            }

            for( int i = 0; i < config.sampler.samples_; ++i )
            {
                auto base_dir = config.workflow.work_dir_;
                auto case_num = std::filesystem::path( fmt::format( "{}_{:04}", config.workflow.name_, i ) );
                auto working_dir = base_dir / case_num;

                spdlog::info( "[{:02}] Input generation for ({:^8})", i, fmt::join( params, "|" ) );

                std::vector<double> values;
                for( auto& generator : config.generators )
                {
                    for( auto& distribution : config.sampler.distributions_ )
                    {
                        if( generator.sampler_ == distribution.name_ )
                        {
                            values.push_back( distribution.values_[ i ] );
                            break;
                        }
                    }
                }

                spdlog::info( "[{:02}] Random values:       ({:8f})", i, fmt::join( values, "|" ) );

                Job job( i, config.codes[ 0 ], config.inputs, working_dir );
                job.prefare();
                jobs.push_back( job );
            }
        }

        void execute()
        {
            std::for_each(
                std::execution::seq,
                std::begin( jobs ), std::end( jobs ),
                []( Job& job )
                {
                    job.run();
                } );
        }

        void compile( Config& config )
        {
            auto type = config.workflow.type_;
            if( type == "uncertainty_quantification" )
            {
                uncertainty_quantification( config );
            }
            else
            {
            }

            execute();
        }
    };
} // namespace Moru

#endif /* E677928D_DCF2_438D_8A2B_F0C62188B82C */
