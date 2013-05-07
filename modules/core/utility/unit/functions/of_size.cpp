//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings of_size helper"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/of_size.hpp>

#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

////////////////////////////////////////////////////////////////////////////
////// Test of_size initializations
////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( empty_of_size )
{
  nt2::_1D  spec1;
  NT2_TEST_EQUAL( spec1.size(), 1u );
  NT2_TEST_EQUAL( spec1[0], 0u );

  nt2::_2D  spec2;
  NT2_TEST_EQUAL( spec2.size(), 2u );
  NT2_TEST_EQUAL( spec2[0], 0u );
  NT2_TEST_EQUAL( spec2[1], 1u );

  nt2::_3D  spec3;
  NT2_TEST_EQUAL( spec3.size(), 3u );
  NT2_TEST_EQUAL( spec3[0], 0u );
  NT2_TEST_EQUAL( spec3[1], 1u );
  NT2_TEST_EQUAL( spec3[2], 1u );

  nt2::_4D  spec4;
  NT2_TEST_EQUAL( spec4.size(), 4u );
  NT2_TEST_EQUAL( spec4[0], 0u );
  NT2_TEST_EQUAL( spec4[1], 1u );
  NT2_TEST_EQUAL( spec4[2], 1u );
  NT2_TEST_EQUAL( spec4[2], 1u );

  nt2::_0D  spec0;
  NT2_TEST_EQUAL( spec0.size(), 0u );
}

////////////////////////////////////////////////////////////////////////
// Test of_size pre-initializations in case of static sizes
////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( init_of_size )
{
  using nt2::of_size_;

  of_size_<42>     spec1;
  NT2_TEST_EQUAL( spec1.size(), 1u );
  NT2_TEST_EQUAL( spec1[0], 42u );

  of_size_<42>     spec1d(42);
  NT2_TEST_EQUAL( spec1d.size(), 1u );
  NT2_TEST_EQUAL( spec1d[0], 42u );

  NT2_TEST_ASSERT( (of_size_<42> spec1b(63)) );
  NT2_TEST_ASSERT( (of_size_<42> spec1b(2,21)) );
  NT2_TEST_ASSERT( (of_size_<42> spec1b(2,3,7)) );
  NT2_TEST_ASSERT( (of_size_<42> spec1b(2,1,3,7)) );

  of_size_<6,9>     spec2;
  NT2_TEST_EQUAL( spec2.size(), 2u );
  NT2_TEST_EQUAL( spec2[0], 6u );
  NT2_TEST_EQUAL( spec2[1], 9u );

  NT2_TEST_ASSERT( (of_size_<6,9> spec2b(54)) );
  NT2_TEST_ASSERT( (of_size_<6,9> spec2b(3,2,9)) );
  NT2_TEST_ASSERT( (of_size_<6,9> spec2b(3,1,6,3)) );

  of_size_<4,2,6>     spec3;
  NT2_TEST_EQUAL( spec3.size(), 3u );
  NT2_TEST_EQUAL( spec3[0], 4u );
  NT2_TEST_EQUAL( spec3[1], 2u );
  NT2_TEST_EQUAL( spec3[2], 6u );

  NT2_TEST_ASSERT( (of_size_<4,2,6> spec3b(48)) );
  NT2_TEST_ASSERT( (of_size_<4,2,6> spec3b(4,12)) );
  NT2_TEST_ASSERT( (of_size_<4,2,6> spec3b(4,1,6,2)) );

  of_size_<1,3,5,7>     spec4;
  NT2_TEST_EQUAL( spec4.size(), 4u );
  NT2_TEST_EQUAL( spec4[0], 1u );
  NT2_TEST_EQUAL( spec4[1], 3u );
  NT2_TEST_EQUAL( spec4[2], 5u );
  NT2_TEST_EQUAL( spec4[3], 7u );

  NT2_TEST_ASSERT( (of_size_<1,3,5,7> spec4b(105)) );
  NT2_TEST_ASSERT( (of_size_<1,3,5,7> spec4b(3,35)) );
  NT2_TEST_ASSERT( (of_size_<1,3,5,7> spec4b(45,1,7)) );
}

