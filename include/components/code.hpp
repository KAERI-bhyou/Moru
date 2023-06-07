#ifndef AFA5333A_351F_4367_BE53_AE81EF48D454
#define AFA5333A_351F_4367_BE53_AE81EF48D454

#include <string>
#include <vector>

#include <boost/json.hpp>

class Code
{
public:
    std::string name;
    std::string binary;
    std::vector<std::string> dependencies;
    int np;
    std::string host;
};

#endif /* AFA5333A_351F_4367_BE53_AE81EF48D454 */
