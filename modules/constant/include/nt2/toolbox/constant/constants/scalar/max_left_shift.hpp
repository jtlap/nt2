/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_MAXLEFTSHIFT_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_MAXLEFTSHIFT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating signmask constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::max_left_shift_, tag::cpu_,(A0)
                            , (target_< scalar_< arithmetic_<A0> > >)
                            )
  {
    typedef typename
            as_integer<typename strip<A0>::type::type,signed>::type  result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typedef typename meta::scalar_of<result_type>::type base_t;
      BOOST_STATIC_CONSTANT(std::size_t, value = sizeof(base_t)*CHAR_BIT-1 );
      return splat<result_type>(value);
    }
  };
} }

#endif
