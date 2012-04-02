//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_BAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_BAND_HPP_INCLUDED

#include <nt2/core/functions/band.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/ge.hpp>
#include <nt2/include/functions/le.hpp>
#include <nt2/include/functions/eq.hpp>
#include <nt2/include/functions/logical_and.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::band_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename meta::strip<Data>::type::type                    result_type;
    typedef typename meta::as_integer<result_type>::type              i_t;
    typedef typename meta::call<nt2::tag::ind2sub_(_2D,State)>::type  sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      sub_t const pos = ind2sub(_2D(a0.extent()),p);

      // Return the upper triangular section with 1 on the diagonal
      return nt2::if_else ( nt2::eq ( nt2::enumerate<i_t>( pos[0] )
                                    , nt2::splat<i_t>( pos[1] )
                                    )
                          , nt2::run(boost::proto::child_c<0>(a0),p,t)
                          , Zero<result_type>()
                          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::offset_band1_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename meta::strip<Data>::type::type                    result_type;
    typedef typename meta::as_integer<result_type>::type              i_t;
    typedef typename meta::call<nt2::tag::ind2sub_(_2D,State)>::type  sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      std::ptrdiff_t offset = boost::proto::value(boost::proto::child_c<1>(a0));
      sub_t const pos = ind2sub(_2D(a0.extent()),p);
      i_t const   is  = nt2::enumerate<i_t>( pos[0] );
      i_t const   ju  = nt2::splat<i_t>( pos[1] + offset );
      i_t const   jd  = nt2::splat<i_t>( pos[1] - offset );

      // Return the band between +/-offset around the main diagonal
      return nt2::if_else ( nt2::logical_and( nt2::le(is,ju)
                                            , nt2::ge(is,jd)
                                            )
                          , nt2::run(boost::proto::child_c<0>(a0),p,t)
                          , Zero<result_type>()
                          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::offset_band2_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename meta::strip<Data>::type::type                    result_type;
    typedef typename meta::as_integer<result_type>::type              i_t;
    typedef typename meta::call<nt2::tag::ind2sub_(_2D,State)>::type  sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      sub_t const pos = ind2sub(_2D(a0.extent()),p);
      i_t const   is  = nt2::enumerate<i_t>( pos[0] );
      i_t const   ju  = nt2::splat<i_t>
                            ( pos[1]
                            + boost::proto::value(boost::proto::child_c<2>(a0))
                            );
      i_t const   jd  = nt2::splat<i_t>
                            ( pos[1]
                            - boost::proto::value(boost::proto::child_c<1>(a0))
                            );

      // Return the band between +/-offset around the main diagonal
      return nt2::if_else ( nt2::logical_and( nt2::le(is,ju)
                                            , nt2::ge(is,jd)
                                            )
                          , nt2::run(boost::proto::child_c<0>(a0),p,t)
                          , Zero<result_type>()
                          );
    }
  };
} }

#endif