////////////////////////////////////////////////////////////////////////
// Test of_size function calls
////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( of_size_call )
{
  using nt2::of_size;
  using nt2::_4D;
  using nt2::_3D;
  using nt2::_2D;
  using nt2::_1D;

  _4D s4 = of_size(2,3,4,5);
  NT2_TEST_EQUAL( s4.size(), 4u );
  NT2_TEST_EQUAL( s4[0], 2u );
  NT2_TEST_EQUAL( s4[1], 3u );
  NT2_TEST_EQUAL( s4[2], 4u );
  NT2_TEST_EQUAL( s4[3], 5u );

  _3D s3 = of_size(2,3,4);
  NT2_TEST_EQUAL( s3.size(), 3u );
  NT2_TEST_EQUAL( s3[0], 2u );
  NT2_TEST_EQUAL( s3[1], 3u );
  NT2_TEST_EQUAL( s3[2], 4u );

  _2D s2 = of_size(2,3);
  NT2_TEST_EQUAL( s2.size(), 2u );
  NT2_TEST_EQUAL( s2[0], 2u );
  NT2_TEST_EQUAL( s2[1], 3u );

  _1D s1 = of_size(2);
  NT2_TEST_EQUAL( s1.size(), 1u );
  NT2_TEST_EQUAL( s1[0], 2u );
}

////////////////////////////////////////////////////////////////////////
// Test of_size initialisation from a Fusion Sequence
////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( dynamic_of_size_from_fusion )
{
  using nt2::of_size_;
  boost::array<std::ptrdiff_t,NT2_MAX_DIMENSIONS> tab = {{2,2,2,2}};

  of_size_<-1>    _1Dtarget(tab);
  NT2_TEST_EQUAL( _1Dtarget.size(), 1u );
  NT2_TEST_EQUAL( _1Dtarget[0], 16u );

  of_size_<-1,-1>    _2Dtarget(tab);
  NT2_TEST_EQUAL( _2Dtarget.size(), 2u );
  NT2_TEST_EQUAL( _2Dtarget[0], 2u );
  NT2_TEST_EQUAL( _2Dtarget[1], 8u );

  of_size_<-1,-1,-1>    _3Dtarget(tab);
  NT2_TEST_EQUAL( _3Dtarget.size(), 3u );
  NT2_TEST_EQUAL( _3Dtarget[0], 2u );
  NT2_TEST_EQUAL( _3Dtarget[1], 2u );
  NT2_TEST_EQUAL( _3Dtarget[2], 4u );

  of_size_<-1,-1,-1,-1>    _4Dtarget(tab);
  NT2_TEST_EQUAL( _4Dtarget.size(), 4u );
  NT2_TEST_EQUAL( _4Dtarget[0], 2u );
  NT2_TEST_EQUAL( _4Dtarget[1], 2u );
  NT2_TEST_EQUAL( _4Dtarget[2], 2u );
  NT2_TEST_EQUAL( _4Dtarget[3], 2u );
}

////////////////////////////////////////////////////////////////////////
// Test static of_size initialisation from a Fusion Sequence
////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( static_of_size_from_fusion )
{
  using nt2::of_size_;
  boost::array<std::ptrdiff_t,NT2_MAX_DIMENSIONS> tab = {{2,2,2,2}};

  of_size_<16>    _1Dtarget(tab);
  NT2_TEST_EQUAL( _1Dtarget.size(), 1u );
  NT2_TEST_EQUAL( _1Dtarget[0], 16u );

  of_size_<2,8>    _2Dtarget(tab);
  NT2_TEST_EQUAL( _2Dtarget.size(), 2u );
  NT2_TEST_EQUAL( _2Dtarget[0], 2u );
  NT2_TEST_EQUAL( _2Dtarget[1], 8u );

  of_size_<2,2,4>    _3Dtarget(tab);
  NT2_TEST_EQUAL( _3Dtarget.size(), 3u );
  NT2_TEST_EQUAL( _3Dtarget[0], 2u );
  NT2_TEST_EQUAL( _3Dtarget[1], 2u );
  NT2_TEST_EQUAL( _3Dtarget[2], 4u );

  of_size_<2,2,2,2>    _4Dtarget(tab);
  NT2_TEST_EQUAL( _4Dtarget.size(), 4u );
  NT2_TEST_EQUAL( _4Dtarget[0], 2u );
  NT2_TEST_EQUAL( _4Dtarget[1], 2u );
  NT2_TEST_EQUAL( _4Dtarget[2], 2u );
  NT2_TEST_EQUAL( _4Dtarget[3], 2u );
}

