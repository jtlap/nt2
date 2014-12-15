//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BAND_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BAND_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_band function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/width.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag blas_band_ of functor blas_band
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct blas_band_ : ext::unspecified_<blas_band_>
    {
      typedef ext::unspecified_<blas_band_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_band_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
}
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_band_, Site> dispatching_blas_band_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_band_, Site>();
    }
    template<class... Args>
    struct impl_blas_band_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::blas_band_, blas_band, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::blas_band_, blas_band, 3)
  /*!
    @brief band a dense matrix  it in a (kl+ku+1)xn storage


    @code
    dest = band ( srce, kl, ku)
    @endcode

    @param srce dense matrix mxn
    @param kl number of sub-diagonals of the matrix to be stored
    @param ku number of super--diagonals of the matrix to be stored
    @return dense matrix  (kl+ku+1)xn representing the band
  **/
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::blas_band_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n = width(boost::proto::child_c<0>(e));
      size_t kl = boost::proto::child_c<1>(e);
      size_t ku = boost::proto::child_c<2>(e);
      _2D sizee = extent(n*(kl+ku+1));
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::blas_band_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                            s_type;
    typedef typename  s_type::value_type                                       type;
  };
} }

#endif
