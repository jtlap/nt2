//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/ulpdist.hpp>

#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>

NT2_TEST_CASE_TPL ( ulpdist_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::ulpdist;
  using nt2::tag::ulpdist_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(T,T)>::type
                  , T
                  );

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ulpdist(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(nt2::Minf<T>(), nt2::Minf<T>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Zero<T>());
#endif

  NT2_TEST_EQUAL(ulpdist(nt2::Mone<T>(), nt2::Mone<T>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(nt2::One<T>(), nt2::One<T>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>());

  NT2_TEST_EQUAL( ulpdist(nt2::One<T>(), nt2::One<T>()+nt2::Eps<T>())
                , T(0.5)
                );

  NT2_TEST_EQUAL( ulpdist(nt2::One<T>(), nt2::One<T>()-nt2::Eps<T>())
                , T(0.5)
                );

  NT2_TEST_EQUAL( ulpdist(nt2::One<T>(), nt2::One<T>()-nt2::Eps<T>()/2)
                , T(0.25)
                );
}

NT2_TEST_CASE_TPL ( ulpdist_signed_integral,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using nt2::ulpdist;
  using nt2::tag::ulpdist_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(T,T)>::type
                  , T
                  );

  NT2_TEST_EQUAL(ulpdist(nt2::Mone<T>(), nt2::Mone<T>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(nt2::One<T>(), nt2::One<T>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>());

  NT2_TEST_EQUAL( ulpdist(nt2::Zero<T>(), nt2::Valmin<T>())
                , nt2::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmin<T>(), nt2::Zero<T>())
                , nt2::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Zero<T>(), nt2::Valmax<T>())
                , nt2::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmax<T>(), nt2::Zero<T>())
                , nt2::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmin<T>(), nt2::Valmax<T>())
                , nt2::Valmax<T>()
                );
}

NT2_TEST_CASE_TPL ( ulpdist_unsigned_integral,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using nt2::ulpdist;
  using nt2::tag::ulpdist_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(T,T)>::type
                  , T
                  );

  NT2_TEST_EQUAL(ulpdist(nt2::Mone<T>(), nt2::Mone<T>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(nt2::One<T>(), nt2::One<T>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>());

  NT2_TEST_EQUAL( ulpdist(nt2::Zero<T>(), nt2::Valmin<T>())
                , nt2::Zero<T>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmin<T>(), nt2::Zero<T>())
                , nt2::Zero<T>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Zero<T>(), nt2::Valmax<T>())
                , nt2::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmax<T>(), nt2::Zero<T>())
                , nt2::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmin<T>(), nt2::Valmax<T>())
                , nt2::Valmax<T>()
                );
}
