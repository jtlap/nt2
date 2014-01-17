//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/ulpdist.hpp>

#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <boost/simd/sdk/config.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/eps.hpp>

NT2_TEST_CASE_TPL ( ulpdist_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::ulpdist;
  using boost::simd::tag::ulpdist_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(T,T)>::type
                  , T
                  );

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ulpdist(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Zero<T>());
#endif

  NT2_TEST_EQUAL(ulpdist(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>());

  NT2_TEST_EQUAL( ulpdist(boost::simd::One<T>(), boost::simd::One<T>()+boost::simd::Eps<T>())
                , T(0.5)
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::One<T>(), boost::simd::One<T>()-boost::simd::Eps<T>())
                , T(0.5)
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::One<T>(), boost::simd::One<T>()-boost::simd::Eps<T>()/2)
                , T(0.25)
                );
}

NT2_TEST_CASE_TPL ( ulpdist_signed_integral,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::ulpdist;
  using boost::simd::tag::ulpdist_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(T,T)>::type
                  , T
                  );

  NT2_TEST_EQUAL(ulpdist(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>());

  NT2_TEST_EQUAL( ulpdist(boost::simd::Zero<T>(), boost::simd::Valmin<T>())
                , boost::simd::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmin<T>(), boost::simd::Zero<T>())
                , boost::simd::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Zero<T>(), boost::simd::Valmax<T>())
                , boost::simd::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmax<T>(), boost::simd::Zero<T>())
                , boost::simd::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmin<T>(), boost::simd::Valmax<T>())
                , boost::simd::Valmax<T>()
                );
}

NT2_TEST_CASE_TPL ( ulpdist_unsigned_integral,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::ulpdist;
  using boost::simd::tag::ulpdist_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(T,T)>::type
                  , T
                  );

  NT2_TEST_EQUAL(ulpdist(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>());

  NT2_TEST_EQUAL( ulpdist(boost::simd::Zero<T>(), boost::simd::Valmin<T>())
                , boost::simd::Zero<T>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmin<T>(), boost::simd::Zero<T>())
                , boost::simd::Zero<T>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Zero<T>(), boost::simd::Valmax<T>())
                , boost::simd::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmax<T>(), boost::simd::Zero<T>())
                , boost::simd::Valmax<T>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmin<T>(), boost::simd::Valmax<T>())
                , boost::simd::Valmax<T>()
                );
}