////////////////////////////////////////////////////////////////////////
// Test of_size function calls - Range constructor
////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( of_size_range )
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::_4D;
  using nt2::_3D;
  using nt2::_2D;
  using nt2::_1D;
  using nt2::_0D;

  std::size_t range[4]   = {2,3,4,5};
  std::size_t range11[4] = {2,1,1,1};
  std::size_t range21[4] = {2,3,1,1};
  std::size_t range31[4] = {2,3,4,1};
  std::size_t ones[4]    = {1,1,1,1};

  // 0D: Any range size
  _0D s01(&ones[0],&ones[0]+1);
  NT2_TEST_EQUAL( s01.size(), 0u );

  _0D s02(&ones[0],&ones[0]+2);

  _0D s03(&ones[0],&ones[0]+3);
  NT2_TEST_EQUAL( s03.size(), 0u );

  _0D s04(&ones[0],&ones[0]+4);
  NT2_TEST_EQUAL( s04.size(), 0u );

  NT2_TEST_ASSERT( (_0D ss(&range[0],&range[0]+1)) );
  NT2_TEST_ASSERT( (_0D ss(&range[0],&range[0]+2)) );
  NT2_TEST_ASSERT( (_0D ss(&range[0],&range[0]+3)) );
  NT2_TEST_ASSERT( (_0D ss(&range[0],&range[0]+4)) );

  // 1D: Exact range size
  _1D s11(&range[0],&range[0]+1);
  NT2_TEST_EQUAL( s11.size(), 1u );
  NT2_TEST_EQUAL( s11[0], 2u );

  _1D s114(&range11[0],&range11[0]+4);
  NT2_TEST_EQUAL( s114.size(), 1u );
  NT2_TEST_EQUAL( s114[0], 2u );

  // 1D: Bigger range size
  NT2_TEST_ASSERT( (_1D ss(&range[0],&range[0]+2)) );
  NT2_TEST_ASSERT( (_1D ss(&range[0],&range[0]+3)) );
  NT2_TEST_ASSERT( (_1D ss(&range[0],&range[0]+4)) );

  // 2D: Smaller range size
  _2D s21(&range[0],&range[0]+1);
  NT2_TEST_EQUAL( s21.size(), 2u );
  NT2_TEST_EQUAL( s21[0], 2u );
  NT2_TEST_EQUAL( s21[1], 1u );

  // 2D: Exact range size
  _2D s22(&range[0],&range[0]+2);
  NT2_TEST_EQUAL( s22.size(), 2u );
  NT2_TEST_EQUAL( s22[0], 2u );
  NT2_TEST_EQUAL( s22[1], 3u );

  _2D s224(&range21[0],&range21[0]+4);
  NT2_TEST_EQUAL( s224.size(), 2u );
  NT2_TEST_EQUAL( s224[0], 2u );
  NT2_TEST_EQUAL( s224[1], 3u );

  // 2D: Bigger range size
  NT2_TEST_ASSERT( (_2D ss(&range[0],&range[0]+3)) );
  NT2_TEST_ASSERT( (_2D ss(&range[0],&range[0]+4)) );

  // 3D: Smaller range size
  _3D s31(&range[0],&range[0]+1);
  NT2_TEST_EQUAL( s31.size(), 3u );
  NT2_TEST_EQUAL( s31[0], 2u );
  NT2_TEST_EQUAL( s31[1], 1u );
  NT2_TEST_EQUAL( s31[2], 1u );

  _3D s32(&range[0],&range[0]+2);
  NT2_TEST_EQUAL( s32.size(), 3u );
  NT2_TEST_EQUAL( s32[0], 2u );
  NT2_TEST_EQUAL( s32[1], 3u );
  NT2_TEST_EQUAL( s32[2], 1u );

  // 3D: Exact range size
  _3D s33(&range[0],&range[0]+3);
  NT2_TEST_EQUAL( s33.size(), 3u );
  NT2_TEST_EQUAL( s33[0], 2u );
  NT2_TEST_EQUAL( s33[1], 3u );
  NT2_TEST_EQUAL( s33[2], 4u );

  _3D s334(&range31[0],&range31[0]+4);
  NT2_TEST_EQUAL( s33.size(), 3u );
  NT2_TEST_EQUAL( s33[0], 2u );
  NT2_TEST_EQUAL( s33[1], 3u );
  NT2_TEST_EQUAL( s33[2], 4u );

  // 3D: Bigger range size
  NT2_TEST_ASSERT( (_3D ss(&range[0],&range[0]+4)) );

  // 4D: Smaller range size
  _4D s41(&range[0],&range[0]+1);
  NT2_TEST_EQUAL( s41.size(), 4u );
  NT2_TEST_EQUAL( s41[0], 2u );
  NT2_TEST_EQUAL( s41[1], 1u );
  NT2_TEST_EQUAL( s41[2], 1u );
  NT2_TEST_EQUAL( s41[3], 1u );

  _4D s42(&range[0],&range[0]+2);
  NT2_TEST_EQUAL( s42.size(), 4u );
  NT2_TEST_EQUAL( s42[0], 2u );
  NT2_TEST_EQUAL( s42[1], 3u );
  NT2_TEST_EQUAL( s42[2], 1u );
  NT2_TEST_EQUAL( s42[3], 1u );

  _4D s43 = of_size(&range[0],&range[0]+3);
  NT2_TEST_EQUAL( s43.size(), 4u );
  NT2_TEST_EQUAL( s43[0], 2u );
  NT2_TEST_EQUAL( s43[1], 3u );
  NT2_TEST_EQUAL( s43[2], 4u );
  NT2_TEST_EQUAL( s43[3], 1u );

  // 4D: Exact range size
  _4D s4(&range[0],&range[0]+4);
  NT2_TEST_EQUAL( s4.size(), 4u );
  NT2_TEST_EQUAL( s4[0], 2u );
  NT2_TEST_EQUAL( s4[1], 3u );
  NT2_TEST_EQUAL( s4[2], 4u );
  NT2_TEST_EQUAL( s4[3], 5u );
}

