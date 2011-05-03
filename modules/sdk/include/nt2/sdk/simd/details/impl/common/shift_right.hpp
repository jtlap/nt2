/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_SHIFT_RIGHT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_SHIFT_RIGHT_HPP_INCLUDED

#include <nt2/sdk/simd/native_cast.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/type_traits/is_same.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_IF(tag::shift_right_, tag::cpu_,
    (A0)(A1)(X),
    (boost::mpl::and_<
      boost::mpl::not_< boost::is_same<A0, A1> >,
      boost::mpl::equal_to< boost::mpl::sizeof_<A0>, boost::mpl::sizeof_<A1> >
    >),
    (tag::shift_right_(tag::simd_<tag::arithmetic_,X>
                      ,tag::simd_<tag::integer_,X>
                      )
    ), 
    ((simd_<arithmetic_<A0>,X>))((simd_<integer_<A1>,X>))
); 

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy,class X>
  struct  call< tag::shift_right_ ( tag::simd_<tag::arithmetic_,X> 
                                  , tag::simd_<tag::integer_,X> 
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
      typedef typename meta::as_integer<A0>::type int_type;
      return simd::native_cast<A0>(shift_right(simd::native_cast<int_type>(a0), a1));
    }
  };
} }

#endif
