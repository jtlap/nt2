/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED

#include <boost/tr1/functional.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/simd/details/impl/splat.hpp>
#include <nt2/sdk/simd/details/impl/constants.hpp>

////////////////////////////////////////////////////////////////////////////////
// Forward all constant call to the simd version of themselves that splat
// the appropriate scalar constants into a proper SIMD vector.
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( Tag, tag::cpu_
                      , (Tag)(A0)(X)
                      , ((target_< simd_< arithmetic_<A0>,X> >))
                      )

namespace nt2 { namespace ext
{
  template<class Tag, class X, class Dummy>
  struct  call< Tag(tag::target_< tag::simd_<tag::arithmetic_,X> >)
              , tag::cpu_, Dummy
              >
          : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)>
    {
      typedef typename meta::strip<Target>::type::type          target;
      typedef typename meta::scalar_of<target>::type            base;
      typedef typename
      std::tr1::result_of<functor<Tag>(nt2::meta::as_<base>)>::type  results;
      typedef typename target::template cast<results>::type      type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::strip<A0>::type::type        target;
      typedef typename meta::scalar_of<target>::type      type;
      typedef typename NT2_RETURN_TYPE(1)::type           result_type;
      functor<Tag> callee;
      return splat<result_type>(callee( nt2::meta::as_<type>()));
    }
  };
} }

#endif
