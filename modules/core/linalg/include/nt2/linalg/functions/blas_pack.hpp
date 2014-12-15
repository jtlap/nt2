//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_PACK_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_PACK_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_pack function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/height.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag blas_pack_ of functor blas_pack
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct blas_pack_ : ext::unspecified_<blas_pack_>
    {
      typedef ext::unspecified_<blas_pack_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_pack_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
}
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_pack_, Site> dispatching_blas_pack_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_pack_, Site>();
    }
    template<class... Args>
    struct impl_blas_pack_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::blas_pack_, blas_pack, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::blas_pack_, blas_pack, 2)
  /*!
    @brief pack a dense matrix according to its to packed storage
    The matrix is supposed triangular hermitian or symmetric
    uplo indicates which part of the dense matrix is accessed to construct the result

    @code
    dest = pack ( uplo, srce)
    @endcode

    @param uplo 'U' or 'L'
    @param srce dense matrix nxn
    @return  dense vector containing the packed storage of numel nx(n-1)/2
  **/
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::blas_pack_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n = height(boost::proto::child_c<1>(e));
      _2D sizee = extent((n*(n+1) >> 1));
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::blas_pack_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,1>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                            s_type;
    typedef typename  s_type::value_type                                       type;
  };
} }

#endif
