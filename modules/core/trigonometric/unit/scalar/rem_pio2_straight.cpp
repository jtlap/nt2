//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/rem_pio2_straight.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/trigonometric/constants.hpp>

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

#include <nt2/constant/constant.hpp>


NT2_TEST_CASE_TPL ( rem_pio2_straight_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::rem_pio2_straight;
  using nt2::tag::rem_pio2_straight_;
  typedef typename nt2::meta::as_integer<T>::type iT;
 typedef std::pair<iT, T>  r_t;


  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<rem_pio2_straight_(T)>::type)
                  , (std::pair<iT,T>)
                  );

  {
    T r1;
    NT2_TEST_EQUAL( rem_pio2_straight(nt2::Pio_2<T>(), r1), nt2::One<iT>());
    NT2_TEST_ULP_EQUAL( r1, nt2::Zero<T>(), 0.5);
    NT2_TEST_EQUAL( rem_pio2_straight(nt2::Pio_4<T>(), r1), nt2::One<iT>());
    NT2_TEST_ULP_EQUAL( r1, -nt2::Pio_4<T>(), 0.5);
  }
}
