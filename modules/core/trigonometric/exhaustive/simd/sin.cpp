////////////////////////////////////////////////////////////////////////
// exhaustive test in simd mode for functor nt2::sin
////////////////////////////////////////////////////////////////////////
#include <nt2/include/functions/sin.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/successor.hpp>

#include <nt2/include/constants/real.hpp>

#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <iostream>

typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

#include <nt2/modules/trigonometric/exhaustive/simd/sin.float.hpp>
#include <nt2/modules/trigonometric/exhaustive/simd/sin.nt2_int32_t.hpp>
#include <nt2/modules/trigonometric/exhaustive/simd/sin.nt2_uint32_t.hpp>


int main(){
{
  //place your test call for float here
  //place your test call for nt2::int32_t here
  //place your test call for nt2::uint32_t here
  return 0;
}

