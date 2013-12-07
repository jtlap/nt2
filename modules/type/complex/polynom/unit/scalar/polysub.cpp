//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/polysub.hpp>
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <nt2/table.hpp>
#include <boost/array.hpp>

NT2_TEST_CASE_TPL ( polysub,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  using nt2::polysub;
  using nt2::tag::polysub_;
  nt2::table<cT, nt2::_2D> a =  nt2::complexify(nt2::_(T(1), T(4)));
  nt2::table<cT, nt2::_2D> b =  nt2::complexify(nt2::_(T(1), T(2)));
  nt2::table<cT, nt2::_2D> c;
  cT aab[] = { 1, 2, 2, 2};
  nt2::table<cT> d(nt2::of_size(1, 4), &aab[0], &aab[4]);
  c = polysub(a, b);
  NT2_TEST_EQUAL(d,polysub(a, b));
  NT2_TEST_EQUAL(-d,polysub(b, a));
}


