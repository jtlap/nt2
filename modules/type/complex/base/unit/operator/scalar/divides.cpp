//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/divides.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( divides_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::divides;
  using nt2::tag::divides_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<divides_(cT,cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nt2::divides(cT(nt2::Inf<T>()),  cT(nt2::Inf<T>())),  cT(nt2::Nan<T>(), nt2::Zero<T>()), 0);
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Minf<T>()), cT(nt2::Minf<T>())), cT(nt2::Nan<T>(), nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Nan<T>()),  cT(nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::One<T>()),  cT(nt2::Zero<T>())), cT(nt2::Inf<T>(), nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Zero<T>()), cT(nt2::Zero<T>())), cT(nt2::Nan<T>(), nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::divides(cT(0, 1), cT(nt2::Inf<T>())), cT(0));
  NT2_TEST_EQUAL(nt2::divides(T(1), cT(nt2::Inf<T>())), cT(0));
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Inf<T>(), nt2::Inf<T>()),  cT(nt2::Zero<T>(), nt2::Zero<T>())), cT(nt2::Inf<T>(), nt2::Inf<T>())  );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::One<T>(), nt2::Inf<T>()),  cT(nt2::Zero<T>(), nt2::Zero<T>())), cT(nt2::Inf<T>(), nt2::Inf<T>())  );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::One<T>(), nt2::One<T>()),  cT(nt2::Zero<T>(), nt2::Zero<T>())), cT(nt2::Inf<T>(), nt2::Inf<T>())  );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Inf<T>(), nt2::One<T>()),  cT(nt2::Zero<T>(), nt2::Zero<T>())), cT(nt2::Inf<T>(), nt2::Inf<T>())  );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Inf<T>(), nt2::Zero<T>()), cT(nt2::Zero<T>(), nt2::Zero<T>())), cT(nt2::Inf<T>(), nt2::Zero<T>()) );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Zero<T>(),nt2::Inf<T>()),  cT(nt2::Zero<T>(), nt2::Zero<T>())), cT(nt2::Zero<T>(), nt2::Inf<T>())  );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Inf<T>(), nt2::Inf<T>()),  cT(nt2::One<T>(),  nt2::Zero<T>())), cT(nt2::Inf<T>(), nt2::Inf<T>())  );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::One<T>(), nt2::Inf<T>()),  cT(nt2::Zero<T>(), nt2::One<T>())),  cT(nt2::Inf<T>(), nt2::Mone<T>()) );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Inf<T>(), nt2::Inf<T>()),  cT(nt2::One<T>(),  nt2::One<T>())),  cT(nt2::Inf<T>(), nt2::Nan<T>()) );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::Inf<T>(), nt2::One<T>()),  cT(nt2::One<T>(),  nt2::One<T>())),  cT(nt2::Inf<T>(), nt2::Minf<T>()) );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::One<T>(), nt2::Zero<T>()), cT(nt2::Inf<T>(),  nt2::Zero<T>())), cT(nt2::Zero<T>(), nt2::Zero<T>()) );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::One<T>(), nt2::Zero<T>()), cT(nt2::Zero<T>(), nt2::Inf<T>())),  cT(nt2::Zero<T>(), nt2::Zero<T>()) );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::One<T>(), nt2::One<T>()),  cT(nt2::Inf<T>(),  nt2::One<T>())),  cT(nt2::Zero<T>(), nt2::Zero<T>()) );
  NT2_TEST_EQUAL(nt2::divides(cT(nt2::One<T>(), nt2::One<T>()),  cT(nt2::One<T>(),  nt2::Inf<T>())),  cT(nt2::Zero<T>(), nt2::Zero<T>()) );
#endif
  NT2_TEST_EQUAL(nt2::divides(cT(0, 1), cT(0, 1)), cT(1, 0));
  NT2_TEST_EQUAL(nt2::divides(cT(1, 0), T(1))    , cT(1, 0));
  NT2_TEST_EQUAL(nt2::divides(cT(0, 2), cT(0, 1)), cT(2, 0));
  NT2_TEST_EQUAL(nt2::divides(cT(1, 1), cT(1, -1)), cT(0, 1));
}
