#ifndef AFA5333A_351F_4367_BE53_AE81EF48D454
#define AFA5333A_351F_4367_BE53_AE81EF48D454

#include <filesystem>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace Moru
{
    class Code
    {
    public:
        std::string name;
        std::filesystem::path executable;
        std::vector<std::filesystem::path> dependencies;
        int np;
    };

    inline void to_json( nlohmann::json& json, const Code& code )
    {
    }

    inline void from_json( const nlohmann::json& json, Code& code )
    {
        if( json.contains( "name" ) )
            json.at( "name" ).get_to( code.name );

        if( json.contains( "executable" ) )
            json.at( "executable" ).get_to( code.executable );

        if( json.contains( "dependencies" ) )
            json.at( "dependencies" ).get_to<std::vector<std::filesystem::path>>( code.dependencies );

        if( json.contains( "np" ) )
            json.at( "np" ).get_to( code.np );
    }
} // namespace Moru

#endif /* AFA5333A_351F_4367_BE53_AE81EF48D454 */
