//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOG2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOG2_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/log2.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/toolbox/exponential/functions/simd/common/impl/logs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{


//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
//                               , (A0)(X)
//                               ,  ((simd_< arithmetic_<A0>, X>))
//                             )
//   {
//     typedef typename  boost::proto::
//                       result_of::make_expr< nt2::tag::log2_
//                                           , container::domain
//                                           , A0 const&
//                                           >::type             result_type;

//     BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
//     {
//       return boost::proto::make_expr< nt2::tag::log2_
//                                     , container::domain
//                                     > ( boost::cref(a0));
//     }
//   };

  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return impl::logarithm<result_type, tag::simd_type>::log2(tofloat(a0));
    }
  };
} }


#endif
