//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_BLKDIAG_HPP_INCLUDED

#include <nt2/core/functions/blkdiag.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::blkdiag_, N>))
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

    typedef typename meta::strip<base_type>::type               result_type;
    typedef typename meta::as_integer<result_type>::type                i_t;
    typedef typename meta::call<nt2::tag::ind2sub_(_2D,i_t)>::type  sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Get size of each children
      _2D ex0 = boost::proto::child_c<0>(a0).extent();
      _2D ex1 = boost::proto::child_c<1>(a0).extent();

      // Get the current index vector
      sub_t pos = ind2sub(a0.extent(),nt2::enumerate<i_t>(p));

      // Find the proper quadrant for each position
      typedef typename meta::as_logical<i_t>::type mask_t;
      mask_t is_stack0 = nt2::le(pos[1],splat<i_t>(ex0[1]));
      mask_t is_row0   = nt2::le(pos[0],splat<i_t>(ex0[0]));

      // Result is out of the diagonal
      result_type z   = Zero<result_type>();

      // Result is in a0
      result_type s0  = nt2::run( boost::proto::child_c<0>(a0)
                                , sub2ind(ex0, pos)
                                , t
                                );

      // Result is in a1
      pos[0] -= splat<i_t>(ex0[0]);
      pos[1] -= splat<i_t>(ex0[1]);
      result_type s1 = nt2::run ( boost::proto::child_c<1>(a0)
                                , sub2ind(ex1, pos)
                                , t
                                );

      // Select proper values depending on quadrant informations
      return nt2::if_else ( is_stack0
                          , nt2::if_else(is_row0, s0, z)
                          , nt2::if_else(!is_row0, s1, z)
                          );
    }
  };
} }

#endif
