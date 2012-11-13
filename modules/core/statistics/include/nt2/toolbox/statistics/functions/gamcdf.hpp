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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GAMCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GAMCDF_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/utility/max_extent.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_exp gamcdf
 *
 * \par Description
 * gamma  cumulative distribution
 *
 * All cdf (cumulative distribution functions  can be called with the syntax
 * r = xxxcdf(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * gamma has 2 parameters: shape (a) and scale (b)
 *
 * Some references refer to the gamma distribution with a single
 * parameter.  This corresponds to the default of b = 1.
 * a has no default.
 *
 * gamcdf can also be called using the following syntax:
 *
 *  nt2::tie(p,plo,pup) = gamcdf(x, a, b, pcov, alpha)
 *
 * to produce confidence bounds for p when the input parameter mu is an estimate. 
 *  pcov is 2x2 matrix of the estimated a, b,  alpha has a default value of 0.05, and
 * specifies 100*(1-alpha)% confidence bounds.  plo and pup are arrays of
 * the same size as p containing the lower and upper confidence bounds.
 *
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/gamcdf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::gamcdf_(A0)>::type
 *     gamcdf(const A0 & a0, const A1 & mu = 1);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag gamcdf_ of functor gamcdf 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct gamcdf_ : ext::tieable_<gamcdf_> { typedef ext::tieable_<gamcdf_> parent; };
    struct gamcdf0_: ext::elementwise_<gamcdf0_> { typedef ext::elementwise_<gamcdf0_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::gamcdf0_, gamcdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::gamcdf0_, gamcdf, 3)    
  NT2_FUNCTION_IMPLEMENTATION(tag::gamcdf_, gamcdf, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::gamcdf_, gamcdf, 5)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::gamcdf_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term0;
    typedef typename meta::strip<seq_term0>::type::extent_type          ext0_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type seq_term1;
    typedef typename meta::strip<seq_term1>::type::extent_type          ext1_t;
    typedef typename boost::proto::result_of::child_c<Expr&,2>::type seq_term2;
    typedef typename meta::strip<seq_term2>::type::extent_type          ext2_t;

    typedef typename utility::result_of::max_extent<ext2_t, ext1_t, ext0_t>::type     result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
     return utility::max_extent(nt2::extent(boost::proto::child_c<0>(e)),
                       nt2::extent(boost::proto::child_c<1>(e)), 
                       nt2::extent(boost::proto::child_c<2>(e)));
    }
  };
  
  template<class Domain, class Expr>
  struct  size_of<tag::gamcdf_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::gamcdf_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} } 

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of gamcdf.hpp
// /////////////////////////////////////////////////////////////////////////////
