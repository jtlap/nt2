//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_EXPAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_EXPAND_HPP_INCLUDED

#include <nt2/core/functions/expand.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/ind2ind.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/isinside.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::expand_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                          result_type;
    typedef typename meta::as_index<result_type>::type i_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // We compute the new position and clamp it to rpevent segfault
      i_t maxpos = splat<i_t>(numel(boost::proto::child_c<0>(a0))-1);
      i_t pos = ind2ind ( boost::proto::value(boost::proto::child_c<1>(a0))
                        , enumerate<i_t>(p)
                        , boost::proto::child_c<0>(a0).extent()
                        );
      pos = if_else( ge(pos,maxpos), maxpos, pos);

      // This code select between the actual values and 0 depending on the
      // fact that the current linear index, once turned into a subscript of
      // the destination matrix, is inside the old one.
      return  nt2::if_else
              ( isinside
                ( ind2sub ( boost::proto::value(boost::proto::child_c<1>(a0))
                          , enumerate<i_t>(p)
                          , boost::proto::child_c<0>(a0).indexes()
                          )
                , boost::proto::child_c<0>(a0)
                )
              , nt2::run( boost::proto::child_c<0>(a0)
                        , pos
                        , t
                        )
              , Zero<result_type>()
              );
    }
  };
} }

#endif
