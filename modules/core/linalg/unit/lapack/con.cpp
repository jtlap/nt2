//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/svx.hpp>
#include <nt2/include/functions/ysv.hpp>
#include <nt2/include/functions/posv.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/con.hpp>
#include <nt2/include/functions/pocon.hpp>
#include <nt2/include/functions/sycon.hpp>
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

NT2_TEST_CASE_TPL(con, NT2_REAL_TYPES )
{
  using nt2::_;


  typedef nt2::table<T>           t_t;
  typedef nt2::table<nt2_la_int>  t_i;

 T rcond,rcond1, anorm;
 t_t lu;

 t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
 t_t a1(a);
 t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
 t_t x(nt2::of_size(3,1));
 t_i ipiv;
 char norm = '1';

 nt2_la_int p = nt2::svx(a,b,x,rcond);

 lu = nt2::lu(a1);
 anorm = nt2::lange(a1, norm);
 rcond1 = nt2::con(lu,norm,anorm);


 NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );
}


NT2_TEST_CASE_TPL(sycon, NT2_REAL_TYPES )
{
  using nt2::_;


  typedef nt2::table<T>           t_t;
  typedef nt2::table<nt2_la_int>  t_i;

 T rcond,rcond1, anorm;
 t_t lu;

 t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
 t_t a1(a);
 t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
 t_t x(nt2::of_size(3,1));

 t_i piv;
 char norm = '1';

 anorm = nt2::lange(a, norm);
 nt2_la_int p = nt2::ysv(a,piv,b,x);

 rcond = nt2::sycon(a,piv,anorm);

 lu = nt2::lu(a1);
 anorm = nt2::lange(a1, norm);
 rcond1 = nt2::con(lu,norm,anorm);

 NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}


NT2_TEST_CASE_TPL(pocon, NT2_REAL_TYPES )
{
  using nt2::_;


  typedef nt2::table<T>           t_t;
  typedef nt2::table<nt2_la_int>  t_i;

 T rcond,rcond1, anorm;
 t_t lu;

 t_t a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
 t_t a1(a);
 t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
 t_t x(nt2::of_size(3,1));

 t_i piv;
 char norm = '1';

 anorm = nt2::lange(a, norm);
 nt2_la_int p = nt2::posv(a,b,x);

 rcond = nt2::pocon(a,anorm);

 lu = nt2::lu(a1);
 anorm = nt2::lange(a1, norm);
 rcond1 = nt2::con(lu,norm,anorm);

 NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}
