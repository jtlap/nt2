//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/ulpdist.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
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

NT2_TEST_CASE_TPL ( ulpdist_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::ulpdist;
  using nt2::tag::ulpdist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(vT,vT)>::type
                  , vT
                  );

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ulpdist(nt2::Inf<vT>(), nt2::Inf<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(nt2::Minf<vT>(), nt2::Minf<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(nt2::Nan<vT>(), nt2::Nan<vT>()), nt2::Zero<vT>());
#endif

  NT2_TEST_EQUAL(ulpdist(nt2::Mone<vT>(), nt2::Mone<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(nt2::One<vT>(), nt2::One<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());

  NT2_TEST_EQUAL( ulpdist(nt2::One<vT>(), nt2::One<vT>()+nt2::Eps<vT>())
                , nt2::splat<vT>(0.5)
                );

  NT2_TEST_EQUAL( ulpdist(nt2::One<vT>(), nt2::One<vT>()-nt2::Eps<vT>())
                , nt2::splat<vT>(0.5)
                );

  NT2_TEST_EQUAL( ulpdist(nt2::One<vT>(), nt2::One<vT>()-nt2::Eps<vT>()/T(2))
                , nt2::splat<vT>(0.25)
                );
}

NT2_TEST_CASE_TPL ( ulpdist_signed_integral,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using nt2::ulpdist;
  using nt2::tag::ulpdist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(ulpdist(nt2::Mone<vT>(), nt2::Mone<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(nt2::One<vT>(), nt2::One<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());

  NT2_TEST_EQUAL( ulpdist(nt2::Zero<vT>(), nt2::Valmin<vT>())
                , nt2::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmin<vT>(), nt2::Zero<vT>())
                , nt2::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Zero<vT>(), nt2::Valmax<vT>())
                , nt2::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmax<vT>(), nt2::Zero<vT>())
                , nt2::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmin<vT>(), nt2::Valmax<vT>())
                , nt2::Valmax<vT>()
                );
}

NT2_TEST_CASE_TPL ( ulpdist_unsigned_integral,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using nt2::ulpdist;
  using nt2::tag::ulpdist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ulpdist_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(ulpdist(nt2::Mone<vT>(), nt2::Mone<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(nt2::One<vT>(), nt2::One<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ulpdist(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());

  NT2_TEST_EQUAL( ulpdist(nt2::Zero<vT>(), nt2::Valmin<vT>())
                , nt2::Zero<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmin<vT>(), nt2::Zero<vT>())
                , nt2::Zero<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Zero<vT>(), nt2::Valmax<vT>())
                , nt2::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmax<vT>(), nt2::Zero<vT>())
                , nt2::Valmax<vT>()
                );

  NT2_TEST_EQUAL( ulpdist(nt2::Valmin<vT>(), nt2::Valmax<vT>())
                , nt2::Valmax<vT>()
                );
}
