//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED

#include <boost/simd/toolbox/swar/functions/split.hpp>
#include <boost/simd/toolbox/swar/functions/group.hpp>
#include <boost/simd/include/functions/simd/load.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/tuple.hpp>

namespace boost { namespace simd { namespace ext
{
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is upgradeable
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_
                                      , tag::cpu_
                                      , (A0)(A1)(X)(Y)
                                      , ( boost::is_same< A1
                                                        , typename dispatch::meta::upgrade<A0>::type
                                                        >
                                        )
                                      , ((simd_<arithmetic_<A0>,X>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                        ((simd_<arithmetic_<A1>,Y>))
                            )
  {
    typedef int result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1, A1 & a2) const
    {
      static const size_t size_2 = meta::cardinal_of<A0>::value/2;
      typedef typename meta::scalar_of<A1>::type sA1; 
      BOOST_SIMD_ALIGNED_TYPE(sA1) tmp1[size_2];
      BOOST_SIMD_ALIGNED_TYPE(sA1) tmp2[size_2];
      for(size_t i = 0; i != size_2; ++i)
      {
        tmp1[i] = a0[i];
        tmp2[i] = a0[i+size_2];
      }
      a1 = load<A1>(&tmp1[0], 0); 
      a2 = load<A1>(&tmp2[0], 0); 
      return 0; 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_, tag::cpu_,
                              (A0)(X),
                              (boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::upgrade<A0>::type> >),
                              ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::upgrade<A0>::type rtype;
    typedef boost::fusion::tuple<rtype, rtype> result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      result_type res;
      boost::simd::split(a0,  boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res));
      return res; 
    }
  };
} } }

#endif
