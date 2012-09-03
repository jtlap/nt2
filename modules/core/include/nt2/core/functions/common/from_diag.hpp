//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_FROM_DIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_FROM_DIAG_HPP_INCLUDED

#include <nt2/core/functions/from_diag.hpp>
#include <nt2/include/functions/arith.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/first.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::from_diag_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                                       result_type;
    typedef typename meta::as_index<result_type>::type     i_t;
    typedef typename meta::
                     call<nt2::tag::enumerate_(State,meta::as_<i_t>)>::type p_t;
    typedef typename meta::call<nt2::tag::ind2sub_(_2D,p_t)>::type          s_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      s_t const pos = ind2sub ( boost::proto::child_c<1>(a0).value()
                              , enumerate<i_t>(p)
                              );

      // Return a diagonal built from boost::proto::child_c<0>(a0)
      return nt2::if_else ( nt2::eq( pos[0], pos[1] )
                          , nt2::run(boost::proto::child_c<0>(a0), pos[1]-1, t)
                          , Zero<result_type>()
                          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::offset_from_diag_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                                       result_type;
    typedef typename meta::as_integer<result_type,signed>::type       i_t;
    typedef typename meta::
                     call<nt2::tag::enumerate_(State,meta::as_<i_t>)>::type p_t;
    typedef typename meta::call<nt2::tag::ind2sub_(_2D,p_t)>::type          s_t;
    typedef typename s_t::value_type          sp_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      s_t const pos = ind2sub ( boost::proto::child_c<2>(a0).value()
                              , enumerate<i_t>(p)
                              );

      // Compute the offset and new position
      std::ptrdiff_t o = boost::proto::value(boost::proto::child_c<1>(a0));
      sp_t op = pos[0]+o;
      sp_t pp = pos[1]-(1+o) + (o < 0 ? o : 0) ;

      // Return a diagonal built from boost::proto::child_c<0>(a0)
      return nt2::if_else ( nt2::eq( op, pos[1] )
                          , nt2::run(boost::proto::child_c<0>(a0), pp, t)
                          , Zero<result_type>()
                          );
    }
  };
} }

#endif
