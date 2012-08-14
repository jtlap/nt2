//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_REPHORZ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_REPHORZ_HPP_INCLUDED

#include <nt2/core/functions/rephorz.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::rephorz_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                                     result_type;
    typedef typename meta::as_integer<result_type>::type            i_t;
    typedef typename  boost::proto::result_of::child_c<A0&,0>::type p_t;
    typedef typename meta::call<tag::ind2sub_(_2D, i_t)>::type      sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      p_t   pattern = boost::proto::child_c<0>(a0);
      _2D   ex      = pattern.extent();
      _2D   in      = a0.extent();

      sub_t pos = ind2sub( in, nt2::enumerate<i_t>(p));
      pos[1] = (pos[1]-1)%ex[1]+1;

      return nt2::run( pattern, sub2ind(ex, pos), t );
    }
  };
} }

#endif
