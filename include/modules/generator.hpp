#ifndef E988D16B_2F30_4296_91B7_BD502DD0F8D9
#define E988D16B_2F30_4296_91B7_BD502DD0F8D9

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>
#include <filesystem>
#include <fstream>

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "components/input.hpp"
#include "modules/sampler.hpp"

namespace Moru
{
    class Location
    {
    public:
        std::size_t line_;
        std::size_t word_;
    };

    class Generator
    {
    public:
        std::string name_;
        std::string base_;
        std::string sampler_;
        std::vector<Location> locations_;
        std::string expression_;

        Input base_input_;
        Distribution distribution_;

    private:
        std::string replace()
        {
            std::ifstream f( base_input_.file_, std::ios::in | std::ios::binary );
            std::string line;
            std::string result_string;
            std::size_t line_number = 1;

            while( std::getline( f, line ) )
            {
                spdlog::info( "[{}] {}", line_number, line );

                result_string.append( line );
                line_number++;
            }
            return result_string;
        }

    public:
        std::string generate()
        {
            return replace();
        }
    };

    inline void to_json( nlohmann::json& json, const Location& location )
    {
    }

    inline void from_json( const nlohmann::json& json, Location& location )
    {
        if( json.contains( "line" ) )
            json.at( "line" ).get_to( location.line_ );

        if( json.contains( "word" ) )
            json.at( "word" ).get_to( location.word_ );
    }

    inline void to_json( nlohmann::json& json, const Generator& generator )
    {
    }

    inline void from_json( const nlohmann::json& json, Generator& generator )
    {
        if( json.contains( "name" ) )
            json.at( "name" ).get_to( generator.name_ );

        if( json.contains( "sampler" ) )
            json.at( "sampler" ).get_to( generator.sampler_ );

        if( json.contains( "base" ) )
            json.at( "base" ).get_to( generator.base_ );

        if( json.contains( "locations" ) )
            json.at( "locations" ).get_to<std::vector<Location>>( generator.locations_ );

        if( json.contains( "expression" ) )
            json.at( "expression" ).get_to( generator.expression_ );
    }

} // namespace Moru

#endif /* E988D16B_2F30_4296_91B7_BD502DD0F8D9 */
