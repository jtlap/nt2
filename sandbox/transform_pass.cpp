#include <boost/proto/debug.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <nt2/include/functions/fma.hpp>

//#include <boost/simd/sdk/dsl/recognition.hpp>
namespace boost { namespace simd { namespace tag
{
  struct recognition_ : dispatch::tag::formal_ {};
} } }

//#include <boost/simd/toolbox/arithmetic/recognition/fma.hpp>
#include <nt2/sdk/details/type_id.hpp>

int main()
{
    using boost::simd::pack;
    namespace proto = boost::proto;
    
    pack<float> a, b, c, d;
    
    proto::display_expr(
      boost::dispatch::meta::compute<boost::simd::tag::recognition_>()
      (
        //a + (b + (c + d))
      
        //a + b + c 
      
        a + b * (a + b * (a + b * (a + b * c)))
      + b * (b * (b * (b * c + a) + a) + a) + a
      )
    );
}
