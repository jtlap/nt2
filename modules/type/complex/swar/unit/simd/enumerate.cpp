//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 type.swar toolbox - enumerate SIMD Mode"

#include <nt2/include/functions/enumerate.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/sdk/complex/complex.hpp>

NT2_TEST_CASE_TPL ( enumerate, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::enumerate;
  using boost::dispatch::meta::as_;
  using boost::simd::tag::enumerate_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T> cT;
  typedef native<cT,ext_t> vT;
  typedef typename boost::dispatch::meta::call<enumerate_(cT, as_<vT> )>::type r_t;

  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(enumerate<vT>(cT(10,5))[i], cT(i+10,5));

  for(std::size_t i=0; i < vT::static_size;++i)
    NT2_TEST_EQUAL(enumerate<vT>(cT(10,5),cT(2,1))[i], cT(2*i+10,i+5));
}
