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
#include "modules/generator.hpp"

#include "utils/job.hpp"

namespace Moru
{
    class Config
    {
    public:
        std::string title;
        std::string author;
        std::string email;
        std::string description;

        Workflow workflow;

        std::vector<Code> codes;
        std::vector<Input> inputs;
        Sampler sampler;
        std::vector<Generator> generators;

        Config() = default;
        ~Config() = default;

        Config( const Config& config )
            : title{ config.title },
              author{ config.author },
              email{ config.email },
              description{ config.description },
              workflow{ config.workflow },
              codes{ config.codes },
              inputs{ config.inputs },
              sampler{ config.sampler },
              generators{ config.generators }
        {
            std::cout << "Config( const Config& config )" << std::endl;
        }

        Config( Config&& config )
            : title{ config.title },
              author{ config.author },
              email{ config.email },
              description{ config.description },
              workflow{ config.workflow },
              codes{ config.codes },
              inputs{ config.inputs },
              sampler{ config.sampler },
              generators{ config.generators }
        {
            std::cout << "Config( Config&& config )" << std::endl;
        }
    };

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

        if( j.contains( "sampler" ) )
            j.at( "sampler" ).get_to( config.sampler );

        if( j.contains( "generators" ) )
            j.at( "generators" ).get_to<std::vector<Generator>>( config.generators );

        if( j.contains( "workflow" ) )
            j.at( "workflow" ).get_to( config.workflow );
    }
} // namespace Moru

#endif /* C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83 */
