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
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <boost/fusion/include/pop_front.hpp>

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
      typedef typename  boost::proto::result_of
                      ::child_c<A0&,0>::value_type::extent_type       ex_t;

      // Retrieve pattern and its extent
      p_t   pattern = boost::proto::child_c<0>(a0);
      ex_t  ex      = pattern.extent();

      // How many vectorizable slices to process
      std::size_t s0  = nt2::numel(boost::fusion::pop_front(ex));

      // Enumeration along vectorizabel dimension
      i_t vp  = nt2::enumerate<i_t>(p) % splat<i_t>(ex[0]);

      // Offset over the slices
      i_t vo  = splat<i_t>( ((p / a0.extent()[0]) % s0)*ex[1]);

      // Load data from there
      return nt2::run( pattern, vo+vp, t );
    }
  };
} }

#endif
