//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_REAL_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_REAL_HPP_INCLUDED

//==============================================================================
// Custom local real functor
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_TPL( (tag::pattern<D,F>) , tag::cpu_
                                , (nt2::uint64_t D)(nt2::uint32_t F)(class A0)
                                , (target_< scalar_<double_<A0> > >)
                                )
  {
    typedef typename strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const that = {D};
      return splat<result_type>(that.value);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_TPL( (tag::pattern<D,F>) , tag::cpu_
                                , (nt2::uint64_t D)(nt2::uint32_t F)(class A0)
                                , (target_< scalar_<float_<A0> > >)
                                )
  {
    typedef typename strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const that = {F};
      return splat<result_type>(that.value);
    }
  };
} }
  
#endif
