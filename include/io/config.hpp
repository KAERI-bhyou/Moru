#ifndef C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83
#define C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <boost/process.hpp>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "component/code.hpp"
#include "component/input.hpp"
#include "component/job.hpp"

namespace bp = boost::process;
namespace fs = std::filesystem;
using Json = nlohmann::json;

namespace Maru
{
    class Config
    {
        std::string title;
        std::string author;
        std::string email;
        std::string description;

        std::vector<Job> jobs_;
        std::vector<Code> codes;
        std::vector<Input> inputs;
        std::vector<Workflow> workflows;

    public:
    };

    void from_json( const Json& j, Config& c )
    {
    }

    void to_json( Json& j, const Config& c )
    {
    }
} // namespace Maru

#endif /* C5FDD5D9_FCF3_42E2_8C67_4E2B06DC5D83 */