////////////////////////////////////////////////////////////////////////////////
// Test of_size constructor with more elements
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( of_size_extra_constructor )
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::_4D;
  using nt2::_3D;
  using nt2::_2D;
  using nt2::_1D;
  using nt2::_0D;

  _0D s01(1);
  NT2_TEST_EQUAL( s01.size(), 0u );
  _0D s02(1,1);
  NT2_TEST_EQUAL( s02.size(), 0u );
  _0D s03(1,boost::mpl::int_<1>(),1);
  NT2_TEST_EQUAL( s03.size(), 0u );
  _0D s04(1,1,1,boost::mpl::int_<1>());
  NT2_TEST_EQUAL( s04.size(), 0u );

  NT2_TEST_ASSERT( (_0D ss(3)      ) );
  NT2_TEST_ASSERT( (_0D ss(2,2)    ) );
  NT2_TEST_ASSERT( (_0D ss(3,1,3)  ) );
  NT2_TEST_ASSERT( (_0D ss(4,1,3,1)) );

  _1D s11(2);
  NT2_TEST_EQUAL( s11.size(), 1u );
  NT2_TEST_EQUAL( s11[0], 2u );
  _1D s12(2,1);
  NT2_TEST_EQUAL( s12.size(), 1u );
  NT2_TEST_EQUAL( s12[0], 2u );
  _1D s13(2,boost::mpl::int_<1>(),1);
  NT2_TEST_EQUAL( s13.size(), 1u );
  NT2_TEST_EQUAL( s13[0], 2u );
  _1D s14(2,1,1,boost::mpl::int_<1>());
  NT2_TEST_EQUAL( s14.size(), 1u );
  NT2_TEST_EQUAL( s14[0], 2u );

  NT2_TEST_ASSERT( (_1D ss(2,2)    ) );
  NT2_TEST_ASSERT( (_1D ss(3,1,3)  ) );
  NT2_TEST_ASSERT( (_1D ss(4,1,3,1)) );

  of_size_<2> sd11(2);
  NT2_TEST_EQUAL( sd11.size(), 1u );
  NT2_TEST_EQUAL( sd11[0], 2u );
  of_size_<2> sd12(2,1);
  NT2_TEST_EQUAL( sd12.size(), 1u );
  NT2_TEST_EQUAL( sd12[0], 2u );
  of_size_<2> sd13(2,1,1);
  NT2_TEST_EQUAL( sd13.size(), 1u );
  NT2_TEST_EQUAL( sd13[0], 2u );
  of_size_<2> sd14(2,1,1,1);
  NT2_TEST_EQUAL( sd14.size(), 1u );
  NT2_TEST_EQUAL( sd14[0], 2u );

  NT2_TEST_ASSERT( (of_size_<2> ss(3)      ) );
  NT2_TEST_ASSERT( (of_size_<2> ss(2,2)    ) );
  NT2_TEST_ASSERT( (of_size_<2> ss(3,1,3)  ) );
  NT2_TEST_ASSERT( (of_size_<2> ss(4,1,3,1)) );

  _2D s21(2);
  NT2_TEST_EQUAL( s21.size(), 2u );
  NT2_TEST_EQUAL( s21[0], 2u );
  NT2_TEST_EQUAL( s21[1], 1u );
  _2D s22(2,3);
  NT2_TEST_EQUAL( s22.size(), 2u );
  NT2_TEST_EQUAL( s22[0], 2u );
  NT2_TEST_EQUAL( s22[1], 3u );
  _2D s23(2,3,1);
  NT2_TEST_EQUAL( s23.size(), 2u );
  NT2_TEST_EQUAL( s23[0], 2u );
  NT2_TEST_EQUAL( s23[1], 3u );
  _2D s24(2,3,1,1);
  NT2_TEST_EQUAL( s24.size(), 2u );
  NT2_TEST_EQUAL( s24[0], 2u );
  NT2_TEST_EQUAL( s24[1], 3u );

  NT2_TEST_ASSERT( (_2D ss(2,1,3)  ) );
  NT2_TEST_ASSERT( (_2D ss(2,1,3,4)) );

  of_size_<2,3> sd21(2);
  NT2_TEST_EQUAL( sd21.size(), 2u );
  NT2_TEST_EQUAL( sd21[0], 2u );
  NT2_TEST_EQUAL( sd21[1], 3u );
  of_size_<2,3> sd22(2,3);
  NT2_TEST_EQUAL( sd22.size(), 2u );
  NT2_TEST_EQUAL( sd22[0], 2u );
  NT2_TEST_EQUAL( sd22[1], 3u );
  of_size_<2,3> sd23(2,3,1);
  NT2_TEST_EQUAL( sd23.size(), 2u );
  NT2_TEST_EQUAL( sd23[0], 2u );
  NT2_TEST_EQUAL( sd23[1], 3u );
  of_size_<2,3> sd24(2,3,1,1);
  NT2_TEST_EQUAL( sd24.size(), 2u );
  NT2_TEST_EQUAL( sd24[0], 2u );
  NT2_TEST_EQUAL( sd24[1], 3u );

  NT2_TEST_ASSERT( (of_size_<2,3> ss(3)      ) );
  NT2_TEST_ASSERT( (of_size_<2,3> ss(2,2)    ) );
  NT2_TEST_ASSERT( (of_size_<2,3> ss(2,3,3)  ) );
  NT2_TEST_ASSERT( (of_size_<2,3> ss(2,3,4,1)) );

  _3D s31(3);
  NT2_TEST_EQUAL( s31.size(), 3u );
  NT2_TEST_EQUAL( s31[0], 3u );
  NT2_TEST_EQUAL( s31[1], 1u );
  NT2_TEST_EQUAL( s31[2], 1u );
  _3D s32(3,4);
  NT2_TEST_EQUAL( s32.size(), 3u );
  NT2_TEST_EQUAL( s32[0], 3u );
  NT2_TEST_EQUAL( s32[1], 4u );
  NT2_TEST_EQUAL( s32[2], 1u );
  _3D s33(3,4,5);
  NT2_TEST_EQUAL( s33.size(), 3u );
  NT2_TEST_EQUAL( s33[0], 3u );
  NT2_TEST_EQUAL( s33[1], 4u );
  NT2_TEST_EQUAL( s33[2], 5u );
  _3D s34(3,4,5,1);
  NT2_TEST_EQUAL( s34.size(), 3u );
  NT2_TEST_EQUAL( s34[0], 3u );
  NT2_TEST_EQUAL( s34[1], 4u );
  NT2_TEST_EQUAL( s34[2], 5u );

  NT2_TEST_ASSERT( (_3D ss(2,1,3,5)) );

  of_size_<2,3,4> sd31(2);
  NT2_TEST_EQUAL( sd31.size(), 3u );
  NT2_TEST_EQUAL( sd31[0], 2u );
  NT2_TEST_EQUAL( sd31[1], 3u );
  NT2_TEST_EQUAL( sd31[2], 4u );
  of_size_<2,3,4> sd32(2,3);
  NT2_TEST_EQUAL( sd32.size(), 3u );
  NT2_TEST_EQUAL( sd32[0], 2u );
  NT2_TEST_EQUAL( sd32[1], 3u );
  NT2_TEST_EQUAL( sd32[2], 4u );
  of_size_<2,3,4> sd33(2,3,4);
  NT2_TEST_EQUAL( sd33.size(), 3u );
  NT2_TEST_EQUAL( sd33[0], 2u );
  NT2_TEST_EQUAL( sd33[1], 3u );
  NT2_TEST_EQUAL( sd33[2], 4u );
  of_size_<2,3,4> sd34(2,3,4,1);
  NT2_TEST_EQUAL( sd34.size(), 3u );
  NT2_TEST_EQUAL( sd34[0], 2u );
  NT2_TEST_EQUAL( sd34[1], 3u );
  NT2_TEST_EQUAL( sd34[2], 4u );

  NT2_TEST_ASSERT( (of_size_<2,3,4> ss(3)      ) );
  NT2_TEST_ASSERT( (of_size_<2,3,4> ss(2,2)    ) );
  NT2_TEST_ASSERT( (of_size_<2,3,4> ss(2,3,3)  ) );
  NT2_TEST_ASSERT( (of_size_<2,3,4> ss(2,3,4,5)) );

  _4D s41(4);
  NT2_TEST_EQUAL( s41.size(), 4u );
  NT2_TEST_EQUAL( s41[0], 4u );
  NT2_TEST_EQUAL( s41[1], 1u );
  NT2_TEST_EQUAL( s41[2], 1u );
  NT2_TEST_EQUAL( s41[3], 1u );
  _4D s42(4,5);
  NT2_TEST_EQUAL( s42.size(), 4u );
  NT2_TEST_EQUAL( s42[0], 4u );
  NT2_TEST_EQUAL( s42[1], 5u );
  NT2_TEST_EQUAL( s42[2], 1u );
  _4D s43(4,5,6);
  NT2_TEST_EQUAL( s43.size(), 4u );
  NT2_TEST_EQUAL( s43[0], 4u );
  NT2_TEST_EQUAL( s43[1], 5u );
  NT2_TEST_EQUAL( s43[2], 6u );
  NT2_TEST_EQUAL( s43[3], 1u );
  _4D s44(4,5,6,7);
  NT2_TEST_EQUAL( s44.size(), 4u );
  NT2_TEST_EQUAL( s44[0], 4u );
  NT2_TEST_EQUAL( s44[1], 5u );
  NT2_TEST_EQUAL( s44[2], 6u );
  NT2_TEST_EQUAL( s44[3], 7u );

  of_size_<2,3,4,5> sd41(2);
  NT2_TEST_EQUAL( sd41.size(), 4u );
  NT2_TEST_EQUAL( sd41[0], 2u );
  NT2_TEST_EQUAL( sd41[1], 3u );
  NT2_TEST_EQUAL( sd41[2], 4u );
  NT2_TEST_EQUAL( sd41[3], 5u );
  of_size_<2,3,4,5> sd42(2,3);
  NT2_TEST_EQUAL( sd42.size(), 4u );
  NT2_TEST_EQUAL( sd42[0], 2u );
  NT2_TEST_EQUAL( sd42[1], 3u );
  NT2_TEST_EQUAL( sd42[2], 4u );
  NT2_TEST_EQUAL( sd42[3], 5u );
  of_size_<2,3,4,5> sd43(2,3,4);
  NT2_TEST_EQUAL( sd43.size(), 4u );
  NT2_TEST_EQUAL( sd43[0], 2u );
  NT2_TEST_EQUAL( sd43[1], 3u );
  NT2_TEST_EQUAL( sd43[2], 4u );
  NT2_TEST_EQUAL( sd43[3], 5u );
  of_size_<2,3,4,5> sd44(2,3,4,5);
  NT2_TEST_EQUAL( sd44.size(), 4u );
  NT2_TEST_EQUAL( sd44[0], 2u );
  NT2_TEST_EQUAL( sd44[1], 3u );
  NT2_TEST_EQUAL( sd44[2], 4u );
  NT2_TEST_EQUAL( sd44[3], 5u );

  NT2_TEST_ASSERT( (of_size_<2,3,4,5> ss(3)      ) );
  NT2_TEST_ASSERT( (of_size_<2,3,4,5> ss(2,2)    ) );
  NT2_TEST_ASSERT( (of_size_<2,3,4,5> ss(2,3,3)  ) );
  NT2_TEST_ASSERT( (of_size_<2,3,4,5> ss(2,3,4,7)) );
}

