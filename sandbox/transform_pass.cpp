#include <boost/proto/debug.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/include/functions/fma.hpp>

int main()
{
    using nt2::simd::pack;
    namespace proto = boost::proto;
    
    pack<float> a, b, c, d;
    
    proto::display_expr(
      nt2::meta::compile<
        nt2::meta::recognition_<boost::mpl::_1>
      >()
      (
        a + b * (a + b * (a + b * (a + b * c)))
      + b * (b * (b * (b * c + a) + a) + a) + a
      )
    );
}
