//==============================================================================
//          Copyright 2015 J.T. Lapreste

//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/globalgeommean.hpp>
#include <nt2/include/functions/geommean.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/core/container/colon/colon.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL( globalgeommean, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::geommean;
  nt2::table<T> a = nt2::reshape(nt2::_(T(1), T(9)), 3, 3);
  NT2_TEST_EQUAL( nt2::globalgeommean(a), geommean(a(_))(1));
}
