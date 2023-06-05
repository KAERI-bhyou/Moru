#ifndef B42C3DB2_1748_414E_9796_76437BD19559
#define B42C3DB2_1748_414E_9796_76437BD19559

#include <string>
#include <vector>
#include "component/code.hpp"
#include "component/input.hpp"
#include "component/workflow.hpp"

class Job
{
public:
    std::string name;
    std::vector<std::string> codes;
    std::vector<std::string> inputs;
    std::vector<std::string> workflows;
};


#endif /* B42C3DB2_1748_414E_9796_76437BD19559 */
