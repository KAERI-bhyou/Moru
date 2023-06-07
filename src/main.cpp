#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/json.hpp>
#include <boost/program_options.hpp>

#include "utils/config.hpp"

std::string arg_parse( int, char*[] );

int main( int argc, char* argv[] )
{
    namespace json = boost::json;

    std::string filename = arg_parse( argc, argv );

    auto ss = std::ostringstream{};
    std::ifstream input_file( filename );
    if( !input_file.is_open() )
    {
        std::cerr << "Could not open the file - '"
                  << filename << "'" << std::endl;
        exit( EXIT_FAILURE );
    }
    ss << input_file.rdbuf();

    json::error_code ec;
    json::monotonic_resource mr;
    json::parse_options opt;
    opt.allow_comments = true;
    opt.allow_trailing_commas = true;

    json::value jv = json::parse( ss.str(), ec, &mr, opt );

    Moru::Config config( json::value_to<Moru::Config>( jv ) );

    std::cout << jv << std::endl;
    std::cout << ec.what() << std::endl;
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