////////////////////////////////////////////////////////////////////////////////
// Test of_size equality operator
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( of_size_equality )
{
  using nt2::_4D;
  using nt2::_3D;
  using nt2::_2D;
  using nt2::_1D;
  using nt2::of_size;
  using nt2::of_size_;

  of_size_<>        s0;
  of_size_<2>       s1;
  of_size_<2,3>     s2;
  of_size_<2,3,4>   s3;
  of_size_<2,3,4,5> s4;

  _1D d1(2);
  _2D d2(2,3);
  _3D d3(2,3,4);
  _4D d4(2,3,4,5);

  _2D d12(2,1);
  _3D d13(2,1,1);
  _4D d14(2,1,1,1);

  // Test that _0D compares to [1 ... ]
  NT2_TEST_EQUAL( s0, of_size(1 )      );
  NT2_TEST_EQUAL( s0, of_size(1,1 )    );
  NT2_TEST_EQUAL( s0, of_size(1,1,1 )  );
  NT2_TEST_EQUAL( s0, of_size(1,1,1,1 ));

  // Test that static and dynamic of_size compares
  NT2_TEST_EQUAL( s1, d1 );
  NT2_TEST_EQUAL( s2, d2 );
  NT2_TEST_EQUAL( s3, d3 );
  NT2_TEST_EQUAL( s4, d4 );

  // Test out of dims comparison
  NT2_TEST_EQUAL( s1, d12 );
  NT2_TEST_EQUAL( s1, d13 );
  NT2_TEST_EQUAL( s1, d14 );

  // Test that stuff don't compare wrongly
  NT2_TEST_NOT_EQUAL( s4, s1 );
  NT2_TEST_NOT_EQUAL( s4, s2 );
  NT2_TEST_NOT_EQUAL( s4, s3 );

  NT2_TEST_NOT_EQUAL( s4, d1 );
  NT2_TEST_NOT_EQUAL( s4, d2 );
  NT2_TEST_NOT_EQUAL( s4, d3 );

  NT2_TEST_NOT_EQUAL( d4, s1 );
  NT2_TEST_NOT_EQUAL( d4, s2 );
  NT2_TEST_NOT_EQUAL( d4, s3 );

  NT2_TEST_NOT_EQUAL( d4, d1 );
  NT2_TEST_NOT_EQUAL( d4, d2 );
  NT2_TEST_NOT_EQUAL( d4, d3 );
}
