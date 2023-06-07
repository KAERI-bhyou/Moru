#include "utils/config.hpp"

Moru::Config tag_invoke( boost::json::value_to_tag<Moru::Config>, boost::json::value const& jv )
{
    Moru::Config c;
    boost::json::object const& obj = jv.as_object();

    if( obj.contains( "title" ) )
        Moru::extract( obj, c.title, "title" );
    if( obj.contains( "author" ) )
        Moru::extract( obj, c.author, "author" );
    if( obj.contains( "email" ) )
        Moru::extract( obj, c.email, "email" );
    if( obj.contains( "description" ) )
        Moru::extract( obj, c.description, "description" );

    return c;
}