//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 integration toolbox - mtc"

#include <iostream>
#include <nt2/sdk/timing/tic.hpp>
#include <nt2/include/functions/mtc.hpp>
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
#include <nt2/include/functions/cons.hpp>
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
    typedef typename X::value_type T;
    return sqr(x(1, nt2::_))+sqr(x(2, nt2::_) <= nt2::One<T>();
  }
};



NT2_TEST_CASE_TPL( mtc_cplx_out, NT2_REAL_TYPES )
{
  using nt2::mtc;
  using nt2::options;
  using nt2::integration::output;
  typedef typename nt2::meta::as_complex<T>::type cT;
  typedef nt2::table<T> tab_t;
  tab_t x =  nt2::cons(nt2::of_size(2, 2), T(0), T(0), T(1), T(1));// x.reshape(nt2::of_size(2, 2))
  nt2::tic();
  BOOST_AUTO_TPL(res, (mtc(f(), x)));
  nt2::toc();
  std::cout << "Integrals:" << res.integrals << ") with error " << res.errors
            << " after " << res.eval_count <<  " evaluations\n";
  NT2_DISPLAY(nt2::Mtcabstol<T>());
  NT2_TEST_LESSER_EQUAL(nt2::dist(res.integrals(1), nt2::Two<cT>()), nt2::Mtcabstol<T>());
}

