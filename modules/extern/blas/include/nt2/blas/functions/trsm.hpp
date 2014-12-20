//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_TRSM_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_TRSM_HPP_INCLUDED

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
    struct trsm_ : ext::abstract_<trsm_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<trsm_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_trsm_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::trsm_, Site> dispatching_trsm_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::trsm_, Site>();
    }
    template<class... Args>
    struct impl_trsm_;
  }

  /*!
    @brief trsm  solves one of the matrix equations
          op( a )*x = alpha*b
       or
          x*op( a ) = alpha*b

       where  alpha  is a scalar, x and b are m by n matrices, a is a unit, or
       non-unit,  upper or lower triangular matrix  and  op( a )  is one  of

        op(x) = x   or   op(x) = trans(x)   or   op(x) = ctrans(x),

       the matrix b is overwritten by x.
    @param   side   - char
              on entry,  side  specifies whether   the   symmetric  matrix   a
              appears on the  left or right  in the  operation as follows:

              side = 'L' or 'l'   c := alpha*a*b + beta*c,

              side = 'R' or 'r'   c := alpha*b*a + beta*c,

              Unchanged on exit.

      @param  uplo   - CHARACTER*1.
              On   entry,    uplo   specifies   whether  the  upper  or  lower
              triangular  part  of  the  symmetric  matrix    a   is   to   be
              referenced as follows:

              uplo = 'U' or 'u'   Only the upper triangular part of the hermi-
              tian matrix is to be referenced.

              uplo = 'L' or 'l'   Only the lower triangular part of the hermi-
              tian matrix is to be referenced.

              Unchanged on exit.


    @param  transa - char.  on entry, transa specifies the form of op(a)
       to be used in the matrix multiplication as follows:

       transa = 'N' or 'n',  op(a) = a.

       transa = 'T' or 't',  op(a) = trans(a).

       transa = 'C' or 'c',  op(a) = ctrans(a).

       Unchanged on exit.


     @param diag   - char
              On  entry, diag specifies whether or not A is unit triangular as
              follows:

              diag = 'U' or 'u'   a is assumed to be unit triangular.

              diag = 'N' or 'n'   a is not assumed to be unit triangular.

              unchanged on exit.

      @param  alpha  - scalar     .
              on  entry,   alpha  specifies  the scalar  alpha. when  alpha is
              zero then  a is not referenced and  b need  not  be  set  before
              entry.  unchanged on exit.

      @param  a      container of dimension ( lda, k ), where k is m
              when   side  =  'l'  or 'l'  and is  n  when  side = 'r' or 'r'.
              before entry  with  uplo = 'u' or 'u',  the   leading   k  by  k
              upper  triangular  part  of  the array  a must contain the upper
              triangular matrix  and the strictly lower triangular part  of  a
              is  not referenced.  before entry  with  uplo = 'l' or 'l',  the
              leading  k by k lower triangular part of the array  a must  con-
              tain  the lower triangular matrix  and the strictly upper trian-
              gular part of a is not referenced.  note that when  diag  =  'u'
              or  'u',  the diagonal elements of a  are not referenced either,
              but are assumed to be  unity.  unchanged on exit.

      @param  b    container of dimension ( ldb, n ).
              before  entry,   the  leading   m by n part of the array  b must
              contain the matrix  b,  and  on exit   is  overwritten   by  the
              transformed matrix.

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::trsm_, trsm
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(const A5&)(A6&)
                                  , 7
                                  );

 } }

#endif

