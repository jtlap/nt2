//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_UNPACK_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_UNPACK_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_unpack function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/constants/eight.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag blas_unpack_ of functor blas_unpack
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct blas_unpack_ : ext::unspecified_<blas_unpack_>
    {
      typedef ext::unspecified_<blas_unpack_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_unpack_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
}
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_unpack_, Site> dispatching_blas_unpack_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_unpack_, Site>();
    }
    template<class... Args>
    struct impl_blas_unpack_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::blas_unpack_, blas_unpack, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::blas_unpack_, blas_unpack, 3)
  /*!
    @brief unpack a packed matrix according to its to unpacked storage
    The matrix is supposed triangular hermitian or symmetric
    uplo indicates which part of the dense matrix is accessed to construct the result

    @code
    dest = unpack ( uplo, shape, srce)
    @endcode

    @param uplo 'U' or 'L'
    @param shape can be 'H' hermitian 'S' symmetric and 'T' triangular
    @param srce packed vector of numel nx(n-1)/2
    @return  dense matrix of dimension nxn
  **/
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::blas_unpack_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t nn = numel(boost::proto::child_c<2>(e));
      size_t n = iround(sqrt(oneplus(Eight<size_t>()*nn))) >> 1;
      _2D sizee = extent(n);
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::blas_unpack_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,2>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                            s_type;
    typedef typename  s_type::value_type                                       type;
  };
} }

#endif
