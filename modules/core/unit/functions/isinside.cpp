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
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/none.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/simd/sdk/simd/native.hpp>

NT2_TEST_CASE( isinside_scalar )
{
  using nt2::table;
  using nt2::of_size;
  using boost::fusion::vector_tie;

  table<double> x( of_size(4,7) );

  for(std::size_t j=1;j<=7;++j)
    for(std::size_t i=1;i<=4;++i)
      NT2_TEST( nt2::isinside(vector_tie(i,j),x) );

  std::cout << "\n";

  for(std::size_t j=8;j<=10;++j)
    for(std::size_t i=1;i<=4;++i)
      NT2_TEST( !nt2::isinside(vector_tie(i,j),x) );

  std::cout << "\n";

  for(std::size_t j=1;j<=7;++j)
    for(std::size_t i=5;i<=9;++i)
      NT2_TEST( !nt2::isinside(vector_tie(i,j),x) );

  std::cout << "\n";

  for(std::size_t j=0;j<1;++j)
    for(std::size_t i=0;i<1;++i)
      NT2_TEST( !nt2::isinside(vector_tie(i,j),x) );
}

NT2_TEST_CASE( isinside_simd )
{
  using nt2::table;
  using nt2::of_size;
  using boost::fusion::make_vector;

  table<double> x( of_size(8,7) );

  typedef boost::simd::native<std::size_t,BOOST_SIMD_DEFAULT_EXTENSION> n_t;
  std::size_t step = boost::simd::meta::cardinal_of<n_t>::value;

  for(std::size_t j=1;j<=7;++j)
    for(std::size_t i=1;i<=8;i+=step)
      NT2_TEST( nt2::all(nt2::isinside(make_vector(nt2::enumerate<n_t>(i),nt2::splat<n_t>(j)),x)) );

  std::cout << "\n";

  for(std::size_t j=8;j<=10;++j)
    for(std::size_t i=1;i<=8;i+=step)
      NT2_TEST( !nt2::all(nt2::isinside(make_vector(nt2::enumerate<n_t>(i),nt2::splat<n_t>(j)),x)) );

  std::cout << "\n";

  for(std::size_t j=1;j<=7;++j)
    for(std::size_t i=9;i<=12;i+=step)
      NT2_TEST( !nt2::all(nt2::isinside(make_vector(nt2::enumerate<n_t>(i),nt2::splat<n_t>(j)),x)) );

  std::cout << "\n";

  for(std::size_t j=0;j<1;++j)
    for(std::size_t i=0;i<1;i+=step)
      NT2_TEST( !nt2::all(nt2::isinside(make_vector(nt2::enumerate<n_t>(i),nt2::splat<n_t>(j)),x)) );
}
