/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_PCHIP_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_PCHIP_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_cau pchip
 *
 * \par Description
 * one dimensional pchip interpolation
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/pchip.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::pchip_(A0)>::type
 *     pchip(const A0 & x, const A1 & y, const A2 & xi, const A3 & extrap);
 * }
 * \endcode
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag pchip_ of functor pchip 
     *        in namespace nt2::tag for toolbox interpol
    **/
    struct pchip_ : ext::unspecified_<pchip_> { typedef ext::unspecified_<pchip_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::pchip_, pchip, 3)  
  NT2_FUNCTION_IMPLEMENTATION(tag::pchip_, pchip, 4)  
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct size_of<tag::pchip_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 2>::value_type child1;
    typedef typename child1::extent_type                               result_type; 

    result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<2>(e).extent();
    }
  };

 template <class Domain, class Expr,  int N>
 struct value_type < tag::pchip_, Domain,N,Expr> {
   typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type  child1;
   typedef typename nt2::meta::scalar_of<child1>::type                    elt_type;
   typedef typename nt2::meta::strip<elt_type>::type                          type;
 }; 
} } }
#endif
