/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::constants eps related"

#include <nt2/sdk/meta/supported_types.hpp>
#include <nt2/sdk/constant/eps_related.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of eps constants for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( double_eps_value )
{
  NT2_TEST_EQUAL( nt2::Eps<double>()            , 2.220446049250313e-16 );
  NT2_TEST_EQUAL( nt2::Halfeps<double>()        , 1.1102230246251565e-16 );
  NT2_TEST_EQUAL( nt2::Threeeps<double>()       , static_cast<double>(-1./2. ) );
  NT2_TEST_EQUAL( nt2::Sqrteps<double>()        , static_cast<double>(-1./2. ) );
  NT2_TEST_EQUAL( nt2::Forthrooteps<double>()   , static_cast<double>(-1./2. ) );
  NT2_TEST_EQUAL( nt2::Thirdrooteps<double>()   , static_cast<double>(-1./2. ) );
  NT2_TEST_EQUAL( nt2::Mlogeps2<double>()       , static_cast<double>(-1./2. ) );
  NT2_TEST_EQUAL( nt2::Mindenormal<double>()    , static_cast<double>(-1./2. ) );
  NT2_TEST_EQUAL( nt2::Smallestposval<double>() , static_cast<double>(-1./2. ) );
}

/*
  LOCAL_CONST(eps__            ,0xLL,,1);
  LOCAL_CONST(half_eps__       ,0xll,,1);
  LOCAL_CONST(_3_x_eps_        ,0x3cde03af9ee75615ll,0x,1);
  LOCAL_CONST(sqrt_eps_        ,0x3e50000000000000ll,0x,3);
  LOCAL_CONST(forth_root_eps_  ,0x3f20000000000000ll,0x,1);
  LOCAL_CONST(third_root_eps_  ,0x3ed965fea53d6e42ll,0x,1);
  LOCAL_CONST(mlog_eps_2_      ,0x403205966f2b4f13ll,0x,0);
  LOCAL_CONST(min_denormal_    ,0x1ll               ,0x1       ,1);
  LOCAL_CONST(smallest_pos_val_,0x0010000000000000LL,0x,1);
*/

NT2_TEST_CASE( float_eps_value )
{
  NT2_TEST_EQUAL( nt2::Eps<float>()             , 1.1920928955078125e-7  );
  NT2_TEST_EQUAL( nt2::Halfeps<float>()         , 5.960464477539063e-8   );
  NT2_TEST_EQUAL( nt2::Threeeps<float>()        , 3.5762786865234375e-7  );
  NT2_TEST_EQUAL( nt2::Sqrteps<float>()         , 0.0003452669770922512  );
  NT2_TEST_EQUAL( nt2::Forthrooteps<float>()    , 0.018581360578536987   );
  NT2_TEST_EQUAL( nt2::Thirdrooteps<float>()    , 0.004921566694974899   );
  NT2_TEST_EQUAL( nt2::Mlogeps2<float>()        , 7.971192359924316      );
  NT2_TEST_EQUAL( nt2::Mindenormal<float>()     , 1.401298464324817e-45  );
  NT2_TEST_EQUAL( nt2::Smallestposval<float>()  , 1.1754943508222875e-38 );
}

////////////////////////////////////////////////////////////////////////////////
// Test value of eps constants for every base integral types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( real_value, NT2_INTEGRAL_TYPES )
{
  NT2_TEST_EQUAL( nt2::Eps<T>()             , 1 );
  NT2_TEST_EQUAL( nt2::Halfeps<T>()         , 1 );
  NT2_TEST_EQUAL( nt2::Threeeps<T>()        , 1 );
  NT2_TEST_EQUAL( nt2::Sqrteps<T>()         , 3 );
  NT2_TEST_EQUAL( nt2::Forthrooteps<T>()    , 1 );
  NT2_TEST_EQUAL( nt2::Thirdrooteps<T>()    , 1 );
  NT2_TEST_EQUAL( nt2::Mlogeps2<T>()        , 0 );
  NT2_TEST_EQUAL( nt2::Mindenormal<T>()     , 1 );
  NT2_TEST_EQUAL( nt2::Smallestposval<T>()  , 1 );
}
