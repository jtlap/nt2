//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_UNIT_ROLL_TEST_HPP_INCLUDED
#define BOOST_SIMD_UNIT_ROLL_TEST_HPP_INCLUDED

#include <boost/simd/toolbox/swar/include/functions/shuffle.hpp>
#include <nt2/sdk/unit/tests.hpp>

//==============================================================================
template<class T, int IA, int IB>
struct roll_unary_test_2
{
  static void call( T a )
  {
    using boost::simd::shuffle;
    T ref, res;
    ref[0] = (IA == -1) ? 0 : a[IA];
    ref[1] = (IB == -1) ? 0 : a[IB];
    res = shuffle<IA,IB>(a);
    NT2_TEST_EQUAL(res,ref);
    roll_unary_test_2<T,IA+1,IB>::call(a);
  }
};

template<class T, int IB>
struct roll_unary_test_2<T,2,IB>
{
  static void call( T a ) { roll_unary_test_2<T,-1,IB+1>::call(a); }
};

template<class T>
struct roll_unary_test_2<T,-1,2> { static void call( T a ){} };

//==============================================================================
template<class T, int I0, int I1, int I2, int I3>
struct roll_unary_test_4
{
  static void call( T a )
  {
    using boost::simd::shuffle;
    T ref, res;
    ref[0] = (I0 == -1) ? 0 : a[I0];
    ref[1] = (I1 == -1) ? 0 : a[I1];
    ref[2] = (I2 == -1) ? 0 : a[I2];
    ref[3] = (I3 == -1) ? 0 : a[I3];
    res = shuffle<I0,I1,I2,I3>(a);
    NT2_TEST_EQUAL(res,ref);
    roll_unary_test_4<T,I0+1,I1,I2,I3>::call(a);
  }
};

template<class T, int I1, int I2, int I3>
struct roll_unary_test_4<T,4,I1,I2,I3>
{
  static void call( T a ) { roll_unary_test_4<T,-1,I1+1,I2,I3>::call(a); }
};

template<class T, int I2, int I3>
struct roll_unary_test_4<T,-1,4,I2,I3>
{
  static void call( T a ) { roll_unary_test_4<T,-1,-1,I2+1,I3>::call(a); }
};

template<class T, int I3>
struct roll_unary_test_4<T,-1,-1,4,I3>
{
  static void call( T a ) { roll_unary_test_4<T,-1,-1,-1,I3+1>::call(a); }
};

template<class T>
struct roll_unary_test_4<T,-1,-1,-1,4> { static void call( T a ){} };

//==============================================================================
template<class T, int IA, int IB>
struct roll_binary_test_2
{
  static void call( T a, T b)
  {
    using boost::simd::shuffle;
    T ref, res;
    ref[0] = (IA == -1) ? 0 : (IA<2 ? a[IA] : b[IA-2]);
    ref[1] = (IB == -1) ? 0 : (IB<2 ? a[IB] : b[IB-2]);
    res = shuffle<IA,IB>(a,b);
    NT2_TEST_EQUAL(res,ref);
    roll_binary_test_2<T,IA+1,IB>::call(a,b);
  }
};


template<class T, int IB>
struct roll_binary_test_2<T,4,IB>
{
  static void call( T a, T b)
  {
     roll_binary_test_2<T,-1,IB+1>::call(a,b);
  }
};

template<class T>
struct roll_binary_test_2<T,-1,4>
{
  static void call( T a, T b) {}
};

//==============================================================================
template<class T, int I0, int I1, int I2, int I3>
struct roll_binary_test_4
{
  static void call( T a, T b )
  {
    using boost::simd::shuffle;
    T ref, res;
    ref[0] = (I0 == -1) ? 0 : a[I0];
    ref[1] = (I1 == -1) ? 0 : a[I1];
    ref[2] = (I2 == -1) ? 0 : b[I2];
    ref[3] = (I3 == -1) ? 0 : b[I3];
    res = shuffle<I0,I1,I2,I3>(a,b);
    NT2_TEST_EQUAL(res,ref);
    roll_unary_test_4<T,I0+1,I1,I2,I3>::call(a,b);
  }
};

template<class T, int I1, int I2, int I3>
struct roll_binary_test_4<T,4,I1,I2,I3>
{
  static void call( T a, T b ) { roll_unary_test_4<T,-1,I1+1,I2,I3>::call(a,b); }
};

template<class T, int I2, int I3>
struct roll_binary_test_4<T,-1,4,I2,I3>
{
  static void call( T a, T b ) { roll_unary_test_4<T,-1,-1,I2+1,I3>::call(a,b); }
};

template<class T, int I3>
struct roll_binary_test_4<T,-1,-1,4,I3>
{
  static void call( T a, T b ) { roll_unary_test_4<T,-1,-1,-1,I3+1>::call(a,b); }
};

template<class T>
struct roll_binary_test_4<T,-1,-1,-1,4> { static void call( T a, T b ){} };


#endif 
