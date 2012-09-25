//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_BSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_BSXFUN_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the bsxfun function
 **/

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <boost/assert.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for bsxfun functor
     **/
    struct bsxfun_ : ext::elementwise_<bsxfun_>
    {
      typedef ext::elementwise_<bsxfun_> parent;
    };
  }

  /*!
    @brief Apply element-by-element binary operation to two expressions
    with singleton expansion enabled

    bsxfun(f,a,b) applies the element-by-element binary @pfo @c f to expressions
    @c a and @c b, with singleton expansion enabled.

    The corresponding dimensions of @c a and @c b must be equal to each other
    or equal to one. Whenever a dimension of @c a or @c b is singleton (i.e equal
    to one), bsxfun virtually replicates the array along that dimension to match
    the other array.

    @param f Binary Polymorphic Function object to apply
    @param a First expression to process
    @param b Second expression to process
  **/
  template<class Functor, class A0, class A1> BOOST_FORCEINLINE
  typename meta::call<tag::bsxfun_(Functor const&, A0 const&, A1 const&)>::type
  bsxfun(Functor const& f, A0 const& a, A1 const& b)
  {
    return typename make_functor<tag::bsxfun_, A0>::type()(f,a,b);
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::bsxfun_,Domain,N,Expr>
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
      result_type sizee ;

      for(size_t i = 0; i < sizee.size(); ++i)
      {
        BOOST_ASSERT_MSG
        ( (s1[i] == s2[i]) || (s1[i] == 1) || (s2[i] == 1)
        , "Error using bsxfun:\n"
          "Non-singleton dimensions of the two input arrays "
          "must match each other."
        );

        sizee[i] = s1[i];
        if(s1[i] == 1) sizee[i] = s2[i];
        if(s2[i] == 1) sizee[i] = s1[i];
      }

      return sizee;
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::bsxfun_,Domain,N,Expr>
  {
    typedef typename meta::
            call< nt2::tag::bsxfun_
                ( typename  boost::proto::result_of
                            ::child_c<Expr&,2>::value_type::value_type
                , typename  boost::proto::result_of
                            ::child_c<Expr&,0>::value_type::value_type
                , typename  boost::proto::result_of
                            ::child_c<Expr&,1>::value_type::value_type
                )
                >::type                            type;
  };
} }

#endif
