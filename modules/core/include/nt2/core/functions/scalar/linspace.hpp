//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_LINSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_LINSPACE_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/functions/linspace.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>

//==============================================================================
// linspace actual functor forward declaration
//==============================================================================
namespace nt2 { namespace details { template<class T> struct linspace; } }

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates linspace from a pair of [low,up]
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linspace_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::linspace_
                                          , container::domain
                                          , box< of_size_<1,100> >
                                          , box< nt2::details::linspace<A0> >
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A0 const& u) const
    {
      return  boost::proto::
              make_expr < nt2::tag::linspace_
                        , container::domain
                        > ( boxify(of_size_<1,100>())
                          , boxify(nt2::details::linspace<A0>(l,u,100))
                          , meta::as_<A0>()
                          );
    }
  };

  //============================================================================
  // Generates linspace from a pair of [low,up] and a number of elements
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linspace_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::linspace_
                                          , container::domain
                                          , box< _2D >
                                          , box< nt2::details::linspace<A0> >
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A0 const& u, A1 const& n) const
    {
      return  boost::proto::
              make_expr < nt2::tag::linspace_
                        , container::domain
                        > ( boxify(of_size(1,n))
                          , boxify(nt2::details::linspace<A0> ( (n<2 ? u : l)
                                                              , u
                                                              , (n<2 ? 2 : n)
                                                              )
                                  )
                          , meta::as_<A0>()
                          );
    }
  };
} }

namespace nt2 { namespace details
{
  //============================================================================
  // linspace actual functor : precompute step and just iterate over
  //============================================================================
  template<class T> struct linspace
  {
    linspace() {}
    linspace( T const& l, T const& u, std::size_t n )
            : lower_(l), step_((u-l)/(n-1)) {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;

      return nt2::fma ( nt2::enumerate<type>(boost::fusion::at_c<1>(p)-1)
                      , nt2::splat<type>(step_)
                      , nt2::splat<type>(lower_)
                      );
    }

    T lower_, step_;
  };
} }

#endif
