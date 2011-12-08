//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_NATIVE_CAST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_NATIVE_CAST_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/native_cast.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::native_cast_, tag::cpu_, (A0)(A1)(X)
                            , (mpl::and_<
                                 boost::simd::meta::is_simd_specific<A0, typename A1::type::extension_type>
                               , mpl::equal_to< mpl::sizeof_<A0>, mpl::sizeof_<typename A1::type> >
                               >
                              )
                            , (unspecified_<A0>)
                              ((target_<simd_<unspecified_<A1>, X> >))
                            )
  {
    typedef typename dispatch::meta::call<tag::bitwise_cast_(A0 const&, A1 const&)>::type result_type;
      
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return bitwise_cast<typename A1::type>(a0);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::native_cast_, tag::cpu_, (A0)(A1)(X)
                            , (mpl::equal_to< mpl::sizeof_<A0>, mpl::sizeof_<typename A1::type> >)
                            , ((simd_< unspecified_<A0>, X>))
                              ((target_<simd_<unspecified_<A1>, X> >))
                            )
  {
    typedef typename dispatch::meta::call<tag::bitwise_cast_(A0 const&, A1 const&)>::type result_type;
      
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return bitwise_cast<typename A1::type>(a0);
    }
  };
  
} } }

#endif
