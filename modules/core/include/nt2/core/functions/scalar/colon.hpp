//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_COLON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_COLON_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/colon.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/splat.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/fuzzy_equal.hpp>
#include <nt2/include/functions/tolerant_floor.hpp>
#include <nt2/include/constants/threeeps.hpp>
#include <nt2/core/utility/generative/generative.hpp>

//==============================================================================
// colon actual functor forward declaration
//==============================================================================
namespace nt2 { namespace details
{
  template<class T> struct colon;
  template<class T> struct unity_colon;
} }

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates colon from a pair of [low,up]
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef nt2::details::
            generative< nt2::tag::table_
                      , nt2::details::unity_colon<A0>
                      , A0
                      , settings(_2D)
                      > base;


    typedef typename  boost::proto::
                      result_of::as_expr< base
                                        , container::domain
                                        >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A0 const& u) const
    {
      std::size_t n = (u>=l) ? std::size_t(u-l+1) : 0;
      nt2::details::unity_colon<A0> callee(l);
      base that(of_size(1,n),callee);
      return boost::proto::as_expr<container::domain>(that);
    }
  };

  //============================================================================
  // Generates colon from a pair of [low,up] and a step
  // Easy case : everything is signed integral
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)
                            , (scalar_< int_<A0> >)
                              (scalar_< int_<A0> >)
                              (scalar_< int_<A0> >)
                            )
  {
    typedef nt2::details::
            generative< nt2::tag::table_
                      , nt2::details::colon<A0>
                      , A0
                      , settings(_2D)
                      > base;


    typedef typename  boost::proto::
                      result_of::as_expr< base
                                        , container::domain
                                        >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A0 const& s, A0 const& u) const
    {
      std::size_t n = (s) ?(((u>l)==(s>0))? ((u-l+s)/s) : 0) : u;
      nt2::details::colon<A0> callee(l,s);
      base that(of_size(1,n),callee);
      return boost::proto::as_expr<container::domain>(that);
    }
  };

  //============================================================================
  // Generates colon from a pair of [low,up] and a step
  // Easy case : everything is unsigned integral
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)
                            , (scalar_< uint_<A0> >)
                              (scalar_< uint_<A0> >)
                              (scalar_< uint_<A0> >)
                            )
  {
    typedef nt2::details::
            generative< nt2::tag::table_
                      , nt2::details::colon<A0>
                      , A0
                      , settings(_2D)
                      > base;

    typedef typename  boost::proto::
                      result_of::as_expr< base
                                        , container::domain
                                        >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A0 const& s, A0 const& u) const
    {
      std::size_t n = (s) ?((u>l)? ((u-l+s)/s) : 0) : u;
      nt2::details::colon<A0> callee(l,s);
      base that(of_size(1,n),callee);
      return boost::proto::as_expr<container::domain>(that);
    }
  };

  //============================================================================
  // Generates colon from a pair of [low,up] and a number of elements
  // Not easy case : floating points :s
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A1> >)
                              (scalar_< arithmetic_<A2> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0,A1,A2>::type base_t;

    typedef nt2::details::
            generative< nt2::tag::table_
                      , nt2::details::colon<base_t>
                      , base_t
                      , settings(_2D)
                      > base;

    typedef typename  boost::proto::
                      result_of::as_expr< base
                                        , container::domain
                                        >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A1 const& s, A2 const& u) const
    {
      std::size_t n = (s) ? (((u-l)*s >= 0) ? colon_size(l,s,u) : 0)
                          : std::size_t(u);

      nt2::details::colon<A0> callee(l,s);
      base that(of_size(1,n),callee);
      return boost::proto::as_expr<container::domain>(that);
    }

    BOOST_FORCEINLINE std::size_t
    colon_size(A0 const& l, A1 const& s, A2 const& u) const
    {
      const std::size_t nelt  = std::size_t(tolerant_floor(base_t(u-l+s)/base_t(s)));
      const base_t      eps3  = Threeeps<base_t>();

      if(!fuzzy_equal(l+(nelt-1)*s, u, eps3))
      {
              if(fuzzy_equal(l+(nelt-2)*s, u, eps3))  return nelt-1;
        else  if(fuzzy_equal(l+nelt*s    , u, eps3))  return nelt+1;
      }
      return nelt;
    }
  };
} }

namespace nt2 { namespace details
{
  //============================================================================
  // colon actual functor : precompute step and just iterate over
  //============================================================================
  template<class T> struct colon
  {
    colon( T const& l, T const& s) : lower_(l), step_(s) {}

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

  template<class T> struct unity_colon
  {
    unity_colon( T const& l ) : lower_(l) {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;

      return  nt2::enumerate<type>(boost::fusion::at_c<1>(p)-1)
            + nt2::splat<type>(lower_);
    }

    T lower_;
  };
} }

#endif
