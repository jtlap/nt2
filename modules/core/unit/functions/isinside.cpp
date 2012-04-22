/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isinside function"

#include <nt2/table.hpp>
#include <nt2/include/functions/isinside.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <boost/fusion/include/vector_tie.hpp>

NT2_TEST_CASE( isinside )
{
  using nt2::table;
  using nt2::of_size;
  using boost::fusion::vector_tie;

  table<double> x( of_size(4,7) );

  for(int j=1;j<=7;++j)
    for(int i=1;i<=4;++i)
      NT2_TEST( nt2::isinside(vector_tie(i,j),x) );

  std::cout << "\n";

  for(int j=8;j<=10;++j)
    for(int i=1;i<=4;++i)
      NT2_TEST( !nt2::isinside(vector_tie(i,j),x) );

  std::cout << "\n";

  for(int j=1;j<=7;++j)
    for(int i=5;i<=9;++i)
      NT2_TEST( !nt2::isinside(vector_tie(i,j),x) );

  std::cout << "\n";

  for(int j=-2;j<1;++j)
    for(int i=-2;i<1;++i)
      NT2_TEST( !nt2::isinside(vector_tie(i,j),x) );
}
