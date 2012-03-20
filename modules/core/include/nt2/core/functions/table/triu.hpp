//===========================//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_TRIU_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_TRIU_HPP_INCLUDED

#include <nt2/core/functions/triu.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/include/functions/extent.hpp>

//==============================================================================
// triu actual functor forward declaration
//==============================================================================
namespace nt2 { namespace details
{
  template<class T, class S> struct triu;
  template<class T> struct triu0;
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::triu_, tag::cpu_, 
                              (A0)(A1)(S0),
                              ((table_< unspecified_<A0>, S0>))
                              (scalar_<integer_<A1> >) 
                              )
  {
    typedef nt2::details::
      generative< nt2::tag::table_
      , nt2::details::triu<A0, A1>
      , A0
      , settings(_2D)
      > base;
    
    typedef typename  boost::proto::
      result_of::as_expr< base
      , container::domain
      >::type             result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a, const A1& k) const
    {
      nt2::details::triu<A0, A1> callee(a, k);
      base that(size(a),callee);
      return boost::proto::as_expr<container::domain>(that);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::triu_, tag::cpu_, 
                              (A0)(S0),
                              ((table_< unspecified_<A0>, S0>))
                              )
  {
    typedef nt2::details::
      generative< nt2::tag::table_
      , nt2::details::triu0<A0>
      , A0
      , settings(_2D)
      > base;
    
    typedef typename  boost::proto::
      result_of::as_expr< base
      , container::domain
      >::type             result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a) const
    {
      nt2::details::triu0<A0> callee(a);
      base that(size(a),callee);
      return boost::proto::as_expr<container::domain>(that);
    }
  };    
} }

namespace nt2 { namespace details
{
  //============================================================================
  // triu actual functor : precompute splatted k and just select
  //============================================================================
  template<class A, class K> struct triu
  {
    typedef typename meta::as_integer<typename A::value_type>::type vtype; 
    triu( A const& a, K const& k) : k_(nt2::splat<vtype>(k)), a_(a) {}
    
    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;
      vtype i = nt2::enumerate<type>(boost::fusion::at_c<1>(p)-1);
      //       // here 2 pb ind2sub does not exists yet
      //       // Is a(ind) correct with a vector of contiguous indices
      //       // in fact we need a a(p) "vectorial" returning a simd vector
      //       // of elements of a from position p. In the present use
      //       // case the access can be aligned as soon as a is 
      //       Sub s = ind2sub(nt2::enumerate<type>(boost::fusion::at_c<1>(p)-1))
      //       return select(le(sub(1), sub(2)+k_), Zero<type>(), a(i)); 
      return Zero<type>(); 
    }
    
    A const& a_;
    vtype k_; 
  };
  
  //============================================================================
  // triu0 actual functor : just select
  //============================================================================
  template<class A> struct triu0
  {
    typedef typename meta::as_integer<typename A::value_type>::type vtype; 
    triu0( A const& a) : a_(a) {}
    
    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;
      vtype i = nt2::enumerate<type>(boost::fusion::at_c<1>(p)-1); 
      //       Sub s = ind2sub(nt2::enumerate<type>(boost::fusion::at_c<1>(p)-1))
      //       return select(le(sub(1), sub(2)), Zero<type>(), a(ind)); 
      return Zero<type>(); 
    }
    
    A const & a_;
  };    
} }
#endif
