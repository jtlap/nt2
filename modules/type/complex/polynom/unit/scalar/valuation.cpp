//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/valuation.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/complexify.hpp>

#include <boost/array.hpp>


NT2_TEST_CASE_TPL ( valuation,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  using nt2::valuation;
  using nt2::tag::valuation_;
  nt2::table<cT> a =  nt2::complexify(nt2::_(T(1), T(4)));
  nt2::table<cT> b =  nt2::complexify(nt2::_(T(0), T(0), T(3)));
  nt2::table<cT> c(nt2::of_size(1, 0));
  NT2_TEST_EQUAL(0, valuation(a));
  NT2_TEST_EQUAL(-1, valuation(b));
  b(2) = b(1) = cT(1);
  NT2_TEST_EQUAL(1, valuation(b));

} // end of test for floating_


NT2_TEST_CASE_TPL ( valuation_2,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  using nt2::valuation;
  using nt2::tag::valuation_;
  cT b = cT(1.0);
  cT a = cT(0.0);
  NT2_TEST_EQUAL(valuation(a), -1);
  NT2_TEST_EQUAL(valuation(b), 0);
  nt2::container::table<cT> bb =  nt2::complexify(nt2::_(T(1), T(1)));
  nt2::container::table<cT> aa =  nt2::complexify(nt2::_(T(0), T(0)));
  NT2_TEST_EQUAL(valuation(aa), -1);
  NT2_TEST_EQUAL(valuation(bb), 0);
  nt2::container::table<cT> cc;
  NT2_TEST_EQUAL(valuation(cc), -1);

}
