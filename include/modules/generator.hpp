#ifndef E988D16B_2F30_4296_91B7_BD502DD0F8D9
#define E988D16B_2F30_4296_91B7_BD502DD0F8D9

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>
#include <filesystem>
#include <fstream>
#include <regex>

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <exprtk.hpp>

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
        double func( double& old_value, double& random_value )
        {
            using SymbolTable = exprtk::symbol_table<double>;
            using Expression = exprtk::expression<double>;
            using Parser = exprtk::parser<double>;

            auto expression = "o" + expression_;

            SymbolTable symbol_table;
            symbol_table.add_constants();
            symbol_table.add_variable( "o", old_value );
            symbol_table.add_variable( "x", random_value );

            Expression expression_object;
            expression_object.register_symbol_table( symbol_table );

            Parser parser;
            parser.compile( expression, expression_object );

            double new_value = expression_object.value();

            return new_value;
        }

        std::string replace()
        {
            std::ifstream f( base_input_.file_, std::ios::in | std::ios::binary );
            std::string line;
            std::string result_string;
            std::size_t line_number = 1;

            while( std::getline( f, line ) )
            {
                std::regex wordRegex( "\\b\\w+\\b" );
                std::sregex_iterator wordIter( line.begin(), line.end(), wordRegex );
                std::sregex_iterator endIter;


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
