//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - saturate_to/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 20/03/2011
/// 
#include <boost/simd/toolbox/ieee/include/functions/saturate_to.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( saturate_to_unsigned_int64,  (uint64_t))
{
  using boost::simd::saturate_to;
  using boost::simd::tag::saturate_to_;
  using boost::simd::native;
  using boost::simd::splat; 
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef native<uint64_t,ext_t>           vuint64_t;
  typedef native< int64_t,ext_t>            vint64_t;
  vuint64_t v = splat<vuint64_t>(1ull        ); 
  saturate_to<vT>(v);
  saturate_to<T>(1ull        ); 
  //  NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(1ull        ))[0], saturate_to<T>(1ull        ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(2ull        ))[0], saturate_to<T>(2ull        ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(6ull        ))[0], saturate_to<T>(6ull        ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(24ull       ))[0], saturate_to<T>(24ull       ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(120ull      ))[0], saturate_to<T>(120ull      ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(720ull      ))[0], saturate_to<T>(720ull      ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(5040ull     ))[0], saturate_to<T>(5040ull     ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(40320ull    ))[0], saturate_to<T>(40320ull    ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(362880ull   ))[0], saturate_to<T>(362880ull   ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(3628800ull  ))[0], saturate_to<T>(3628800ull  ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(39916800ull ))[0], saturate_to<T>(39916800ull ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vuint64_t>(479001600ull))[0], saturate_to<T>(479001600ull));

//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(1ll        ))[0], saturate_to<T>(1ll        ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(2ll        ))[0], saturate_to<T>(2ll        ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(6ll        ))[0], saturate_to<T>(6ll        ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(24ll       ))[0], saturate_to<T>(24ll       ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(120ll      ))[0], saturate_to<T>(120ll      ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(720ll      ))[0], saturate_to<T>(720ll      ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(5040ll     ))[0], saturate_to<T>(5040ll     ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(40320ll    ))[0], saturate_to<T>(40320ll    ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(362880ll   ))[0], saturate_to<T>(362880ll   ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(3628800ll  ))[0], saturate_to<T>(3628800ll  ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(39916800ll ))[0], saturate_to<T>(39916800ll ));
//   NT2_TEST_EQUAL(saturate_to<vT>(splat<vint64_t>(479001600ll))[0], saturate_to<T>(479001600ll));

} // end of test for unsigned_int_
