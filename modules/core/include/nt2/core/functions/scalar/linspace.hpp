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
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/functions/linspace.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/core/utility/generator/generator.hpp>

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
    typedef nt2::details::
            generator < nt2::tag::table_
                      , nt2::details::linspace<A0>
                      , A0
                      , settings(of_size_<1,100>)
                      > base;

    typedef typename boost::proto::terminal<base>::type  expr_type;
    typedef typename boost::
            result_of<container::domain(expr_type)>::type const result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A0 const& u) const
    {
      container::domain domain_;
      nt2::details::linspace<A0> callee(l,u,100);

      return domain_( expr_type::make( base(of_size_<1,100>(),callee) ) );
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
    typedef nt2::details::
            generator < nt2::tag::table_
                      , nt2::details::linspace<A0>
                      , A0
                      , settings(_2D)
                      > base;

    typedef typename boost::proto::terminal<base>::type  expr_type;
    typedef typename boost::
            result_of<container::domain(expr_type)>::type const result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A0 const& u, A1 const& n) const
    {
      container::domain domain_;
      nt2::details::linspace<A0> callee((n<2 ? u : l),u,(n<2 ? 2 : n));

      return domain_( expr_type::make( base(of_size(1,n),callee) ) );
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
