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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_IDX_LINEAR_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_IDX_LINEAR_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
/*!
 * \ingroup interpol
 * \defgroupinterpol_idx_linear idx_linear
 *
 * \par Description
 * one dimensional idx_linear interpolation
 * given an array a and a vector idx of "real" indices
 * provides the interpolated values along the a rows
 * by linear formula.
 * calls can be idx_linear(a, idx)
 *              idx_linear(a, idx, true) allowing extrapolation
 *              idx_linear(a, idx, val1) putting val1 outside the bounds
 *              idx_linear(a, idx, val1, val2)}, putting val1 under the index bounds val2 ovr
 *              idx_linear(a, idx, _, dim) dim is the dimension of interpolation firstnonsingletopn of xi by default
 *              idx_linear(a, idx, val1, dim)
 *              idx_linear(a, idx, val1, val2, dim) can also be used
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/idx_linear.hpp>
 * \endcode
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag idx_linear_ of functor idx_linear 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct idx_linear_ : ext::unspecified_<idx_linear_> { typedef ext::unspecified_<idx_linear_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 2)  
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 3)  
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 5)
}

namespace nt2 { namespace container { namespace ext
{
//   template<class Domain, class Expr,  int N>
//   struct size_of<tag::idx_linear_, Domain, N, Expr> //N = 2, 3
//   {
//     typedef typename boost::proto::result_of::child_c<Expr&,0>::type       value_t;
//     typedef typename boost::proto::result_of::child_c<Expr&,1>::type         idx_t;
//     typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  child0;
//     typedef typename child0::extent_type                               result_type; 

//     result_type operator()(Expr& e) const
//     {
//       result_type sizee     = boost::proto::child_c<0>(e).extent(); 
//       sizee[nt2::firstnonsingleton(boost::proto::child_c<1>(e))-1] =
//         numel(boost::proto::child_c<1>(e));
//       return sizee;
//     }
//   };
   
  template<class Domain, class Expr,  int N>
  struct size_of<tag::idx_linear_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type       value_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type         idx_t;
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  child0;
    typedef typename boost::proto::result_of::child_c<Expr&,N-1>::type    choice_t; 
    typedef typename child0::extent_type                               result_type; 

    result_type operator()(Expr& e) const
    {
      const value_t & y     =  boost::proto::child_c<0>(e);
      const idx_t & xi      =  boost::proto::child_c<1>(e);
      const choice_t & v    =  boost::proto::child_c<N-1>(e);
      typedef typename nt2::meta::is_integral<choice_t>::type c_t; 
      std::size_t dim       =  getdim(xi, v, c_t());
      result_type sizee = y.extent(); 
      sizee[dim-1] = numel(xi);
      return sizee;
    }
    static std::size_t getdim(const idx_t & xi, const choice_t &, const boost::mpl::false_& )
    {return nt2::firstnonsingleton(xi); }
    static std::size_t getdim(const idx_t &, const choice_t &v, const boost::mpl::true_& )
    {return v; }
  
  }; 
//   template<class Domain, class Expr>
//   struct size_of<tag::idx_linear_, Domain, 5, Expr>
//   {
//     typedef typename boost::proto::result_of::child_c<Expr&,0>::type       value_t;
//     typedef typename boost::proto::result_of::child_c<Expr&,1>::type         idx_t;
//     typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  child0;
//     typedef typename child0::extent_type                               result_type; 

//     result_type operator()(Expr& e) const
//     {
//       const value_t & y     =  boost::proto::child_c<0>(e);
//       const idx_t & xi      =  boost::proto::child_c<1>(e);
//       std::size_t dim       =  boost::proto::child_c<4>(e);
//       result_type sizee = y.extent(); 
//       sizee[dim-1] = numel(xi);
//       return sizee;
//     }
//   };

  template <class Domain, class Expr,  int N>
  struct value_type < tag::idx_linear_, Domain,N,Expr> {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type  child1;
    typedef typename nt2::meta::scalar_of<child1>::type                    elt_type;
    typedef typename nt2::meta::strip<elt_type>::type                          type;
  }; 
} } }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of idx_linear.hpp
// /////////////////////////////////////////////////////////////////////////////
