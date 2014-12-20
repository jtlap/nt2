//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_GEMM_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_GEMM_HPP_INCLUDED

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
    struct gemm_ : ext::abstract_<gemm_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<gemm_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_gemm_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::gemm_, Site> dispatching_gemm_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::gemm_, Site>();
    }
    template<class... Args>
    struct impl_gemm_;
  }

  /*!
    @brief gemm - perform the matrix-matrix operation

    c := alpha*op(a)*op(b) + beta*c

       where  op(x) is one of

          op(x) = x   or   op(x) = trans(x)   or   op(x) = ctrans(x),

       alpha  and  beta are scalars, and a, b and c are matrices, with op(a)
       an m by k matrix, op(b)  a  k by n matrix and  c an m by n matrix.

    @param  transa - char.  on entry, transa specifies the form of op(a)
       to be used in the matrix multiplication as follows:

       transa = 'N' or 'n',  op(a) = a.

       transa = 'T' or 't',  op(a) = trans(a).

       transa = 'C' or 'c',  op(a) = ctrans(a).

       Unchanged on exit.

      @param  transb  -  char.  On entry, TRANSB specifies the form of op( B )
       to be used in the matrix multiplication as follows:

       transb = 'N' or 'n',  op(b) = b.

       transb = 'T' or 't',  op(b) = trans(b).

       transb = 'C' or 'c',  op(b) = ctrans(b).

       Unchanged on exit.

      @param  ALPHA  - scalar     .
              On entry, ALPHA specifies the scalar alpha.  Unchanged on  exit.

      @param a     -  container of dimension haxka, where ka is
              k   when   transa  =  'n' or 'n',  and is  m  otherwise.  before
              entry with  transa = 'n' or 'n',  the leading  m by  k  part  of
              the array a must contain the matrix  a,  otherwise the leading
              k by m  part of the  array  a  must  contain   the  matrix  a.
              unchanged on exit.

      @param  b    -  container of dimension hbxkb, ka is, where kb is
              n  when  transb = 'n' or 'n',  and  is   k   otherwise.   before
              entry  with   transb  = 'n' or 'n',  the leading  k by n part of
              the array  b  must contain the matrix  b,  otherwise the leading
              n  by  k   part  of  the  array   b  must contain  the matrix b.
              unchanged on exit.

      @param  beta   - scalar
              on  entry,   beta   specifies  the scalar  beta.  when  beta  is
              supplied as zero then c need not be set on input.  unchanged  on
              exit.

      @param   c container of dimension mxn.
              before  entry,  the  leading   m by n  part of the array  c must
              contain the matrix  c,  except when  beta   is  zero,  in  which
              case  c  need  not  be  set on entry.  on exit, the array  c  is
              overwritten by the  m by n  matrix ( alpha*op(a)*op(b)+ beta*c ).


  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::gemm_, gemm
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(const A5&)(A6&)
                                  , 7
                                  );

 } }

#endif

