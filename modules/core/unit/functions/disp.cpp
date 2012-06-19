/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::table "

#include <nt2/table.hpp>
#include <nt2/include/functions/disp.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/display.hpp>

#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL( stream, NT2_TYPES )
{
  using nt2::_;
  using nt2::ones;
  using nt2::table;
  using nt2::of_size;
  using nt2::meta::as_;

  std::cout << "empty container\n";
  std::cout << _() << "\n";
  std::cout << "\n";

  table<T> x = ones(4,4, as_<T>() );
  std::cout << "ones(4,4)\n";
  std::cout << x << "\n";
  std::cout << "\n";
}

NT2_TEST_CASE_TPL( disp, NT2_TYPES )
{
  using nt2::_;
  using nt2::ones;
  using nt2::disp;
  using nt2::table;
  using nt2::of_size;
  using nt2::meta::as_;

  disp("a scalar\n");
  disp( T(4) );
  disp("\n");

  disp("empty container\n");
  disp( _() );
  disp("\n");

  table<T> x = ones(4,4, as_<T>() );
  disp("ones(4,4)\n");
  disp( x );
  disp("\n");
}

NT2_TEST_CASE_TPL( display, NT2_TYPES )
{
  using nt2::_;
  using nt2::ones;
  using nt2::display;
  using nt2::table;
  using nt2::of_size;
  using nt2::meta::as_;

  display("a scalar\n");
  display( T(4) );
  display("\n");

  std::cout << "empty container\n";
  display( _() );
  std::cout << "\n";

  display( "empty container", _() );
  std::cout << "\n";

  table<T> x = ones(4,4, as_<T>() );
  std::cout << "ones(4,4)\n";
  display( x );
  std::cout << "\n";

  display( "x", x );
  std::cout << "\n";
}
