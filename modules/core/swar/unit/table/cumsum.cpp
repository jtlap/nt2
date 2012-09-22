/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 function cumsum"

#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cumsum.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( cumsum_inner )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::cumsum;
  using nt2::reshape;
  typedef double T;
  using nt2::_;

  table<T> a = reshape(_(T(1), 3*5*2), 3, 5, 2);
  table<T> b = cumsum(a);

  T r[] = { T(1),    T(3),    T(6),
            T(4),    T(9),    T(15),
            T(7),    T(15),   T(24),
            T(10),   T(21),   T(33),
            T(13),   T(27),   T(42),
            T(16),   T(33),   T(51),
            T(19),   T(39),   T(60),
            T(22),   T(45),   T(69),
            T(25),   T(51),   T(78),
            T(28),   T(57),   T(87)
          };
  table<T, nt2::shared_> c(of_size(3, 5, 2), nt2::share(&r[0], r + sizeof r/sizeof *r));
  NT2_TEST( isequal(b, c) );
}

NT2_TEST_CASE( cumsum_outer )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::cumsum;
  using nt2::reshape;
  typedef double T;
  using nt2::_;

  table<T> a = reshape(_(T(1), 3*5*2), 3, 5, 2);
  table<T> b = cumsum(a, 2);

  T r[] = { T(1),     T(2),     T(3),
            T(5),     T(7),     T(9),
            T(12),    T(15),    T(18),
            T(22),    T(26),    T(30),
            T(35),    T(40),    T(45),
            T(16),    T(17),    T(18),
            T(35),    T(37),    T(39),
            T(57),    T(60),    T(63),
            T(82),    T(86),    T(90),
            T(110),   T(115),   T(120)
          };
  table<T, nt2::shared_> c(of_size(3, 5, 2), nt2::share(&r[0], r + sizeof r/sizeof *r));
  NT2_TEST( isequal(b, c) );
}
