//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_UNBAND_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_UNBAND_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements unband function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/width.hpp>

namespace nt2 { namespace blas { namespace tag
  {
    /*!
     * \brief Define the tag unband_ of functor unband
     *        in namespace nt2 { namespace blas::tag for toolbox algebra
     **/
    struct unband_ : ext::unspecified_<unband_>
    {
      typedef ext::unspecified_<unband_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_unband_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
}
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::unband_, Site> dispatching_unband_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::unband_, Site>();
    }
    template<class... Args>
    struct impl_unband_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::unband_, unband, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::unband_, unband, 4)
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

namespace nt2 { namespace blas { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::unband_, Domain, N, Expr>
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
  struct value_type < tag::unband_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                            s_type;
    typedef typename  s_type::value_type                                       type;
  };
}  } }

#endif
