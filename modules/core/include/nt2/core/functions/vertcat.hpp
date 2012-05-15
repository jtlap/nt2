//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_VERTCAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_VERTCAT_HPP_INCLUDED

#include <nt2/sdk/parameters.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>


namespace nt2
{
  namespace tag
  {
    struct  vertcat_
          : ext::elementwise_<vertcat_> { typedef ext::elementwise_<vertcat_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, vertcat, 1) 
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, vertcat, 2) 
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::vertcat_,Domain,3,Expr>
        : boxed_size_of<Expr,2>
  {};

  template<class Domain, int N, class Expr>
  struct  generator<nt2::tag::vertcat_,Domain,N,Expr>
  {
    // We behave as our child
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type    c_sema_t;
    typedef typename boost::dispatch::meta::semantic_of<c_sema_t>::type sema_t;

    // .. except we have a special size
    typedef typename boxed_size_of<Expr, 2>::result_type               sizes_t;

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
