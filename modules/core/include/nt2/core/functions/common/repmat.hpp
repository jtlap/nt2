//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_REPMAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_REPMAT_HPP_INCLUDED

#include <nt2/core/functions/repmat.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/modulo.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/minus.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::repmat_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::dispatch::meta::
            call<nt2::tag::run_ ( typename  boost::proto::result_of::
                                            child_c<A0&, 0>::type
                                , State&, Data&
                                )
                >::type                                      base_t;

    typedef typename meta::strip<base_t>::type               result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_integer<result_type>::type            i_t;
      typedef typename  boost::proto::result_of::child_c<A0&,0>::type p_t;
      typedef typename meta::call<tag::ind2sub_(_2D, i_t)>::type    sub_t;

      // Retrieve pattern and its extent
      p_t   pattern = boost::proto::child_c<0>(a0);
      _2D   in_sz   = pattern.extent();
      _2D   out_sz  = a0.extent();

      sub_t pos = ind2sub(out_sz, nt2::enumerate<i_t>(p));
      pos[0] = (pos[0]-1) % in_sz[0] + 1;
      pos[1] = (pos[1]-1) % in_sz[1] + 1;

      return nt2::run( pattern, sub2ind(in_sz, pos), t );
    }
  };
} }

#endif
