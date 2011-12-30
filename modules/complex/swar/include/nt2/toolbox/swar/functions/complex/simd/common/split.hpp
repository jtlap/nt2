//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED
#include <nt2/toolbox/swar/functions/group.hpp>
#include <nt2/include/functions/load.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/tuple.hpp>

namespace nt2 { namespace ext
{
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is upgradeable
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::split_, tag::cpu_,
                              (A0)(A1)(X),
                              (boost::mpl::and_ <
                                boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::upgrade<A0>::type> >,
                                boost::is_same<A1, typename dispatch::meta::upgrade<A0>::type>
                              >),
                              ((simd_<complex_<arithmetic_<A0> >,X>))
                              ((simd_<complex_<arithmetic_<A1> >,X>))
                              ((simd_<complex_<arithmetic_<A1> >,X>))
                            )
  {
    typedef int result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1, A1 & a2) const
    {
      split(real(a0), ar0, ar1); 
      split(imag(a0), ai0, ai1);
      a1 = A1(ar0, ai0);
      a2 = A1(ar1, ai1);
      return 0; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::split_, tag::cpu_,
                              (A0)(X),
                              (boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::upgrade<A0>::type> >),
                              ((simd_<complex_<arithmetic_<A0> >,X>))
                            )
  {
    typedef typename dispatch::meta::upgrade<A0>::type rtype;
    typedef boost::fusion::tuple<rtype, rtype> result_type;
    
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      result_type res;
      nt2::split(a0,  boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res));
      return res; 
    }
  };
} }

#endif
