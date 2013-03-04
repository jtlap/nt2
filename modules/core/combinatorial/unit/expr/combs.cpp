//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - combs/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
///
#include <nt2/toolbox/combinatorial/include/functions/combs.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/saturate.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/colvect.hpp>


#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/tic.hpp>
#include <nt2/include/functions/toc.hpp>
#include <nt2/sdk/meta/type_id.hpp>

NT2_TEST_CASE_TPL ( combs_integer__1_0, NT2_REAL_TYPES)
{

  using nt2::combs;
  using nt2::tag::combs_;

   nt2::table<T, nt2::_2D> a =  combs(nt2::_(T(1), T(5)), 3);
   NT2_DISPLAY(a);
   nt2::table<T, nt2::_2D> b =  combs(nt2::_(T(1), T(5)), 5);
   NT2_DISPLAY(b);
   NT2_TEST(nt2::isequal(b,nt2::_(T(1), T(5)) ));
   nt2::table<T, nt2::_2D> c =  combs(nt2::_(T(1), T(5)), 1);
   NT2_DISPLAY(c);
   NT2_TEST(nt2::isequal(c,nt2::colvect(nt2::_(T(1), T(5)))));

}
