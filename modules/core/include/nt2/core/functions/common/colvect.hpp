//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_COLVECT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_COLVECT_HPP_INCLUDED

#include <nt2/core/functions/colvect.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::colvect_, N>))
                              (fusion_sequence_<State>)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename meta::strip<Data>::type::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      ptriff_t i = nt2::sub2ind(p); 
      return a0(nt2::sub2ind(p)); 
    }
  };

} }

#endif
