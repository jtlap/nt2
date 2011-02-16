#include <iostream>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
//#include <nt2/include/functions/madd.hpp>

using namespace std;

int main()
{
  nt2::simd::pack<float> x(5.321f);
  cout << x << std::endl;
  cout << nt2::type_id<nt2::meta::hierarchy_of< nt2::simd::pack<float> >::type>() << "\n";

  nt2::simd::pack<float,8> y(5.321f);
  cout << y << std::endl;
  cout << nt2::type_id<nt2::meta::hierarchy_of< nt2::simd::pack<float,8> >::type>() << "\n";

  cout << nt2::type_id<nt2::meta::primitive_of< nt2::simd::native<int,nt2::tag::sse_> >::type>() << "\n";
  cout << nt2::type_id<nt2::meta::factory_of< nt2::simd::native<int,nt2::tag::sse_> >::type>() << "\n";

  cout << nt2::type_id< boost::mpl::
          apply< nt2::meta::factory_of< nt2::simd::native<int,nt2::tag::sse_> >::type
                , double >::type
                      >() << "\n";

  cout << nt2::type_id<nt2::meta::as_integer< nt2::simd::native<double,nt2::tag::sse_> >::type>() << "\n";

  //typedef nt2::meta::primitive_of<std::ostream>::type po;
}
