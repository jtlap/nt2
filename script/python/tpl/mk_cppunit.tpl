#define NT2_UNIT_MODULE "nt2 $self.tb_name$ toolbox - $self.name$ - $acts$ Mode"

#include <nt2/toolbox/$self.tb_name$/include/$self.name$.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of $self.tb_name$ component $self.name$ using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
//NT2_TEST_CASE_TPL ( $self.tb_name$,  (double)(nt2::uint64_t)(nt2::int64_t) 
//                          (float)(nt2::uint32_t)(nt2::int32_t)  
//                          (nt2::uint16_t)(nt2::int16_t)         
//                          (nt2::uint8_t)(nt2::int8_t)
//                          (bool)
//                  )
//{
//  using nt2::$self.name$;
//  using nt2::functors::$self.name$_;
//
//  NT2_TEST( (boost::is_same<typename nt2::meta::call<$self.tb_name$_($self.const_type_list$)>::type,
//                            typename nt2::meta::floating<$self.const_type_list$>::type
//                            >::value)
//          );
//}

