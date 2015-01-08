//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/integration/primitive.hpp>
#include <nt2/include/functions/quad.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/integration/output.hpp>
#include <nt2/table.hpp>

#include <boost/dispatch/meta/strip.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

struct f
{
  template<class Sig>
  struct result;

  template<class This, class X>
  struct result<This(X)>
       : boost::dispatch::meta::strip<X>
  {
  };

  template < class X > inline
  X operator()(const X & x ) const
  {
    return x;
  }
};


NT2_TEST_CASE_TPL( primitive_cplx_inout2, NT2_REAL_TYPES )
{
  using nt2::primitive;
  using nt2::options;
  using nt2::integration::output;
//  primitive<nt2::tag::quad_>(f(), nt2::linspace(T(0), T(5), 10));

   BOOST_AUTO_TPL(res, (primitive<nt2::tag::quad_>(f(), nt2::linspace(T(0), T(5)))));
   NT2_TEST_ULP_EQUAL(res.integrals(nt2::end_), T(12.5), 2);
}
