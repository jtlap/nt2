//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - saturate_to/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 20/03/2011
/// 
#include <boost/simd/toolbox/ieee/include/functions/saturate_to.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp> 


NT2_TEST_CASE_TPL ( saturate_to_unsigned_int16,  (int16_t))
{
  
   using boost::simd::saturate_to;
   using boost::simd::tag::saturate_to_;
   using boost::simd::Valmax;
   using boost::simd::Valmin;
  NT2_TEST_ULP_EQUAL(1,           saturate_to<T>(1ull        ), 0);
  NT2_TEST_ULP_EQUAL(2,           saturate_to<T>(2ull        ), 0);
  NT2_TEST_ULP_EQUAL(6,           saturate_to<T>(6ull        ), 0);
  NT2_TEST_ULP_EQUAL(24,          saturate_to<T>(24ull       ), 0);
  NT2_TEST_ULP_EQUAL(120,         saturate_to<T>(120ull      ), 0); 
  NT2_TEST_ULP_EQUAL(720,         saturate_to<T>(720ull      ), 0);
  NT2_TEST_ULP_EQUAL(5040,        saturate_to<T>(5040ull     ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(40320ull    ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(362880ull   ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(3628800ull  ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(39916800ull ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(479001600ull), 0);

  NT2_TEST_ULP_EQUAL(1,           saturate_to<T>(1ll        ), 0);
  NT2_TEST_ULP_EQUAL(2,           saturate_to<T>(2ll        ), 0);
  NT2_TEST_ULP_EQUAL(6,           saturate_to<T>(6ll        ), 0);
  NT2_TEST_ULP_EQUAL(24,          saturate_to<T>(24ll       ), 0);
  NT2_TEST_ULP_EQUAL(120,         saturate_to<T>(120ll      ), 0); 
  NT2_TEST_ULP_EQUAL(720,         saturate_to<T>(720ll      ), 0);
  NT2_TEST_ULP_EQUAL(5040,        saturate_to<T>(5040ll     ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(40320ll    ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(362880ll   ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(3628800ll  ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(39916800ll ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(479001600ll), 0);

  NT2_TEST_ULP_EQUAL(-1,           saturate_to<T>(-1ll        ), 0);
  NT2_TEST_ULP_EQUAL(-2,           saturate_to<T>(-2ll        ), 0);
  NT2_TEST_ULP_EQUAL(-6,           saturate_to<T>(-6ll        ), 0);
  NT2_TEST_ULP_EQUAL(-24,          saturate_to<T>(-24ll       ), 0);
  NT2_TEST_ULP_EQUAL(-120,         saturate_to<T>(-120ll      ), 0); 
  NT2_TEST_ULP_EQUAL(-720,         saturate_to<T>(-720ll      ), 0);
  NT2_TEST_ULP_EQUAL(-5040,        saturate_to<T>(-5040ll     ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-40320ll    ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-362880ll   ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-3628800ll  ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-39916800ll ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-479001600ll), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( saturate_to_unsigned_uint16,  (uint16_t))
{
  
   using boost::simd::saturate_to;
   using boost::simd::tag::saturate_to_;
   using boost::simd::Valmax; 
  NT2_TEST_ULP_EQUAL(1,           saturate_to<T>(1ull        ), 0);
  NT2_TEST_ULP_EQUAL(2,           saturate_to<T>(2ull        ), 0);
  NT2_TEST_ULP_EQUAL(6,           saturate_to<T>(6ull        ), 0);
  NT2_TEST_ULP_EQUAL(24,          saturate_to<T>(24ull       ), 0);
  NT2_TEST_ULP_EQUAL(120,         saturate_to<T>(120ull      ), 0); 
  NT2_TEST_ULP_EQUAL(720,         saturate_to<T>(720ull      ), 0);
  NT2_TEST_ULP_EQUAL(5040,        saturate_to<T>(5040ull     ), 0);
  NT2_TEST_ULP_EQUAL(40320,       saturate_to<T>(40320ull    ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(362880ull   ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(3628800ull  ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(39916800ull ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(479001600ull), 0);

  NT2_TEST_ULP_EQUAL(1,           saturate_to<T>(1ll        ), 0);
  NT2_TEST_ULP_EQUAL(2,           saturate_to<T>(2ll        ), 0);
  NT2_TEST_ULP_EQUAL(6,           saturate_to<T>(6ll        ), 0);
  NT2_TEST_ULP_EQUAL(24,          saturate_to<T>(24ll       ), 0);
  NT2_TEST_ULP_EQUAL(120,         saturate_to<T>(120ll      ), 0); 
  NT2_TEST_ULP_EQUAL(720,         saturate_to<T>(720ll      ), 0);
  NT2_TEST_ULP_EQUAL(5040,        saturate_to<T>(5040ll     ), 0);
  NT2_TEST_ULP_EQUAL(40320,       saturate_to<T>(40320ll    ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(362880ll   ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(3628800ll  ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(39916800ll ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(479001600ll), 0);

} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( saturate_to_unsigned_int8,  (int8_t))
{
  
   using boost::simd::saturate_to;
   using boost::simd::tag::saturate_to_;
   using boost::simd::Valmax;
   using boost::simd::Valmin;
  NT2_TEST_ULP_EQUAL(1,           saturate_to<T>(1ull        ), 0);
  NT2_TEST_ULP_EQUAL(2,           saturate_to<T>(2ull        ), 0);
  NT2_TEST_ULP_EQUAL(6,           saturate_to<T>(6ull        ), 0);
  NT2_TEST_ULP_EQUAL(24,          saturate_to<T>(24ull       ), 0);
  NT2_TEST_ULP_EQUAL(120,         saturate_to<T>(120ull      ), 0); 
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(720ull      ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(5040ull     ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(40320ull    ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(362880ull   ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(3628800ull  ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(39916800ull ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(479001600ull), 0);

  NT2_TEST_ULP_EQUAL(1,           saturate_to<T>(1ll        ), 0);
  NT2_TEST_ULP_EQUAL(2,           saturate_to<T>(2ll        ), 0);
  NT2_TEST_ULP_EQUAL(6,           saturate_to<T>(6ll        ), 0);
  NT2_TEST_ULP_EQUAL(24,          saturate_to<T>(24ll       ), 0);
  NT2_TEST_ULP_EQUAL(120,         saturate_to<T>(120ll      ), 0); 
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(720ll      ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(5040ll     ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(40320ll    ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(362880ll   ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(3628800ll  ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(39916800ll ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(479001600ll), 0);

  NT2_TEST_ULP_EQUAL(-1,           saturate_to<T>(-1ll        ), 0);
  NT2_TEST_ULP_EQUAL(-2,           saturate_to<T>(-2ll        ), 0);
  NT2_TEST_ULP_EQUAL(-6,           saturate_to<T>(-6ll        ), 0);
  NT2_TEST_ULP_EQUAL(-24,          saturate_to<T>(-24ll       ), 0);
  NT2_TEST_ULP_EQUAL(-120,         saturate_to<T>(-120ll      ), 0); 
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-720ll      ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-5040ll     ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-40320ll    ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-362880ll   ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-3628800ll  ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-39916800ll ), 0);
  NT2_TEST_ULP_EQUAL(Valmin<T>(),  saturate_to<T>(-479001600ll), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( saturate_to_unsigned_uint8,  (uint8_t))
{
  
   using boost::simd::saturate_to;
   using boost::simd::tag::saturate_to_;
   using boost::simd::Valmax; 
  NT2_TEST_ULP_EQUAL(1,           saturate_to<T>(1ull        ), 0);
  NT2_TEST_ULP_EQUAL(2,           saturate_to<T>(2ull        ), 0);
  NT2_TEST_ULP_EQUAL(6,           saturate_to<T>(6ull        ), 0);
  NT2_TEST_ULP_EQUAL(24,          saturate_to<T>(24ull       ), 0);
  NT2_TEST_ULP_EQUAL(120,         saturate_to<T>(120ull      ), 0); 
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(720ull      ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(5040ull     ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(40320ull    ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(362880ull   ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(3628800ull  ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(39916800ull ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(479001600ull), 0);

  NT2_TEST_ULP_EQUAL(1,           saturate_to<T>(1ll        ), 0);
  NT2_TEST_ULP_EQUAL(2,           saturate_to<T>(2ll        ), 0);
  NT2_TEST_ULP_EQUAL(6,           saturate_to<T>(6ll        ), 0);
  NT2_TEST_ULP_EQUAL(24,          saturate_to<T>(24ll       ), 0);
  NT2_TEST_ULP_EQUAL(120,         saturate_to<T>(120ll      ), 0); 
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(720ll      ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(5040ll     ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(40320ll    ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(362880ll   ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(3628800ll  ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(39916800ll ), 0);
  NT2_TEST_ULP_EQUAL(Valmax<T>(), saturate_to<T>(479001600ll), 0);

  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-1ll        ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-2ll        ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-6ll        ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-24ll       ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-120ll      ), 0); 
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-720ll      ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-5040ll     ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-40320ll    ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-362880ll   ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-3628800ll  ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-39916800ll ), 0);
  NT2_TEST_ULP_EQUAL(0, saturate_to<T>(-479001600ll), 0);
} // end of test for unsigned_int_
