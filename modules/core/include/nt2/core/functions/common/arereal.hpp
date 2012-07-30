//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_AREREAL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_AREREAL_HPP_INCLUDED

#include <nt2/core/functions/arereal.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arereal_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      typedef typename nt2::meta::scalar_of<A0>::type sA0; 
      //      if(is_real<sA0>::type::value)  return true;  //TODO meta function saying if a type is real
      if(nt2::all(is_real(a0)))      return true;
      return false; 

    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arereal_, tag::cpu_
                            , (A0)
                            , (scalar_<fundamental_<A0> >)
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      return nt2::is_real(a0);
    }
  };
} }

#endif
