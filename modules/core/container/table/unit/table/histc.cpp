//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/histc.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/prev.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/colon/colon.hpp>


NT2_TEST_CASE_TPL( histc1, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::histc;
  typedef typename nt2::meta::as_integer<T, unsigned>::type uiT;
  table<T> x =  nt2::trans(cath(T(-12), nt2::linspace(T(-10), T(10), 101)));
  table<T> bins =  cath(nt2::Minf<T>(), nt2::linspace(T(-10), T(10), 10));
  table<uiT> h =  histc(x, bins, 1);
  table<uiT> r =  nt2::cons<uiT>( nt2::of_size(11, 1),1,  12, 11, 11, 11, 11, 11, 11, 11, 11, 1);
  NT2_TEST_EQUAL(h, r);
}

NT2_TEST_CASE_TPL( histc2, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::histc;
  typedef typename nt2::meta::as_integer<T, unsigned>::type uiT;
  table<T> x = nt2::linspace(T(-10), T(10), 101);
  table<T> bins =  nt2::linspace(T(-10), T(10), 10);
  table<uiT> h =  histc(x, bins, std::size_t(2));
  table<uiT> r =  nt2::cons<uiT>( nt2::of_size(1, 10),  12, 11, 11, 11, 11, 11, 11, 11, 11, 1);
  NT2_TEST_EQUAL(h, r);
}

NT2_TEST_CASE_TPL( histc3, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::histc;
  typedef typename nt2::meta::as_integer<T, unsigned>::type uiT;
  table<T> x = nt2::trans( nt2::repmat(nt2::linspace(T(-10), T(10), 101), 10, 1));
  table<T> bins =  nt2::linspace(T(-10), T(10), 10);
  table<uiT> h =  histc(x, bins, std::size_t(1));
  table<uiT> r =  nt2::repmat(nt2::cons<uiT>( nt2::of_size(10, 1), 12, 11, 11, 11, 11, 11, 11, 11, 11, 1), 1, 10);
  NT2_TEST_EQUAL(h, r);
}

NT2_TEST_CASE_TPL( histc4, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::histc;
  typedef typename nt2::meta::as_integer<T, unsigned>::type uiT;
  table<T> x = nt2::repmat(nt2::linspace(T(-10), T(10), 101), 10, 1);
  table<T> bins =  nt2::linspace(T(-10), T(10), 10);
  table<uiT> h =  histc(x, bins, std::size_t(2));
  table<uiT> r =  nt2::repmat(nt2::cons<uiT>( nt2::of_size(1, 10), 12, 11, 11, 11, 11, 11, 11, 11, 11, 1), 10, 1);
  NT2_TEST_EQUAL(h, r);
}

NT2_TEST_CASE_TPL( histc5, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::histc;
  typedef typename nt2::meta::as_integer<T, unsigned>::type uiT;
  table<T> x = nt2::_(T(-9.5), T(9.5));
  table<T> bins =  nt2::_(T(-10), T(10));

  table<uiT> h, p;
  nt2::tie(h, p) =  histc(x, bins, std::size_t(2));
  table<uiT> r = ones(x.extent(), nt2::meta::as_<uiT>()); //nt2::cons<uiT>( nt2::of_size(1, 10), 12, 11, 11, 11, 11, 11, 11, 11, 11, 1);
  NT2_TEST_EQUAL(h, r);
}

NT2_TEST_CASE_TPL( histc6, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::histc;
  typedef typename nt2::meta::as_integer<T, unsigned>::type uiT;
  table<T> x = nt2::repmat(nt2::linspace(T(-10), T(10), 101), 10, 1);
  table<T> bins =  nt2::linspace(T(-9.5), T(9.5), 10);

  table<uiT> h, p;
  nt2::tie(h, p) =  histc(x, bins, std::size_t(2));
  table<uiT> r =  nt2::repmat(nt2::cons<uiT>( nt2::of_size(1, 9), 11, 10, 11, 10, 11, 10, 11, 10, 11 ), 10, 1);
  NT2_TEST_EQUAL(h, r);
}







