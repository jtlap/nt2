//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TSXFUN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>

/*!
 * \ingroup core
 * \defgroup core tsxfun
 *
 * \par Description
 * Returns the tsxfun of functor of 3 variables applied to
 * the three other parameters with singleton expansion
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/tsxfun.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1, class A2, class A3>
 *     meta::call<tag::tsxfun_(A0, A1, A2, A3)>::type
 *     tsxfun(const A0 & a0, const A1 & a1, const A2 & a2, const A3 & a3);
 * }
 * \endcode
 *
 * \param a0 a three parameters elementwise func...something
 * \param a1 a2 a3 the two parameters on which func will be applied
 *        elementwise with singleton expansion
 *
 *
 * \par
 *
**/


namespace nt2
{
  namespace tag
  {
    struct tsxfun_ : ext::elementwise_<tsxfun_>
    {
      typedef ext::elementwise_<tsxfun_> parent;
    };
  }

  //============================================================================
  /*!
   * tsxfun
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tsxfun_       , tsxfun, 4)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::tsxfun_,Domain,5,Expr>
        : boxed_size_of<Expr,4>
  {};

  template<class Domain, class Expr>
  struct  value_type<nt2::tag::tsxfun_,Domain,5,Expr>
  {
    typedef typename meta::
            call< nt2::tag::tsxfun_
                ( typename  boost::proto::result_of
                            ::child_c<Expr&,3>::value_type::value_type
                , typename  boost::proto::result_of
                            ::child_c<Expr&,0>::value_type::value_type
                , typename  boost::proto::result_of
                            ::child_c<Expr&,1>::value_type::value_type
                , typename  boost::proto::result_of
                            ::child_c<Expr&,2>::value_type::value_type
                )
                >::type                            type;

  };
} } }

#endif
