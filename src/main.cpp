#include <iostream>
#include <string_view>
#include <spdlog/spdlog.h>
#include <mpi.h>

#include "utils/config.hpp"
#include "utils/worker.hpp"

#include "modules/sampler.hpp"

int main( int argc, char* argv[] )
{
    MPI_Init( &argc, &argv );

    int rank, size;
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    const std::vector<std::string_view> args( argv + 1, argv + argc );
    std::string filename{};

    for( auto i = 0; i < argc - 1; ++i )
    {
        if( args[ i ] == "-i" || args[ i ] == "--input" )
        {
            filename = args[ i + 1 ];
        }
        if( args[ i ] == "-h" || args[ i ] == "--help" )
        {
            std::cout << "Help message." << '\n';
            std::exit( 0 );
        }
    }

    std::ifstream config_file( filename );

    nlohmann::json config_json;

    try
    {
        config_json = nlohmann::json::parse( config_file, nullptr, true, true );
    }
    catch( nlohmann::json::exception& ec )
    {
        spdlog::error( "{}", ec.what() );
    }

    config_file.close();
    Moru::Config config = config_json;

    Moru::Worker worker;
    worker.compile( config );

    spdlog::info( "All calculation have been finished." );

    MPI_Finalize();

    return 0;
}
