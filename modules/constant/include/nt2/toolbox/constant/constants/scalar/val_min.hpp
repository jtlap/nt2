/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_VALMIN_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_VALMIN_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating valmin constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::val_min_,tag::cpu_
                            , (A0), (target_< scalar_< double_<A0> > > )
                            )
  {
    typedef typename meta::strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const
      that = {0xffefffffffffffffLL};
      return splat<result_type>(that.value);
    }
  };
} }

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::val_min_,tag::cpu_
                            , (A0), (target_< scalar_< float_<A0> > > )
                            )
  {
    typedef typename meta::strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const
      that = {0xff7fffff};
      return splat<result_type>(that.value);
    }
  };
} }

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::val_min_,tag::cpu_,(A0)
                            , (target_< scalar_< unsigned_<A0> > > )
                            )
  {
    typedef typename meta::strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return splat<result_type>(0);
    }
  };
} }

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::val_min_,tag::cpu_
                            , (A0), (target_< scalar_< signed_<A0> > > )
                            )
  {
    typedef typename meta::strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typedef typename meta::as_unsigned<result_type>::type base;
      BOOST_STATIC_CONSTANT(base, value = base(1) << (sizeof(base)*CHAR_BIT-1) );
      return splat<result_type>(base(value));
    }
  };
} }

#endif
