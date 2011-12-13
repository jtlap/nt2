//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_INSERT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_INSERT_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/insert.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>

// workaround for circular includes
namespace boost { namespace simd { namespace tag
{
  struct Allbits;
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::insert_, tag::cpu_, (A0)(A1)(A2)(X)
                            , (scalar_< arithmetic_<A0> >)
                              ((simd_< arithmetic_<A1>, X >))
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A1& result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1, A2 const& a2) const
    {
      typedef BOOST_SIMD_MAY_ALIAS typename meta::scalar_of<A1>::type stype_alias;
      reinterpret_cast<stype_alias*>(&a1)[a2] = a0;
      return a1;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::insert_, tag::cpu_, (A0)(A1)(A2)(X)
                            , (mpl::equal_to< mpl::sizeof_<A1>, mpl::sizeof_<typename A1::type> >)
                            , (scalar_< logical_<A0> >)
                              ((simd_< logical_<A1>, X >))
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A1& result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1, A2 const& a2) const
    {
      typedef typename meta::scalar_of<typename A1::type>::type type;
      type allbits = typename dispatch::make_functor<tag::Allbits, A0>::type()(dispatch::meta::as_<type>());
      insert(a0 ? allbits : a0, reinterpret_cast<typename A1::type&>(a1), a2);
      return a1;
    }
  };
  
} } }

#endif
