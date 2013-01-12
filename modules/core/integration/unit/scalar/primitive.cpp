//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 integration toolbox - primitive"

#include <iostream>
#include <nt2/sdk/timing/tic.hpp>
#include <nt2/toolbox/integration/primitive.hpp>
#include <nt2/include/functions/quad.hpp>
#include <nt2/toolbox/integration/output.hpp>
#include <nt2/toolbox/integration/options.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/table.hpp>
struct f
{
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
  nt2::tic();
//  primitive<nt2::tag::quad_>(f(), nt2::linspace(T(0), T(5), 10));

   BOOST_AUTO_TPL(res, (primitive<nt2::tag::quad_>(f(), nt2::linspace(T(0), T(5)))));
   nt2::toc();
   std::cout << "Integrals:" << res.integrals << ") with error " << res.errors
             << " after " << res.eval_count <<  " evaluations\n";
   NT2_TEST_ULP_EQUAL(res.integrals(nt2::end_), T(12.5), 2);
}
