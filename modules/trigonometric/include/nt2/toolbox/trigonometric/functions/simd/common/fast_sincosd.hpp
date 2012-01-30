//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_FAST_SINCOSD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_FAST_SINCOSD_HPP_INCLUDED
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/toolbox/trigonometric/functions/simd/common/impl/trigo.hpp>

/////////////////////////////////////////////////////////////////////////////
// reference based Implementation
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_IF(nt2::tag::fast_sincosd_, boost::simd::tag::simd_,(A0)(A1)(X),
                             (boost::mpl::equal_to<nt2::meta::cardinal_of<A0>, 
                                                     nt2::meta::cardinal_of<A1> >), 
                             ((simd_ < arithmetic_<A0>,X > ))
                             ((simd_ < floating_<A1>,X > ))
                             ((simd_ < floating_<A1>,X > ))
                             )
  {
    typedef int result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1,A1 & a2) const
    {
      a1 = impl::trig_base <A1,degree_tag,
                       tag::not_simd_type>::sincosa(tofloat(a0),a2); 
      return 0;
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION_IF(nt2::tag::fast_sincosd_, boost::simd::tag::simd_,(A0)(A1)(X),
                                (boost::mpl::equal_to<nt2::meta::cardinal_of<A0>, 
                                                 nt2::meta::cardinal_of<A1>
                                        >
                                ),
                                ((simd_ < arithmetic_<A0>,X > ))
                                ((simd_ < floating_<A1>,X > ))
                             )
  {
    typedef A1 result_type;    
    inline result_type operator()(A0 const& a0,A1 & a2) const
    {
      return impl::trig_base <A1,degree_tag,fast_tag,
                       tag::simd_type>::sincosa(tofloat(a0),a2); 
    }
  };
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::fast_sincosd_, boost::simd::tag::simd_,
                               (A0)(X),
                               ((simd_<arithmetic_<A0>,X>))
                              )
  {
      typedef typename meta::as_floating<A0>::type  rtype;
      typedef boost::fusion::tuple<rtype, rtype> result_type;
    
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      result_type res;
      typedef typename  boost::fusion::result_of::value_at_c<result_type,0>::type type;
      boost::fusion::at_c<0>(res) = impl::trig_base < type,degree_tag
        ,  tag::simd_type, clipped_pio4
        >::sincosa( tofloat(a0)
                    , boost::fusion::at_c<1>(res)
                    );
      return res;
    }
  };
} }
#endif
