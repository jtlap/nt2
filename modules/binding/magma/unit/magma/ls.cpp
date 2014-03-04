//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ls.hpp>
#include <nt2/include/functions/lsy.hpp>
#include <nt2/linalg/details/utility/llspgen.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/sv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(ls, (float) )
{
  using nt2::_;

typedef nt2::table<T>         t_t;
typedef nt2::table<nt2_la_int>         t_i;
size_t m=200, n=100, nr=1, q=1;

t_t a,x,r,b;
t_i jpvt = nt2::zeros(nt2::of_size(m,1), nt2::meta::as_<nt2_la_int>());


nt2::tie(a,x,r,b) = nt2::llspgen(m,n,q,nr, nt2::meta::as_<T>());


t_t a1(a);
t_t b1(b);

nt2_la_int p = nt2::ls(boost::proto::value(a),boost::proto::value(b));

nt2_la_int p1 = nt2::lsy(boost::proto::value(a1),boost::proto::value(jpvt)
                       ,boost::proto::value(b1));

NT2_TEST_ULP_EQUAL(b, b1, T(100000000) );
NT2_TEST_EQUAL(p, 0);
NT2_TEST_EQUAL(p1, 0);


}
