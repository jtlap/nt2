//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::as_real"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/mpl/placeholders.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE(as_floating)
{
  using boost::mpl::_;
  using boost::dispatch::meta::as_floating;

  NT2_TEST_TYPE_IS( as_floating<double>::type                ,double);
  NT2_TEST_TYPE_IS( as_floating<float>::type                 ,float );
  NT2_TEST_TYPE_IS( as_floating<boost::simd::int64_t>::type  ,double);
  NT2_TEST_TYPE_IS( as_floating<boost::simd::int32_t >::type ,float );
  NT2_TEST_TYPE_IS( as_floating<boost::simd::uint64_t>::type ,double);
  NT2_TEST_TYPE_IS( as_floating<boost::simd::uint32_t>::type ,float );
}

NT2_TEST_CASE(as_floating_2_args)
{
  using boost::mpl::_;
  using boost::dispatch::meta::as_floating;

  NT2_TEST_TYPE_IS( (as_floating<double,double>::type               ), double);
  NT2_TEST_TYPE_IS( (as_floating<double,float>::type                ), double);
  NT2_TEST_TYPE_IS( (as_floating<double,boost::simd::int64_t>::type ), double);
  NT2_TEST_TYPE_IS( (as_floating<double,boost::simd::int32_t>::type ), double);
  NT2_TEST_TYPE_IS( (as_floating<double,boost::simd::uint64_t>::type), double);
  NT2_TEST_TYPE_IS( (as_floating<double,boost::simd::uint32_t>::type), double);
  NT2_TEST_TYPE_IS( (as_floating<float,double>::type                ), double);
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int64_t,double>::type ), double);
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int32_t,double>::type ), double);
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint64_t,double>::type), double);
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint32_t,double>::type), double);

  NT2_TEST_TYPE_IS( (as_floating<float,float>::type)                , float );
  NT2_TEST_TYPE_IS( (as_floating<float,boost::simd::int64_t>::type) , double);
  NT2_TEST_TYPE_IS( (as_floating<float,boost::simd::int32_t>::type) , float );
  NT2_TEST_TYPE_IS( (as_floating<float,boost::simd::uint64_t>::type), double);
  NT2_TEST_TYPE_IS( (as_floating<float,boost::simd::uint32_t>::type), float );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int64_t,float>::type) , double);
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int32_t,float>::type) , float );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint64_t,float>::type), double);
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint32_t,float>::type), float );

  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int64_t,boost::simd::int64_t>::type), double );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int64_t,boost::simd::int32_t>::type) , double );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int64_t,boost::simd::uint64_t>::type), double);
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int64_t,boost::simd::uint32_t>::type), double );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int32_t,boost::simd::int64_t>::type) , double );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint64_t,boost::simd::int64_t>::type), double);
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint32_t,boost::simd::int64_t>::type), double );

  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint64_t,boost::simd::uint64_t>::type), double );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint64_t,boost::simd::int32_t>::type) , double );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint64_t,boost::simd::uint32_t>::type), double );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int32_t,boost::simd::uint64_t>::type) , double );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint32_t,boost::simd::uint64_t>::type), double );

  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int32_t,boost::simd::int32_t>::type) , float  );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int32_t,boost::simd::uint32_t>::type), float  );
  NT2_TEST_TYPE_IS( (as_floating<boost::simd::int32_t,boost::simd::uint64_t>::type), double );

  NT2_TEST_TYPE_IS( (as_floating<boost::simd::uint32_t,boost::simd::int32_t>::type), float );
}
