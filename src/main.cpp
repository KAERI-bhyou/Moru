#include <iostream>
#include <spdlog/spdlog.h>
#include "io/config.hpp"
#include "boost/program_options.hpp"

using Json = nlohmann::json;

std::string arg_parse( int, char*[] );

int main( int argc, char* argv[] )
{
    spdlog::info( "First Run" );
    std::string filename = arg_parse( argc, argv );

    Maru::Config config;

    auto yaml = fs::current_path() / filename;

    std::ifstream ifs( filename );

    Json json = Json::parse( ifs, nullptr, true, true );
    auto c = json.get<Maru::Config>();

    std::cout << json;
}

std::string arg_parse( int argc, char* argv[] )
{
    namespace po = boost::program_options;

    po::options_description desc( "all options" );
    desc.add_options()( "input,i", po::value<std::string>()->default_value( "workflow-reference.json" ), "Input file name." )( "output,o", po::value<std::string>()->default_value( "output.log" ), "Output file name." )( "version,v", po::value<std::string>(), "0.1.0" )( "help,h", "produce help message" );

    po::variables_map vm;
    po::store( po::parse_command_line( argc, argv, desc ), vm );
    po::notify( vm );

    if( vm.count( "help" ) )
    {
        std::cout << desc << "\n";
        std::exit( -1 );
    }

    return vm[ "input" ].as<std::string>();
}