//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/include/functions/plinsolve.hpp>
#include <nt2/include/functions/gesv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <boost/core/ignore_unused.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(plinsolve, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>           t_t;
typedef nt2::table<nt2_la_int>  t_i;

t_t lu;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(10,1),nt2::meta::as_<T>());
t_t x1(b+b);
t_i piv;

nt2::plinsolve(a ,b+b, nt2::tie(x) );
nt2_la_int iter = nt2::gesv( boost::proto::value(a), boost::proto::value(piv)
                         , boost::proto::value(x1) );

NT2_TEST_ULP_EQUAL(x(_(1,3)), x1 , T(10));
NT2_TEST_EQUAL(T(iter)>=T(0)?true:false, true);

}
