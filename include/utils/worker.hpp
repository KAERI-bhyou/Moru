#ifndef E677928D_DCF2_438D_8A2B_F0C62188B82C
#define E677928D_DCF2_438D_8A2B_F0C62188B82C

#include <random>
#include <vector>

#include <oneapi/tbb/parallel_for_each.h>
#include <oneapi/tbb/task_arena.h>

namespace Moru
{
    class Worker
    {
    public:
        void worker()
        {
            using namespace oneapi;

            std::vector<int> is;

            for( int i = 0; i < 100; ++i )
                is.push_back( i );

            std::mt19937_64 eng{ std::random_device{}() };

            int maximum_degree_of_parallelism = 4;
            tbb::task_arena arena( maximum_degree_of_parallelism );

            arena.execute(
                [ & ]
                {
                    tbb::parallel_for_each(
                        std::begin( is ), std::end( is ),
                        [ & ]( int ii )
                        {
                            std::uniform_int_distribution<> dist{ 1, 5 };
                            auto sec = dist( eng );
                            int worker_index = tbb::this_task_arena::current_thread_index();
                            std::this_thread::sleep_for( std::chrono::seconds{ sec } );
                        } );
                } );
        }
    };
} // namespace Moru

#endif /* E677928D_DCF2_438D_8A2B_F0C62188B82C */
