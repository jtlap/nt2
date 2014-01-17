//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
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
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>

NT2_TEST_CASE_TPL ( ulpdist_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::ulpdist;
  using boost::simd::tag::ulpdist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(vT,vT)>::type
                  , vT
                  );

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ulpdist(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Zero<vT>());
#endif

  NT2_TEST_EQUAL(ulpdist(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());

  NT2_TEST_EQUAL( ulpdist(boost::simd::One<vT>(), boost::simd::One<vT>()+boost::simd::Eps<vT>())
                , boost::simd::splat<vT>(0.5)
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::One<vT>(), boost::simd::One<vT>()-boost::simd::Eps<vT>())
                , boost::simd::splat<vT>(0.5)
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::One<vT>(), boost::simd::One<vT>()-boost::simd::Eps<vT>()/T(2))
                , boost::simd::splat<vT>(0.25)
                );
}


NT2_TEST_CASE_TPL ( ulpdist_signed_integral,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::ulpdist;
  using boost::simd::tag::ulpdist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(ulpdist(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());

  NT2_TEST_EQUAL( ulpdist(boost::simd::Zero<vT>(), boost::simd::Valmin<vT>())
                , boost::simd::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmin<vT>(), boost::simd::Zero<vT>())
                , boost::simd::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Zero<vT>(), boost::simd::Valmax<vT>())
                , boost::simd::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmax<vT>(), boost::simd::Zero<vT>())
                , boost::simd::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmin<vT>(), boost::simd::Valmax<vT>())
                , boost::simd::Valmax<vT>()
                );
}

NT2_TEST_CASE_TPL ( ulpdist_unsigned_integral,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::ulpdist;
  using boost::simd::tag::ulpdist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(ulpdist(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());

  NT2_TEST_EQUAL( ulpdist(boost::simd::Zero<vT>(), boost::simd::Valmin<vT>())
                , boost::simd::Zero<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmin<vT>(), boost::simd::Zero<vT>())
                , boost::simd::Zero<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Zero<vT>(), boost::simd::Valmax<vT>())
                , boost::simd::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmax<vT>(), boost::simd::Zero<vT>())
                , boost::simd::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(boost::simd::Valmin<vT>(), boost::simd::Valmax<vT>())
                , boost::simd::Valmax<vT>()
                );
}
