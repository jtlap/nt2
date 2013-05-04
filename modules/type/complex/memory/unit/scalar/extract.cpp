//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/extract.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(complex, BOOST_SIMD_REAL_TYPES)
{
  using std::complex;
  using nt2::extract;
  using nt2::tag::extract_;

  typedef typename boost::dispatch::meta
                        ::call<extract_(complex<T>, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, std::complex<T> );

  complex<T> data;
  complex<T> ref = complex<T>(13,37);

  data = extract(ref, 0);

  NT2_TEST_EQUAL( data, ref   );
}

NT2_TEST_CASE_TPL(dry, BOOST_SIMD_REAL_TYPES)
{
  using nt2::dry;
  using nt2::extract;
  using nt2::tag::extract_;

  typedef typename boost::dispatch::meta
                        ::call<extract_(dry<T>, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, dry<T> );

  dry<T> data;
  dry<T> ref = dry<T>(37);

  data = extract(ref, 0);

  NT2_TEST_EQUAL( data, ref   );
}

NT2_TEST_CASE_TPL(imaginary, BOOST_SIMD_REAL_TYPES)
{
  using nt2::imaginary;
  using nt2::extract;
  using nt2::tag::extract_;

  typedef typename boost::dispatch::meta
                        ::call<extract_(imaginary<T>, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, imaginary<T> );

  imaginary<T> data;
  imaginary<T> ref = imaginary<T>(37);

  data = extract(ref, 0);

  NT2_TEST_EQUAL( data, ref   );
}
