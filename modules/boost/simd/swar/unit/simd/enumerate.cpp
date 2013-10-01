//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/enumerate.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( enumerate, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::enumerate;
  using boost::dispatch::meta::as_;
  using boost::simd::tag::enumerate_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<enumerate_(as_<vT> )>::type
                  , vT
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<enumerate_(T,as_<vT> )>::type
                  , vT
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<enumerate_(T,T,as_<vT> )>::type
                  , vT
                  );

  vT ref;

  for(std::size_t i=0; i < vT::static_size;++i)
    ref[i] = T(i);

  NT2_TEST_EQUAL(enumerate<vT>(), ref);

  for(std::size_t i=0; i < vT::static_size;++i)
    ref[i] = T(i+42);

  NT2_TEST_EQUAL(enumerate<vT>(42), ref);
  for(std::size_t i=0; i < vT::static_size;++i)
    ref[i] = T(3*i+4);

  NT2_TEST_EQUAL(enumerate<vT>(4,3), ref);
}
