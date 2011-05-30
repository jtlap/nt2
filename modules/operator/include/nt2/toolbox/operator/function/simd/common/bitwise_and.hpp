/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_BITWISE_AND_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_BITWISE_AND_HPP_INCLUDED

#include <nt2/sdk/simd/native_cast.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_same.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////

NT2_REGISTER_DISPATCH_IF(tag::bitwise_and_, tag::cpu_,
    (A0)(A1)(X),
    (boost::mpl::not_< boost::is_same<A0, A1> >),
    (tag::bitwise_and_(tag::simd_<tag::arithmetic_,X>
                      ,tag::simd_<tag::arithmetic_,X>
                      )
    ), 
    ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A1>,X>))
); 

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy,class X>
  struct  call< tag::bitwise_and_ ( tag::simd_<tag::arithmetic_,X> 
                                  , tag::simd_<tag::arithmetic_,X> 
                                  )
              , tag::cpu_, Dummy
              > : callable
  {
    template<class Sig>
    struct result;
    
    template<class This, class A0, class A1>
    struct result<This(A0, A1)> : meta::strip<A0>
    {
    };
    
    NT2_FUNCTOR_CALL(2)
    {
      return bitwise_and(a0, simd::native_cast<A0>(a1));
    }
  };
} }

#endif
