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

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::from_diag_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::dispatch::meta::
            call<nt2::tag::run_ ( typename  boost::proto::result_of::
                                            child_c<A0&, 0>::type
                                , State&, Data&
                                )
                >::type                                               base_type;

    typedef typename meta::strip<base_type>::type                     result_type;
    typedef typename meta::as_integer<result_type,unsigned>::type     id_t;
    typedef typename meta::call<nt2::tag::ind2sub_(_2D,State)>::type  sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      sub_t const pos = ind2sub(boost::proto::child_c<1>(a0).value(),p);

      // Compute which part of the input table to load for selection
      std::size_t k = ((pos[1]-1)
                    & ~(boost::simd::meta::cardinal_of<result_type>::value-1));

      // Return a diagonal built from boost::proto::child_c<0>(a0)
      return nt2::if_else ( nt2::eq ( nt2::enumerate<id_t>( pos[0] )
                                    , nt2::splat<id_t>( pos[1] )
                                    )
                          , nt2::run(boost::proto::child_c<0>(a0), k, t)
                          , Zero<result_type>()
                          );
    }
  };
} }

#endif
