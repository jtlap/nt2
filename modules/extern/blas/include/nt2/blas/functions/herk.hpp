//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_HERK_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_HERK_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements herk function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines herk function tag
    struct herk_ : ext::abstract_<herk_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<herk_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_herk_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::herk_, Site> dispatching_herk_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::herk_, Site>();
    }
    template<class... Args>
    struct impl_herk_;
  }

  /*!
    @brief herk  -  perform  one  of  the  hermitian  rank  k  operations

    c  =  alpha*a*ctrans(a) + beta*c,

    c =   alpha*ctrans(a)*a + beta*c


      @param  uplo   - CHARACTER*1.
              On   entry,    uplo   specifies   whether  the  upper  or  lower
              triangular  part  of  the  hermitian  matrix    a   is   to   be
              referenced as follows:

              uplo = 'U' or 'u'   Only the upper triangular part of the hermi-
              tian matrix is to be referenced.

              uplo = 'L' or 'l'   Only the lower triangular part of the hermi-
              tian matrix is to be referenced.

              Unchanged on exit.

     @param trans  - char
              On entry, trans specifies the operation to be performed as  follows:

              trans = 'N' or 'n'   x := A*x.

              trans = 'T' or 't'   x := A'*x.

              trans = 'C' or 'c'   x := conjg( A' )*x.

              unchanged on exit.

      @param alpha  - real scalar
              on  entry, alpha specifies the scalar alpha.  unchanged on exit.

      @param a    array of dimension ( lda, ka ), where ka is
              k  when  trans = 'n' or 'n',   and  is   n   otherwise.   before
              entry  with   trans  = 'n' or 'n',  the  leading  n by k part of
              the array  a  must contain the matrix  a,  otherwise the leading
              k  by  n   part  of  the  array   a  must contain  the matrix a.
              unchanged on exit.

      @param beta   - real scalar
              on entry, beta specifies the scalar beta.  unchanged on exit.

      @param c      -  container of dimension ( ldc, n ).
              before  entry   with   uplo  =  'u' or 'u',  the leading  n by n
              upper triangular part of the array c must contain the upper tri-
              angular  part   of the  hermitian matrix  and the strictly lower
              triangular part of c is not referenced.  on exit, the upper tri-
              angular  part of the array  c is overwritten by the upper trian-
              gular part of the updated matrix.  before entry   with   uplo  =
              'l'  or  'l',   the leading  n by n lower triangular part of the
              array c must contain the lower triangular part  of  the   hermi-
              tian  matrix  and the strictly upper triangular part of c is not
              referenced.  on exit, the lower triangular part of the array   c
              is  overwritten  by  the  lower  triangular  part of the updated
              matrix.  note that the imaginary parts of the diagonal  elements
              need not be set,  they are assumed to be zero,  and on exit they
              are set to zero.
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::herk_, herk
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(A5&)
                                  , 6
                                  );

 } }

#endif

