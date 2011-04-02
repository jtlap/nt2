/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_MAXLEFTSHIFT_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_MAXLEFTSHIFT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating signmask constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

NT2_REGISTER_DISPATCH ( tag::max_left_shift_
                      , tag::cpu_,(A0)
                      , (target_< arithmetic_<A0> > )
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::max_left_shift_(tag::target_<tag::arithmetic_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)>
        : meta::as_integer<typename meta::strip<Target>::type::type,signed> {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename  NT2_RETURN_TYPE(1)::type  type;
      typedef typename meta::scalar_of<type>::type base_t;
      BOOST_STATIC_CONSTANT(std::size_t, value = sizeof(base_t)*CHAR_BIT-1 );
      return splat<type>(value);
    }
  };
} }

#endif
