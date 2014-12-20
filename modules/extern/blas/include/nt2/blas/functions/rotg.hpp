//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_ROTG_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_ROTG_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements rotg function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines rotg function tag
    struct rotg_ : ext::abstract_<rotg_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<rotg_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_rotg_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::rotg_, Site> dispatching_rotg_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::rotg_, Site>();
    }
    template<class... Args>
    struct impl_rotg_;
  }

  /*!
    @brief Generates plane rotation

    @code
    rotg(a, b, c, s)
    @endcode

    computes a Givens rotation (c,s) which zeroes the second component of vector (a,b),

    [  c  s ] [ a ] = [ r ]
    [ -s  c ] [ b ]   [ 0 ]

    The variables a and b are overwritten by the routine.
    These functors are defined for float and double entries

    @param a
    @param b
    @param c L-value to receive the cosine
    @param s L-value to receive the sine

    @return Meaning of the Output L-Values:
       a       (input and output) floating scalar L-value

               First vector component.  On input, the first component  of  the
               vector to be rotated.  On output, a is overwritten by by r, the
               first component of the vector in the rotated coordinate  system
               where:

               r = sign(sqrt(a**2 + b**2),a), if |a| > |b|

               r = sign(sqrt(a**2 + b**2),b), if |a| <= |b|

       b       (input and output) floating scalar L-value
               Second vector component.

               On input, the second component of the vector to be rotated.  On
               output, b contains z, where:

                   z=s    if  |a| >  |b|
                   z=1/c  if  |a| <= |b|  and  c != 0  and r != 0
                   z=1    if  |a| <= |b|  and  c  = 0  and r != 0
                   z=0    if  r = 0

       c       (output)  floating scalar L-value
               Cosine of the angle of rotation:

                    c = a/r  if  r != 0
                    c = 1    if  r  = 0

       s       (output)  floating scalar L-value
               Sine of the angle of rotation:

                    s = b/r  if  r != 0
                    s = 0    if  r  = 0
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::rotg_, rotg
                                  , (A0&)(A1&)(A2&)(A3&)
                                  , 4
                                  );

 } }

#endif

