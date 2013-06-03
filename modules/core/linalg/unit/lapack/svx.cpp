//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/svx.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(sv, NT2_REAL_TYPES )
{
  using nt2::_;


  typedef nt2::table<T>         t_t;

  // t_t a  = nt2::ones (1, 3, nt2::meta::as_<T>())
  //          + T(10)*nt2::eye  (1, 3, nt2::meta::as_<T>());

  // t_t b = nt2::ones(1, 1, nt2::meta::as_<T>());

 T rcond;

 t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
 t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
 t_t x(nt2::of_size(3,1));



  NT2_DISPLAY(a);
  NT2_DISPLAY(b);

  nt2_la_int p = nt2::svx(a,b,x,rcond);

  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  NT2_DISPLAY(x);
  NT2_DISPLAY(rcond);


}
