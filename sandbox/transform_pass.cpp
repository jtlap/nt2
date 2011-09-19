#include <boost/proto/debug.hpp>
#include <boost/simd/sdk/dsl/recognition.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <nt2/include/functions/fma.hpp>

int main()
{
    using boost::simd::pack;
    namespace proto = boost::proto;
    
    pack<float> a, b, c, d;
    
    proto::display_expr(
      boost::dispatch::meta::compile<
        boost::simd::meta::recognition_<boost::mpl::_1>
      >()
      (
        a + b * (a + b * (a + b * (a + b * c)))
      + b * (b * (b * (b * c + a) + a) + a) + a
      )
    );
}
