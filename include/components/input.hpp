#ifndef FE085B95_3A5E_463B_AAE5_012E944CB9DC
#define FE085B95_3A5E_463B_AAE5_012E944CB9DC

#include <filesystem>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace Moru
{
    class Input
    {
    public:
        std::string name_;
        std::filesystem::path file_;
    };
    inline void to_json( nlohmann::json& json, const Input& input )
    {
    }

    inline void from_json( const nlohmann::json& json, Input& input )
    {
        if( json.contains( "name" ) )
            json.at( "name" ).get_to( input.name_ );

        if( json.contains( "file" ) )
            json.at( "file" ).get_to( input.file_ );
    }
} // namespace Moru

#endif /* FE085B95_3A5E_463B_AAE5_012E944CB9DC */
