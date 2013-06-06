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
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(complex, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using std::complex;
  using nt2::extract;
  using nt2::tag::extract_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<complex<T>,ext_t>      vT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, std::complex<T> );

  rT data;
  vT ref;

  for(std::size_t i=0;i<vT::static_size;++i)
    ref[i] = complex<T>(i+1,i*2);

  for(std::size_t i=0;i<vT::static_size;++i)
  {
    data = extract(ref, i);
    NT2_TEST_EQUAL( data, complex<T>(i+1,i*2) );
  }
}

NT2_TEST_CASE_TPL(dry, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::dry;
  using nt2::extract;
  using nt2::tag::extract_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<dry<T>,ext_t>      vT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, dry<T> );

  rT data;
  vT ref;

  for(std::size_t i=0;i<vT::static_size;++i)
    ref[i] = dry<T>(i+1);

  for(std::size_t i=0;i<vT::static_size;++i)
  {
    data = extract(ref, i);
    NT2_TEST_EQUAL( data, dry<T>(i+1) );
  }
}

NT2_TEST_CASE_TPL(imaginary, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::imaginary;
  using nt2::extract;
  using nt2::tag::extract_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<imaginary<T>,ext_t>      vT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, imaginary<T> );

  rT data;
  vT ref;

  for(std::size_t i=0;i<vT::static_size;++i)
    ref[i] = imaginary<T>(i+1);

  for(std::size_t i=0;i<vT::static_size;++i)
  {
    data = extract(ref, i);
    NT2_TEST_EQUAL( data, imaginary<T>(i+1) );
  }
}
