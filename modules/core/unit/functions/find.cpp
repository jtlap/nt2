/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 function find"

#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( find )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::find;
  typedef double T;
  typedef std::ptrdiff_t U;

  T in[] ={ T(1),    T(0),    T(6),
            T(4),    T(9),    T(15),
            T(7),    T(0),    T(24),
            T(10),   T(21),   T(0),
            T(13),   T(27),   T(42),
            T(0),    T(0),    T(51),
            T(19),   T(39),   T(60),
            T(22),   T(45),   T(69),
            T(25),   T(0),    T(78),
            T(0),    T(57),   T(0)
          };

  U out[]={ U(1),             U(3),
            U(4),    U(5),    U(6),
            U(7),             U(9),
            U(10),   U(11),
            U(13),   U(14),   U(15),
                              U(18),
            U(19),   U(20),   U(21),
            U(22),   U(23),   U(24),
            U(25),            U(27),
                     U(29)
          };

  T out2[]={T(1),             T(6),
            T(4),    T(9),    T(15),
            T(7),             T(24),
            T(10),   T(21),
            T(13),   T(27),   T(42),
                              T(51),
            T(19),   T(39),   T(60),
            T(22),   T(45),   T(69),
            T(25),            T(78),
                     T(57),
          };
  table<T, nt2::shared_> in2(of_size(3, 5, 2), nt2::share(&in[0], in + sizeof in/sizeof *in));
  table<U, nt2::shared_> c(of_size(sizeof out/sizeof *out), nt2::share(&out[0], out + sizeof out/sizeof *out));
  table<T, nt2::shared_> d(of_size(sizeof out2/sizeof *out2), nt2::share(&out2[0], out2 + sizeof out2/sizeof *out2));

  table<T> a = in2;
  table<U> b = find(a);
  NT2_TEST( isequal(b, c) );

  table<T> e = a(nt2::is_nez(a));
  NT2_TEST( isequal(e, d) );
}
