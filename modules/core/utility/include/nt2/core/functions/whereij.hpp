//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_WHEREIJ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_WHEREIJ_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the whereij function
 **/

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/isscalar.hpp>
#include <boost/assert.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for whereij functor
     **/
    struct whereij_ : ext::elementwise_<whereij_>
    {
      typedef ext::elementwise_<whereij_> parent;
    };
  }

  /*!
    @brief Act as : for i for j r(i, j) = f(i, j) ? a(i, j) : b(i, j)
    @param f Binary Polymorphic Function object to apply to 0 based indices
    @param a First expression to process
    @param b Second expression to process
  **/
  template<class Functor, class A0, class A1> BOOST_FORCEINLINE
  typename meta::call<tag::whereij_(Functor const&, A0 const&, A1 const&)>::type
  whereij(Functor const& f, A0 const& a, A1 const& b)
  {
    return typename make_functor<tag::whereij_, A0>::type()(f,a,b);
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::whereij_,Domain,N,Expr>
  {
    // TODO dual static of_size case to handle
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type  c1_t;
    typedef typename c0_t::extent_type                                      e1_t;
    typedef typename c1_t::extent_type                                      e2_t;
    typedef typename make_size< !(e1_t::static_size <= e2_t::static_size)
                                ? e1_t::static_size
                                : e2_t::static_size
                              >::type                               result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type s1 = boost::proto::child_c<0>(e).extent();
      result_type s2 = boost::proto::child_c<1>(e).extent();
      BOOST_ASSERT_MSG(s1 == s2 ||
                       nt2::isscalar(boost::proto::child_c<0>(e)) ||
                       nt2::isscalar(boost::proto::child_c<1>(e)), "incompatible sizes using whereij");
      return s1;
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::whereij_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                  ::child_c<Expr&,0>::value_type::value_type  type;
  };
} }

#endif
