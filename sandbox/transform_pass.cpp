#include <boost/proto/debug.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/optimize.hpp>

int main()
{
    using boost::simd::pack;
    const pack<float> a, b, c, d;

    boost::proto::display_expr(
      boost::simd::optimize
      (
        a + b * (a + b * (a + b * (a + b * c)))
      + b * (b * (b * (b * c + a) + a) + a) + a
      )
    );
}
