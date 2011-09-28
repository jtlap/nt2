#include <boost/proto/debug.hpp>
#include <boost/simd/sdk/dsl/recognition.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <nt2/include/functions/fma.hpp>
//#include <boost/simd/toolbox/arithmetic/recognition/fma.hpp>
#include <nt2/sdk/details/type_id.hpp>

int main()
{
    using boost::simd::pack;
    namespace proto = boost::proto;
    
    pack<float> a, b, c, d;
    
    proto::display_expr(
      boost::dispatch::meta::compile<
        boost::dispatch::meta::compute<boost::mpl::_1, boost::simd::tag::recognition_>
       // boost::simd::meta::recognition_<boost::mpl::_1>
      >()
      (
        //a + (b + (c + d))
      
        //a + b + c 
      
        a + b * (a + b * (a + b * (a + b * c)))
      + b * (b * (b * (b * c + a) + a) + a) + a
      )
    );
}
