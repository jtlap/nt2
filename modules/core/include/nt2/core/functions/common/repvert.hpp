//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_REPVERT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_REPVERT_HPP_INCLUDED

#include <nt2/core/functions/repvert.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/rem.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::repvert_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::dispatch::meta::
            call<nt2::tag::run_ ( typename  boost::proto::result_of::
                                            child_c<A0&, 0>::type
                                , State&, Data&
                                )
                >::type                                        base_type;

    typedef typename meta::strip<base_type>::type                       result_type;
    typedef typename meta::as_integer<result_type>::type                        i_t;
    typedef typename meta::call<nt2::tag::ind2sub_(of_size_max,State)>::type  sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Get the subscript
      of_size_max ex0 = boost::proto::child_c<0>(a0).extent();
      sub_t pos0 = ind2sub(a0.extent(),p);

      // replicate by modulo on the leading dimension
      pos0[0] = (pos0[0]-1)%ex0[0]+1;

      // We need a gather there cause we may wrap up before cardinal
      i_t p0 = nt2::enumerate<i_t>(pos0[0]);

      // This shifts us along other dimensions
      i_t shift = nt2::splat<i_t> ( boost::proto::child_c<0>(a0).leading_size()
                                  * (pos0[1]-1) // FIXME for size>2D
                                  );

      // We compute a SIMD index by wrapping around and moving aside
      i_t h0 = nt2::splat<i_t>(ex0[0]);
      i_t p1 = nt2::rem(minusone(p0), h0) + shift;

      // Evaluates
      return nt2::run(boost::proto::child_c<0>(a0),p1,t);
    }
  };
} }

#endif
