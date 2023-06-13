#ifndef D2533A66_36D1_4A39_8AF2_270F9AB90142
#define D2533A66_36D1_4A39_8AF2_270F9AB90142

#include <mkl.h>

enum class Distribution
{
    NORMAL,
    BETA,
    LOGNORMAL,
};

class NormalDist
{
};

class BetaDist
{
};

class LogNormalDist
{
public:
    void run()
    {
        VSLStreamStatePtr stream_;
        double a[ 1 ] = { 0.0 };
        auto status = vdRngGaussian( VSL_RNG_METHOD_UNIFORM_STD, stream_, 1, a, 1.0, 1.0 );
    }
};

#endif /* D2533A66_36D1_4A39_8AF2_270F9AB90142 */
