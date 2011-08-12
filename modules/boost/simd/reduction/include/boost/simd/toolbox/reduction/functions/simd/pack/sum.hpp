//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_PACK_SUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_PACK_SUM_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/dsl/terminal_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implementation when type  is expression of pack
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::sum_, tag::cpu_
                            , (A0)(T)(Card)(Tag)(Sema)
                            , ((expr_<A0, domain_< simd::domain<T,Card> >, Tag, Sema>))
                            )
  {

    typedef T result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typename boost::mpl::apply< boost::dispatch::meta::terminal_of<A0>, T>::type  that;
      that = a0;
      return boost::simd::sum(that.value().value());
    }
  };
} } }


#endif
