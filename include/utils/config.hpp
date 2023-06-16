#ifndef C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83
#define C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <nlohmann/json.hpp>

#include "components/code.hpp"
#include "components/input.hpp"
#include "components/workflow.hpp"

#include "modules/sampler.hpp"

namespace Moru
{
    class Config
    {
    public:
        std::string title;
        std::string author;
        std::string email;
        std::string description;

        std::vector<Code> codes;
        std::vector<Input> inputs;
        std::vector<Sampler> samplers;
        std::vector<Workflow> workflows;
    };

    // NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, title, author, email, description)

    inline void to_json( nlohmann::json& j, const Config& config )
    {
    }

    inline void from_json( const nlohmann::json& j, Config& config )
    {
        if( j.contains( "title" ) )
            j.at( "title" ).get_to( config.title );

        if( j.contains( "author" ) )
            j.at( "author" ).get_to( config.author );

        if( j.contains( "email" ) )
            j.at( "email" ).get_to( config.email );

        if( j.contains( "description" ) )
            j.at( "description" ).get_to( config.description );

        if( j.contains( "codes" ) )
            j.at( "codes" ).get_to<std::vector<Code>>( config.codes );

        if( j.contains( "inputs" ) )
            j.at( "inputs" ).get_to<std::vector<Input>>( config.inputs );

        if( j.contains( "samplers" ) )
            j.at( "samplers" ).get_to<std::vector<Sampler>>( config.samplers );
    }
} // namespace Moru

#endif /* C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83 */
