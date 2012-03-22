//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SUM_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/include/functions/plus.hpp>
#include <boost/simd/toolbox/constant/constants/zero.hpp>
#include <iostream>

/*!
 * \ingroup boost_simd_reduction
 * \defgroup boost_simd_reduction_sum sum
 *
 * \par Description
 * Returns the sum of the elements of the SIMD vector
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/sum.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::sum_(A0)>::type
 *     sum(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sum
 * 
 * \return always a scalar value
 *  
 * \par Notes
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation always has a scalar result which translate a property
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag sum_ of functor sum 
     *        in namespace boost::simd::tag for toolbox boost.simd.reduction
    **/
    struct sum_ : ext::reduction_<sum_, tag::plus_, tag::Zero> 
    { 
      typedef ext::reduction_<sum_, tag::plus_, tag::Zero> parent; 
    };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sum_, sum, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sum_, sum, 2)

} }

namespace nt2 { namespace container { namespace ext
{

  template<class Domain, class Expr>
  struct  size_of<boost::simd::tag::sum_,Domain,1,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr,0>::type     expr_t;
    typedef typename nt2::make_size<NT2_MAX_DIMENSIONS>::type            result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type res;
      for(std::size_t i =0; i < NT2_MAX_DIMENSIONS; ++i)
        res[i] = 1;

      return res;
    }
    
  };

  template<class Domain, class Expr>
  struct  size_of<boost::simd::tag::sum_,Domain,2,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr,0>::type      expr_t;
    typedef typename nt2::make_size<NT2_MAX_DIMENSIONS>::type            result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type res = boost::proto::child_c<0>(e).extent();
      res[boost::proto::child_c<1>(e)-1] = 1;
      return res;
    }
    
  };


  template<class Domain, class Expr, int N>
  struct  generator<boost::simd::tag::sum_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr,0>::type               expr_t;
    typedef typename boost::dispatch::meta::semantic_of<expr_t>::type             sema_t;

    typedef typename boost::proto::tag_of<Expr>::type                             tag_type;
    typedef typename size_of<boost::simd::tag::sum_,Domain,N,Expr>::result_type   size_type;
    typedef typename nt2::memory::container< typename sema_t::tag_type
                                             , nt2::id_<0>
                                             , typename sema_t::value_type
                                             , size_type >                        type;

    typedef expression< typename boost::remove_const<Expr>::type
                      , type
                      >                                                           result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };




} } }

#endif

// modified by jt the 25/12/2010
