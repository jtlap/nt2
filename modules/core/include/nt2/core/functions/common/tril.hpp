//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TRIL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TRIL_HPP_INCLUDED

#include <nt2/core/functions/tril.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::tril_, N>))
                              (fusion_sequence_<State>)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename meta::strip<Data>::type::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      return nt2::if_else
            ( nt2::ge ( nt2::enumerate<result_type>( boost::fusion::at_c<0>(p) )
                      , nt2::splat<result_type>    ( boost::fusion::at_c<1>(p) )
                      )
            , nt2::run(boost::proto::child_c<0>(a0),p,t)
            , Zero<result_type>()
            );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::offset_tril_, N>))
                              (fusion_sequence_<State>)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename meta::strip<Data>::type::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      return nt2::if_else
            ( nt2::ge ( nt2::enumerate<result_type>( boost::fusion::at_c<0>(p) )
                      , nt2::splat<result_type>
                        ( boost::fusion::at_c<1>(p)
                        + boost::proto::value(boost::proto::child_c<1>(a0))
                        )
                      )
            , nt2::run(boost::proto::child_c<0>(a0),p,t)
            , Zero<result_type>()
            );
    }
  };
} }

#endif
