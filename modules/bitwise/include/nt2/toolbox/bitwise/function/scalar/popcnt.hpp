//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_POPCNT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_POPCNT_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>

#include <nt2/include/functions/lo.hpp>
#include <nt2/include/functions/hi.hpp>
#include <nt2/include/functions/sbits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#ifdef BOOST_MSVC
  #include <intrin.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::popcnt_, tag::cpu_
                            , (A0)
                            , (scalar_< type32_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, unsigned>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
    #ifdef BOOST_MSVC
      return __popcnt(a0);
    #else
      return __builtin_popcount(a0); //& Mone<A0>());
    #endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::popcnt_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, unsigned>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      int64_t v = sbits(a0);
    #if defined BOOST_MSVC && defined _WIN64
      return __popcnt64(v);
    #elif defined BOOST_MSVC
      return  __popcnt( hi(v) )
            + __popcnt( lo(v) );
    #else
      return  __builtin_popcount( hi(v) )
            + __builtin_popcount( lo(v) );
    #endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::popcnt_, tag::cpu_
                            , (A0)
                            , (scalar_< float_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, unsigned>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
    #ifdef BOOST_MSVC
      return __popcnt(sbits(a0));
    #else
      return __builtin_popcount(sbits(a0));
    #endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::popcnt_, tag::cpu_
                            , (A0)
                            , (scalar_< type8_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, unsigned>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
    #ifdef BOOST_MSVC
      return __popcnt16(int16_t(a0) & 0xFF);
    #else
      return __builtin_popcount(int32_t(a0) & 0xFF);
    #endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::popcnt_, tag::cpu_
                            , (A0)
                            , (scalar_< type16_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, unsigned>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
    #ifdef BOOST_MSVC
      return __popcnt16(a0);
    #else
      return __builtin_popcount(int32_t(a0) & 0xFFFF);
    #endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::popcnt_, tag::cpu_
                            , (A0)
                            , (scalar_< type64_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, unsigned>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
    #if defined BOOST_MSVC && defined _WIN64
      return __popcnt64(a0);
    #elif defined BOOST_MSVC
      return  __popcnt( hi(a0) )
            + __popcnt( lo(a0) );
    #else
      return  __builtin_popcount( hi(a0) )
            + __builtin_popcount( lo(a0) );
    #endif
    }
  };
} }


#endif
