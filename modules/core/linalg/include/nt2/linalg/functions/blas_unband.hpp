//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_UNBAND_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_UNBAND_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_unband function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/width.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag blas_unband_ of functor blas_unband
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct blas_unband_ : ext::unspecified_<blas_unband_>
    {
      typedef ext::unspecified_<blas_unband_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_unband_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
}
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_unband_, Site> dispatching_blas_unband_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_unband_, Site>();
    }
    template<class... Args>
    struct impl_blas_unband_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::blas_unband_, blas_unband, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::blas_unband_, blas_unband, 4)
  /*!
    @brief unband a dense matrix  it in a (kl+ku+1)xn storage


    @code
    dest = unband ( srce, m, kl, ku)
    @endcode

    @param srce band matrix stored in (kl+ku+1)*n
    @param m  number of rows of the full matrix
    @param kl number of sub-diagonals of the stored matrix
    @param ku number of super-diagonals of the stored matrix
    @return dense matrix  mxn represented by srce
  **/
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::blas_unband_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t m = width(boost::proto::child_c<0>(e));
      size_t n = width(boost::proto::child_c<1>(e));
      _2D sizee = extent(n*m);
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::blas_unband_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                            s_type;
    typedef typename  s_type::value_type                                       type;
  };
} }

#endif
