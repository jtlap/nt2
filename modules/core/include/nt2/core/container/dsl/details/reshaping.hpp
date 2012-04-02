//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_RESHAPING_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_RESHAPING_HPP_INCLUDED

#include <boost/proto/core.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform.hpp>
#include <tn2/sdk/meta/add_settings.hpp>

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // This is the factorized size_of for all reshaping function.
  // For any given reshaping function tag RSH, the registration of their
  // size_of is simply :
  //
  // namespace nt2 { namespace container { namespace ext
  // {
  //  template<class Domain, class Expr, int N>
  //  struct size_of<RSH,Domain,N,Expr> : reshaping_size_of<Expr>
  //  {};
  // } } }
  //
  //============================================================================
  template<class Expr> struct reshaping_size_of
  {
    // The size is contained in the second child
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type  term_t;
    typedef typename boost::proto::result_of::value<term_t>::type     sizes_t;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::value( boost::proto::child_c<1>(e) );
    }
  };

  //============================================================================
  // This is the factorized generator for all reshaping function.
  // For any given reshaping function tag RSH, the registration of their
  // reshaper is simply :
  //
  // namespace nt2 { namespace container { namespace ext
  // {
  //  template<class Domain, class Expr, int N>
  //  struct generator<RSH,Domain,N,Expr> : reshaping_generator<Expr>
  //  {};
  // } } }
  //
  //============================================================================
  template<class Expr> struct reshaping_generator
  {
    // We behave as our child
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type  c_sema_t;
    typedef typename meta::semantic_of<c_sema_t>::type                sema_t;

    // .. except we have a special size
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type  c_sizes_t;
    typedef typename boost::proto::result_of::value<c_sizes_t>::type  sizes_t;

    // Rebuild proper expression type with semantic using the new size
    // and revoking any shape settings
    typedef expression< typename boost::remove_const<Expr>::type
                      , typename meta::
                        add_settings< sema_t
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
