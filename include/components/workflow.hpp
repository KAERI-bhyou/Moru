#ifndef FF18329F_5221_444A_8D3A_4023BB151234
#define FF18329F_5221_444A_8D3A_4023BB151234

#include <filesystem>
#include <string>

#include <nlohmann/json.hpp>
namespace Moru
{
    class Workflow
    {
    public:
        std::string name_;
        std::string type_;
        std::filesystem::path work_dir_;
    };

    inline void to_json( nlohmann::json& json, const Workflow& workflow )
    {
    }

    inline void from_json( const nlohmann::json& json, Workflow& workflow )
    {
        if( json.contains( "name" ) )
            json.at( "name" ).get_to( workflow.name_ );

        if( json.contains( "type" ) )
            json.at( "type" ).get_to( workflow.type_ );

        if( json.contains( "work_dir" ) )
            json.at( "work_dir" ).get_to( workflow.work_dir_ );
    }
} // namespace Moru

#endif /* FF18329F_5221_444A_8D3A_4023BB151234 */
