//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_ROTMG_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_ROTMG_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements rotmg function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines rotmg function tag
    struct rotmg_ : ext::abstract_<rotmg_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<rotmg_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_rotmg_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::rotmg_, Site> dispatching_rotmg_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::rotmg_, Site>();
    }
    template<class... Args>
    struct impl_rotmg_;
  }

  /*!
    @brief Generates modified plane rotation

    @code
    blas_rotg(d1, d2, x1, y1, dparam)
    @endcode

    construct the modified givens transformation matrix h which zeros
    the second component of the colon vector  [sqrt(d1)*x1; sqrt(d2)*y1].
    with dparam(1)=dflag, h has one of the following forms..

      dflag=-1.0    dflag=0.0     dflag=1.0     dflag=-2.0

      (h11  h12)    (1.0  h12)    (h11  1.0)    (1.0  0.0)
    h=(        )    (        )    (        )    (        )
      (h21  h22),   (h21  1.0),   (-1.0 h22),   (0.0  1.0).
    locations 2-5 of dparam contain h11, h21, h12, and h22
    respectively. (values of 1.0, -1.0, or 0.0 implied by the
    value of dparam(1) are not stored in dparam.)

    [  h11 h12 ]  [ a ] = [ r ]
    [  h21 h22 ]  [ b ]   [ 0 ]

    The variables a and b are overwritten by the routine.
    These functors are defined for float and double entries


  @param      d1      floating scalar L-value

               First diagonal element.

               On input, this value is the first diagonal element of the scal-
               ing  matrix D.  On the first call to the routine, this value is
               typically 1.0.  Subsequent calls typically use the  value  from
               the previous call.  On output, this value is the first diagonal
               element of the updated scaling matrix D'.


  @param      d2       floating scalar L-value

               Second diagonal element.

               On input, this is the second diagonal element  of  the  scaling
               matrix D.  On the first call to the routine, this value is typ-
               ically 1.0.  Subsequent calls typically use the value from  the
               previous  call.   On  output, this value is the second diagonal
               element of the updated scaling matrix D'.



   @param      b1      floating scalar L-value

               x-coordinate.

               on input, this value is the x-coordinate of the vector used  to
               define  the  angle  of rotation, before scaling (multiplying by
               the matrix D).  On output, this value is  the  x-coordinate  of
               the  rotated  vector, before scaling (multiplying by the matrix
               D').


    @param     b2       floating scalar

               y-coordinate.

               On input, this value is the y-coordinate of the vector used  to
               define  the  angle  of rotation, before scaling (multiplying by
               the matrix D).  It is unchanged on output.


    @param     rparam  L-value container of  floating of dimension 5

               This array contains rotation matrix information.   The  routine
               sets up the computed elements in rparam from inputs d1, d2, b1,
               and b2.


     @return     Meaning of the Output L-Values:

       The output values are  returned  through  arguments  d1,  d2,  b1,  and
       rparam.

       The  scaling  factors  d1 and d2 are updated with each call to the rou-
       tine.  Although DROTM does not  need  the  updated  factors,  they  are
       needed in two other important contexts:

       As  input for subsequent calls to this routine.  As scaling factors for
       rotated but unscaled points (x(i), y(i)), which are output from  DROTM.

       In  this  second  usage,  the  actual (scaled) points would be given by
       (sqrt(d1)*x(i), sqrt(d2)*y(i)).  Doing this operation frequently on all
       of  your  points is counterproductive.  The main advantage of the modi-
       fied rotation algorithm is to reduce the number of operations.  If  you
       fold in the scaling factors after each rotation, you are performing the
       same number of operations as in the standard Givens rotation.

       These two uses for the scaling factors are mutually exclusive; that is,
       if  you  fold  the  scaling  factors  back into all your points, you no
       longer need those factors for this routine.  After folding in the scal-
       ing  factors,  and  before  the next call to DROTMG, reset d1 and d2 to
       1.0.

       On output, b1 represents  the  new  x-coordinate  after  rotating  (but
       before scaling) the rotation vector.  Although the y-coordinate of this
       vector is 0.0 (see the  the  previous  discussion),  the  corresponding
       value b2 is unchanged on output.

       The  output array argument rparam specifies the format of matrix H, and
       it holds the nonunit values of H.  This is the only output of this rou-
       tine  that DROTM requires.  Each element of rparam has a specific mean-
       ing, as follows:

       rparam(1)  a flag parameter that specifies how the matrix is stored
              0.0 =>  Off-diagonal elements of H are units.

              1.0 =>  Diagonal elements of H are units.

             -1.0 =>  Rescaling case (see the following subsection).

             -2.0 =>  H is the identity matrix; no rotation needed.

         rparam(2)  = h    if needed
                       1,1
         rparam(3)  = h    if needed
                       2,1
         rparam(4)  = h    if needed
                       1,2
         rparam(5)  = h    if needed
                       2,2


  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::rotmg_, rotmg
                                  , (A0&)(A1&)(A2&)(A3&)(A4&)
                                  , 5
                                  );

 } }

#endif

