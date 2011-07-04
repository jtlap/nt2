//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_FINITE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_FINITE_HPP_INCLUDED
#include <boost/simd/include/functions/boolean.hpp>
#include <boost/simd/sdk/details/ignore_unused.hpp>

#include <boost/simd/include/functions/is_eqz.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::is_finite_, tag::cpu_
                            , (A0)
                            , (scalar_< fundamental_<A0> >)
                            )
  {

    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return True<A0>();
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::is_finite_, tag::cpu_
                            , (A0)
                            , (scalar_< real_<A0> >)
                            )
  {

    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return is_eqz(a0-a0);
    }
  };
} } }


#endif
