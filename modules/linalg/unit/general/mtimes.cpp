//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - mtimes"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of algebra components
//////////////////////////////////////////////////////////////////////////////

#include <nt2/table.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

template<class T>
struct extent_type
{
  typedef typename T::extent_type type;
};

NT2_TEST_CASE( mtimes_size )
{
  using boost::mpl::_;

  typedef double T;
  nt2::table<T, nt2::_2D> a0(nt2::of_size(5, 7));
  nt2::table<T, nt2::_4D> a1(nt2::of_size(7, 19));
  nt2::table<T, nt2::of_size_<5, 7> > a2;
  nt2::table<T, nt2::of_size_<7, 19> > a3;

  NT2_TEST_EXPR_TYPE( nt2::mtimes(a0, a1)
                    , extent_type<_>
                    , (nt2::of_size_<-1, -1>)
                    );
  NT2_TEST_EQUAL( nt2::mtimes(a0, a1).extent(), nt2::of_size(5, 19) );

  NT2_TEST_EXPR_TYPE( nt2::mtimes(a2, a3)
                    , extent_type<_>
                    , (nt2::of_size_<5, 19>)
                    );

#ifdef NT2_ASSERTS_AS_EXCEPTIONS
  NT2_TEST_THROW( nt2::mtimes(a1, a0), nt2::assert_exception );

  nt2::table<T, nt2::_4D> a4(nt2::of_size(5, 7, 1, 12));
  NT2_TEST_THROW( nt2::mtimes(a4, a1), nt2::assert_exception );
#endif
}

NT2_TEST_CASE( mtimes_reduction )
{
  typedef double T;
  using nt2::_;

  nt2::table<T> a0 = nt2::reshape(_(T(1), 5*7), nt2::of_size(5, 7));
  nt2::table<T> a1 = nt2::reshape(_(T(1), 7*19), nt2::of_size(7, 19));

  T r0[5*19] =
  {
      588,   616,   644,   672,   700,  1372,  1449,  1526,  1603,  1680,  2156,  2282,  2408,  2534,  2660,  2940,  3115,  3290,  3465,
     3640,  3724,  3948,  4172,  4396,  4620,  4508,  4781,  5054,  5327,  5600,  5292,  5614,  5936,  6258,  6580,  6076,  6447,  6818,
     7189,  7560,  6860,  7280,  7700,  8120,  8540,  7644,  8113,  8582,  9051,  9520,  8428,  8946,  9464,  9982, 10500,  9212,  9779,
    10346, 10913, 11480,  9996, 10612, 11228, 11844, 12460, 10780, 11445, 12110, 12775, 13440, 11564, 12278, 12992, 13706, 14420, 12348,
    13111, 13874, 14637, 15400, 13132, 13944, 14756, 15568, 16380, 13916, 14777, 15638, 16499, 17360, 14700, 15610, 16520, 17430, 18340
  };

  T r1[5*19] =
  {
     2072,  2184,  2296,  2408,  2520,  3640,  3850,  4060,  4270,  4480,  5208,  5516,  5824,  6132,  6440,  6776,  7182,  7588,  7994,
     8400,  8344,  8848,  9352,  9856, 10360,  9912, 10514, 11116, 11718, 12320, 11480, 12180, 12880, 13580, 14280, 13048, 13846, 14644,
    15442, 16240, 14616, 15512, 16408, 17304, 18200, 16184, 17178, 18172, 19166, 20160, 17752, 18844, 19936, 21028, 22120, 19320, 20510,
    21700, 22890, 24080, 20888, 22176, 23464, 24752, 26040, 22456, 23842, 25228, 26614, 28000, 24024, 25508, 26992, 28476, 29960, 25592,
    27174, 28756, 30338, 31920, 27160, 28840, 30520, 32200, 33880, 28728, 30506, 32284, 34062, 35840, 30296, 32172, 34048, 35924, 37800
  };

  nt2::table<T> r;
  r = nt2::mtimes(a0, a1);

  for(std::size_t j=0; j!=19; ++j)
    for(std::size_t i=0; i!=5; ++i)
      NT2_TEST_EQUAL( r(i+1, j+1), r0[j*5+i] );

  r = nt2::mtimes(T(2)*a0, a1+T(4));
  for(std::size_t j=0; j!=19; ++j)
    for(std::size_t i=0; i!=5; ++i)
      NT2_TEST_EQUAL( r(i+1, j+1), r1[j*5+i] );

  r = nt2::mtimes(T(2)*a0, a1+T(4)) / T(10);
  for(std::size_t j=0; j!=19; ++j)
    for(std::size_t i=0; i!=5; ++i)
      NT2_TEST_EQUAL( r(i+1, j+1), r1[j*5+i] / T(10) );
}
