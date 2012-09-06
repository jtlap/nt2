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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPINV_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_exp expinv
 *
 * \par Description
 * exponential inverse cumulative distribution
 *
 * All inv (inverse cumulative distribution functions  can be called with the syntax
 * r = xxxinv(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * values outside of [0 1] return Nan 
 * exponential has 1 parameters: mean value default of which is 1
 *
 * expinv can also be called using the following syntax:
 *
 *  nt2::tie(p,plo,pup) = expinv(x,mu,pcov,alpha)
 *
 * to produce confidence bounds for p when the input parameter mu is an estimate. 
 *  pcov is the variance of the estimated mu. alpha has a default value of 0.05, and
 * specifies 100*(1-alpha)% confidence bounds. xlo and xup are arrays of
 * the same size as x containing the lower and upper confidence bounds.
 * the bounds are based on a normal approximation for the distribution of
 * the log of the estimate of mu.
 * You can get a more accurate set ofbounds simply by using expfit to get a confidence
 * interval for mu,  and evaluating expinv at the lower and upper end points
 * of that interval.
 *
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/expinv.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::expinv_(A0)>::type
 *     expinv(const A0 & a0, const A1 & mu = 1);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag expinv_ of functor expinv 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct expinv_ : ext::tieable_<expinv_> { typedef ext::tieable_<expinv_> parent; };
    struct expinv0_ : ext::elementwise_<expinv0_> { typedef ext::elementwise_<expinv0_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::expinv0_, expinv, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::expinv0_, expinv, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::expinv_,  expinv, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::expinv_,  expinv, 4)
}


namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::expinv_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term0;
    typedef typename meta::strip<seq_term0>::type::extent_type          ext0_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type seq_term1;
    typedef typename meta::strip<seq_term1>::type::extent_type          ext1_t;
    //    typedef typename meta::max_extent_ < ext1_t, ext0_t>::type     result_type;
    typedef typename make_size< (ext0_t::static_size > ext1_t::static_size)
                                ? ext0_t::static_size
                                : ext1_t::static_size
                               >::type                              result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = nt2::extent(boost::proto::child_c<0>(e));
      result_type sizee1 = nt2::extent(boost::proto::child_c<1>(e)); 
      for(size_t i = 0; i < sizee.size(); ++i)
        {
          if (sizee[i] < sizee1[i]) sizee[i] = sizee1[i];
        }
      return sizee;
    }
  };
  template<class Domain, class Expr>
  struct  size_of<tag::expinv_,Domain,1,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename meta::strip<seq_term>::type::extent_type        result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
//       return boost::proto::child_c<0>(e).extent();
    }
  };
  template<class Domain, int N, class Expr>
  struct  generator<tag::expinv_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename boost::dispatch::meta::semantic_of<seq_term>::type sema_t;

    // Rebuild proper expression type with semantic
    typedef expression< typename boost::remove_const<Expr>::type
                      , sema_t
                      >                                     result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of expinv.hpp
// /////////////////////////////////////////////////////////////////////////////
