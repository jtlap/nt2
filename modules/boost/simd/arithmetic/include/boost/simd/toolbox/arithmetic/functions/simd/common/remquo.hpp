//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_REMQUO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_REMQUO_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/round2even.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/toint.hpp>
#include <boost/simd/include/functions/is_gtz.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/if_nan_else.hpp>
#include <boost/mpl/logical.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::remquo_, tag::cpu_,
                             (A0)(X),
                             ((simd_<arithmetic_<A0>,X>))
                             ((simd_<arithmetic_<A0>,X>))
                             )
  {
    typedef typename dispatch::meta::as_floating<A0>::type               stA0;
    typedef typename dispatch::meta::as_integer<A0, signed>::type     iA0;             
    typedef boost::fusion::tuple<stA0,iA0>          result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
      {
        result_type res;
        boost::simd::remquo( tofloat(a0), tofloat(a1)
              , boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res)
              );
        return res;
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // reference based Implementation
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF(  boost::simd::tag::remquo_, tag::cpu_,(A0)(A1)(A2)(A3)(X)
                                  ,( boost::mpl::and_ <
                                     boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                          , boost::simd::meta::cardinal_of<A1> >, 
                                     boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                          , boost::simd::meta::cardinal_of<A2> >,
                                     boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                          , boost::simd::meta::cardinal_of<A3> >
                                     >
                                  )
                               , ((simd_<arithmetic_<A0>,X>))
                                 ((simd_<arithmetic_<A1>,X>))
                                 ((simd_<floating_<A2>,X>))
                                 ((simd_<integer_<A3>,X>))
                             )
  {
    typedef void result_type;    
    inline result_type operator()(A0 const& a0, A1 const& a1,
                                  A2 & a2, A3 & a3) const
    {
      boost::simd::remquo(tofloat(a0), tofloat(a1), a2, a3); 
    }
  };

/////////////////////////////////////////////////////////////////////////////
  // reference based Implementation
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF(  boost::simd::tag::remquo_, tag::cpu_,(A0)(A1)(X)
                                  ,( boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                          , boost::simd::meta::cardinal_of<A1> >)
                                  , ((simd_<floating_<A0>,X>))
                                  ((simd_<floating_<A0>,X>))
                                  ((simd_<floating_<A0>,X>))
                                  ((simd_<integer_<A1>,X>))
                             )
  {
    typedef void result_type;    
    inline result_type operator()(A0 const& a0, A0 const& a1,
                                  A0 & a2, A1 & a3) const
    {
      a2 = round2even(a0/a1); 
      a3 = toint(a2);
      a2 =  if_nan_else(b_or(is_invalid(a0), is_eqz(a1)), a0-a2*a1);
//a2 = b_or(is_invalid(a0), b_or(is_eqz(a1), a0-a2*a1)); 
 
    }
  };
 
} } }
#endif
