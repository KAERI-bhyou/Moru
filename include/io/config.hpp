#ifndef C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83
#define C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <boost/process.hpp>
#include <boost/json.hpp>

#include "component/code.hpp"
#include "component/input.hpp"
#include "component/job.hpp"

namespace Moru
{
    class Config
    {
    public:
        std::string title;
        std::string author;
        std::string email;
        std::string description;

        std::vector<Job> jobs_;
        std::vector<Code> codes;
        std::vector<Input> inputs;
        std::vector<Workflow> workflows;
    };

    template <class T>
    void extract( boost::json::object const& obj, T& t, boost::json::string_view key )
    {
        t = boost::json::value_to<T>( obj.at( key ) );
    }

    Config tag_invoke( boost::json::value_to_tag<Config>, boost::json::value const& jv )
    {
        Config c;
        boost::json::object const& obj = jv.as_object();

        if( obj.contains( "title" ) )
            extract( obj, c.title, "title" );
        if( obj.contains( "author" ) )
            extract( obj, c.author, "author" );
        if( obj.contains( "email" ) )
            extract( obj, c.email, "email" );
        if( obj.contains( "description" ) )
            extract( obj, c.description, "description" );

        return c;
    }
} // namespace Moru

#endif /* C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83 */
