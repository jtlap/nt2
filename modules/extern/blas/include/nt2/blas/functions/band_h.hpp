//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_BAND_H_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_BAND_H_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements band_h function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/width.hpp>

namespace nt2 { namespace blas { namespace tag
  {
    /*!
     * \brief Define the tag band_h_ of functor band_h
     *        in namespace nt2 { namespace blas::tag for toolbox algebra
     **/
    struct band_h_ : ext::unspecified_<band_h_>
    {
      typedef ext::unspecified_<band_h_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_band_h_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
}
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::band_h_, Site> dispatching_band_h_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::band_h_, Site>();
    }
    template<class... Args>
    struct impl_band_h_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::band_h_, band_h, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::band_h_, band_h, 3)
  /*!
    @brief band_h a dense matrix  it in a (kl+ku+1)xn storage


    @code
    dest = band_h ( uplo, srce, kd)
    @endcode

    @param srce dense matrix nxn symetric or hermitian
    @param uplo 'U' or 'L'
    @param kd number of sub/super--diagonals of the matrix to be stored
    @return dense matrix  (kd+1)xn representing the (half) band
  **/
}

namespace nt2 { namespace blas { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::band_h_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n = width(boost::proto::child_c<1>(e));
      size_t kd = boost::proto::child_c<2>(e);
      _2D sizee = extent(n*(kd+1));
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::band_h_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,1>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                            s_type;
    typedef typename  s_type::value_type                                       type;
  };
}  } }

#endif
