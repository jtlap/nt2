//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_HEMM_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_HEMM_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements rotm function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines rotm function tag
    struct hemm_ : ext::abstract_<hemm_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<hemm_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_hemm_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::hemm_, Site> dispatching_hemm_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::hemm_, Site>();
    }
    template<class... Args>
    struct impl_hemm_;
  }

  /*!
    @brief hemm - perform one of the following matrix-matrix operation

     c = alpha*a*b + beta*c,
     c = alpha*b*a + beta*c

     where alpha and beta are scalars, A is an hermitian matrix and  B and C
     are m by n matrices.


     @param   side   - char
              on entry,  side  specifies whether   the   hermitian  matrix   a
              appears on the  left or right  in the  operation as follows:

              side = 'L' or 'l'   c := alpha*a*b + beta*c,

              side = 'R' or 'r'   c := alpha*b*a + beta*c,

              Unchanged on exit.

      @param  uplo   - CHARACTER*1.
              On   entry,    uplo   specifies   whether  the  upper  or  lower
              triangular  part  of  the  hermitian  matrix    a   is   to   be
              referenced as follows:

              uplo = 'U' or 'u'   Only the upper triangular part of the hermi-
              tian matrix is to be referenced.

              uplo = 'L' or 'l'   Only the lower triangular part of the hermi-
              tian matrix is to be referenced.

              Unchanged on exit.

      @param  alpha  - scalar     .
              On entry, ALPHA specifies the scalar alpha.  Unchanged on  exit.

      @param  a      - container   array of dimension ( lda, ka ), where ka is
              m  when  side = 'l' or 'l'  and is n  otherwise.   before  entry
              with   side  =  'l'  or  'l',  the  m by m  part of the array  a
              must contain the  hermitian matrix,  such that when  uplo =  'u'
              or 'u', the leading m by m upper triangular part of the array  a
              must contain the upper triangular part of the  hermitian  matrix
              and  the   strictly   lower triangular part of  a  is not refer-
              enced,  and when  uplo = 'l' or 'l', the leading  m by m   lower
              triangular part  of the  array  a must  contain  the  lower tri-
              angular part  of the  hermitian matrix and the   strictly  upper
              triangular  part  of   a  is not referenced.  before entry  with
              side = 'r' or 'r',  the  n by n  part of the array  a  must con-
              tain  the  hermitian matrix,  such that when  uplo = 'u' or 'u',
              the leading n by n upper triangular part of the array   a   must
              contain  the  upper triangular part of the  hermitian matrix and
              the  strictly  lower triangular part of  a  is  not  referenced,
              and when  uplo = 'l' or 'l', the leading  n by n  lower triangu-
              lar part  of the  array  a must  contain  the  lower  triangular
              part   of the  hermitian matrix and the  strictly upper triangu-
              lar part of  a  is not  referenced.   note  that  the  imaginary
              parts   of  the  diagonal  elements  need  not  be set, they are
              assumed to be zero.  unchanged on exit.


      @param  b    -  container of dimension ldbxn
              Before  entry,  the  leading   m by n part of the array  B  must
              contain the matrix B.  Unchanged on exit.

      @param  beta   - scalar
              on  entry,   beta   specifies  the scalar  beta.  when  beta  is
              supplied as zero then c need not be set on input.  unchanged  on
              exit.

      @param   c container of dimension mxn.
               before entry, the leading  m by n  part of  the  array   c  must
              contain  the  matrix   c,   except when  beta  is zero, in which
              case c need not be set on entry.  on  exit,  the  array   c   is
              overwritten by the  m by n updated matrix.

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::hemm_, hemm
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(const A5&)(A6&)
                                  , 7
                                  );

 } }

#endif

