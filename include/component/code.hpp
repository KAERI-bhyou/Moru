#ifndef AFA5333A_351F_4367_BE53_AE81EF48D454
#define AFA5333A_351F_4367_BE53_AE81EF48D454

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class Code
{
public:
    std::string name;
    std::string binary;
    std::vector<std::string> dependencies;
    int np;
    std::string host;

    void from_json( const Json& j, Code& c )
    {
    }

    void to_json( Json& j, const Code& c )
    {
    }
};

#endif /* AFA5333A_351F_4367_BE53_AE81EF48D454 */
