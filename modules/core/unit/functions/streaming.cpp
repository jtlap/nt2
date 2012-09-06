/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "streaming for containers"

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( output_stream, (double)(unsigned char) )
{
  {
    std::cout << nt2::_() << "\n";

    NT2_DISPLAY(nt2::_());
    std::cout << "\n===================================================\n";
  }

  {
    nt2::table<T> x00( nt2::of_size(0,0));
    std::cout << x00 << "\n";

    NT2_DISPLAY(x00);
    std::cout << "\n===================================================\n";
  }

  {
    nt2::table<T> x01( nt2::of_size(0,1));
    std::cout << x01 << "\n";

    NT2_DISPLAY(x01);
    std::cout << "\n===================================================\n";
  }

  {
    nt2::table<T> x010( nt2::of_size(0,1,0));
    std::cout << x010 << "\n";

    NT2_DISPLAY(x010);
    std::cout << "\n===================================================\n";
  }

  {
    nt2::table<T> x( nt2::of_size(4,6) );
    for(int j=1;j<=6;++j)
      for(int i=1;i<=4;++i)
        x(i,j) = T(i + 10*j);

    std::cout << (x+x*T(3)) << std::endl;

    NT2_DISPLAY(x+x*T(3));
    std::cout << "\n===================================================\n";
  }

  {
    nt2::table<T> x( nt2::of_size(4,3,2) );
    for(int k=1;k<=2;++k)
      for(int j=1;j<=3;++j)
        for(int i=1;i<=4;++i)
          x(i,j,k) = T(i + 10*(j+10*k));

    std::cout << x << std::endl;

    nt2::display("x", x);
    std::cout << "\n===================================================\n";
  }

  {
    T u = 0;
    nt2::table<T> x( nt2::of_size(5,4,3,2) );
    for(int l=1;l<=2;++l)
      for(int k=1;k<=3;++k)
        for(int j=1;j<=4;++j)
          for(int i=1;i<=5;++i)
            x(i,j,k,l) = u++;

    std::cout << x << std::endl;

    nt2::display("x", x);
    std::cout << "\n===================================================\n";
  }
}
