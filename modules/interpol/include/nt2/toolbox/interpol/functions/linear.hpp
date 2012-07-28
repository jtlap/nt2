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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_LINEAR_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_LINEAR_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_cau linear
 *
 * \par Description
 * one dimensional linear interpolation
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/linear.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::linear_(A0)>::type
 *     linear(const A0 & a0, const A1 & a1, const A2 & a2);
 * }
 * \endcode
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag linear_ of functor linear 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct linear_ : ext::unspecified_<linear_> { typedef ext::unspecified_<linear_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::linear_, linear, 3)  
  NT2_FUNCTION_IMPLEMENTATION(tag::linear_, linear, 4)  
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct size_of<tag::linear_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 2>::value_type child1;
    typedef typename child1::extent_type                               result_type; 

    result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<2>(e).extent();
    }
  };

 template <class Domain, class Expr,  int N>
 struct value_type < tag::linear_, Domain,N,Expr> {
   typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type  child1;
   typedef typename nt2::meta::scalar_of<child1>::type                    elt_type;
   typedef typename nt2::meta::strip<elt_type>::type                          type;
 }; 
} } }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of linear.hpp
// /////////////////////////////////////////////////////////////////////////////
