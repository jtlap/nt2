//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_BSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_BSXFUN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>

namespace nt2
{
  namespace tag
  {
    struct bsxfun_ : ext::elementwise_<bsxfun_>
    {
      typedef ext::elementwise_<bsxfun_> parent;
    };
  }

  //============================================================================
  /*!
   * bsxfun
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::bsxfun_, bsxfun, 3)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::bsxfun_,Domain,4,Expr>
        : boxed_size_of<Expr,3>
  {};

  template<class Domain, class Expr>
  struct  value_type<nt2::tag::bsxfun_,Domain,4,Expr>
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
} } }

#endif
