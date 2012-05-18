//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPAND_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::expand function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct expand_ : ext::reshaping_<expand_>
    {
      typedef ext::reshaping_<expand_> parent;
    };
  }

  //============================================================================
  /*!
   * expand an expression
   *
   * \param xpr   Expression to expand
   * \param size  New size of the expression
   */
  //============================================================================
  #define M0(z,n,t)                                         \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::expand_, expand, n) \
  /**/
  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)
  #undef M0
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::expand_,Domain,2,Expr>
        : boxed_size_of<Expr,1>
  {};

  template<class Domain, class Expr>
  struct  generator<nt2::tag::expand_,Domain,2,Expr>
  {
    // We behave as our child but without allowing references
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type  child0;
    typedef typename boost::dispatch::meta::semantic_of<child0>::type sema_t;
    typedef typename meta::strip<sema_t>::type                        cont_t;

    // .. except we have a special size
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type  child1;
    typedef typename boost::proto::result_of::value<child1>::type     extent_t;
    typedef typename meta::strip<extent_t>::type                      sizes_t;

    // Rebuild proper expression type with semantic using the new size
    // and revoking any shape settings
    typedef expression< typename boost::remove_const<Expr>::type
                      , typename meta::
                        add_settings< cont_t
                                    , settings(rectangular_,sizes_t)
                                    >::type
                      >                                             result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }
#endif
