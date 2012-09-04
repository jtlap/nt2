//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINE_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINE_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_sine sine
 *
 * \par Description
 * templated sine.
 * \par
 * sine is a templated version of cos
 * the template parameter T is a mode that allows some control on the computation
 * accuracy
 * \par
 * In fact the control is on the reduction routine of the angle to the
 * \f$[-\pi/4, \pi/4]\f$ interval
 * they actually are 3 reduction routines protocol that respectly are
 * sufficient for small, medium and big angle values to have within
 * cover test one ulp of difference with the according crlibm result.
 * \par
 * Each one covers respectively intervals \f$[-A, A]\f$ with :
 * \verbatim
 * |--------------|-------------------|----------------|
 * |              |   float  A        |  double  A     |
 * |--------------|-------------------|----------------|
 * |    small     |   20*pi           | 20*pi          |
 * |--------------|-------------------|----------------|
 * |    medium    |   2^6*pi          | 2^18*pi        |
 * |--------------|-------------------|----------------|
 * |    big       |   Inf<float>      |  Inf<double>   |
 * |--------------|------------------------------------|
 * \endverbatim
 * In fact for each scalar singleton or simd vector of angles
 * There are two possibilities :
 * \arg one is to test if all vector element(s) are in the proper range
 * for the consecutive increasing values of A until we reach a good
 * one or the last :
 * the corresponding template tags are small, medium and big
 * \arg the second is to force directly a reduction method
 * The corresponding template tags are direct_small, direct_medium
 * and direct_big
 * \par
 * direct_small is NOT equivalent to small because there are also
 * two other methods for \f$[0, \pi/4]\f$ (no reduction)
 * and \f$[\pi/4, \pi/2]\f$
 * (straight reduction) that are not considered in direct small
 * \par
 * Note that for float the big case is both early an hyper costly and
 * shall be avoided whenever possible. To partially achieve this aim
 * when double are available on the platform, this part of reduction
 * is delegated to the double precision routines.
 * \par Advices
 * \arg If there is no restrictions ever on your angles and you care for precision
 * use nt2::sine<big> which is equivalent to nt2::cos
 * \arg if you do not care for precision you can use
 * nt2::sine<medium> or nt2::sine<small_>
 * that will be accurate for their proper range and degrade
 * with greater values
 * \par
 * Now, the choice of direct or not relies on probabilities
 * computations:
 * assuming that a vector contains k elements and that testing all
 * values that are in an interval takes c cycles and the probability of a value
 * to be in interval \f$[a, b]\f$ is \f$p(a, b)\f$
 * the number of cycles used by a
 * \f$direct_i\f$ method is simply the reduction time:
 * \f[N(direct_i)\f]
 * On the other side the number of cycles for the non-direct methods will have a more
 * complicated expression :
 * \f[\sum_{i=1}^{m} p(Ai-1, A_i)^k N(direct_i)\f]
 * So the non direct methods will be interesting only if you want accurate
 * results everywhere and have anyhow a big proportion of small angles.
 * This is even more true (if possible) in simd and the more k is big, because
 * of the kth power
 * \parFor instance in the medium float case:
 * \arg  if angles are equidistributed  on \f$[0 2^16*\pi]\f$,
 * the \f$p(0, 20*\pi)\f$ will be
 * less than \f$2^11\f$ and thus in sse2 there will be 1 quadruple over
 * 1.76e+13 falling in the small case...
 * Even sorting will do no good because the sort cost will be against 
 * the ratio of 1 successful quadruplet over 2048.
 * \arg  Contrarily if your angles have a gaussian distribution with 0 mean and
 * \f$10\pi\f$ standard deviation,  80% of the intervals will be in the "small"
 * case (95% of the values).
 * \arg Finally for those that are sure of their angles taking place in a fixed
 * range and want speed, three other template tags can be of choice:
 *             clipped_pio4,  clipped_small and clipped_medium
 * they use the fastest adapted reduction and return Nan for any outsider.
 * sine<clipped_pio4> have a perhaps still faster equivalent the non template
 * nt2::fast_sin. 
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/sine.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class T,class A0>
 *     meta::call<tag::sine_(A0)>::type
 *     sine(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sine
 * 
 * \param T template parameter of sine, used to control accuracy and speed
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

//////////////////////////////////////////////////////////////////////////////
/*

  sine if a templated version of sin
  the template parameter "mode" allows some control on the computation
  accuracy
  In fact the control is on the reduction routine of the angle to the
  [-pi/4, pi/4] interval
  they actually are 3 reduction routines protocol that respectly are
  sufficient for small, medium and big angle values to have within
  cover test one ulp of difference with the according crlibm result.

  Each one covers respectively intervals [-A, A] with :

  ****************************************************
  *              *   float  A        * double  A     *
  ****************************************************
  *    small     *   20*pi           * 20*pi         *
  ****************************************************
  *    medium    *   2^6*pi          * 2^18*pi       *
  ****************************************************
  *    big       *   Inf<float>      * Inf<double>   *
  ****************************************************

  In fact for each scalar singleton or simd vector of angles
  There are two possibilities :

    1) is to test if all vector element(s) are in the proper range
    for the consecutive increasing values of A until we reach a good
    one or the last :

      The corresponding template tags are

                      small, medium and big

    2) is to force directly a reduction method

    The corresponding template tags are

              direct_small, direct_medium and direct_big

    direct_small is NOT equivalent to small because there are also
    to other methods for [0 pi/4] (no reduction) and [pi/4, pi/2]
    (straight reduction) that are not considered in direct small

    Note for float the big case if both early an hyper sintly and
    shall be avoided whenever possible. To partially achieve this aim
    when double are available on the platform, this part of reduction
    is delegated to the double precision routines.

    Advices are :

    If there is no restrictions ever on your angles and you care for precision
    use
		                  nt2::sine<big>
    which is equivalent to nt2::sin

    if you d'ont care for precision you can use
                nt2::sine<medium> or sine::nt2<small_>

    they will be accurate for their proper range and degrade (or not)
    with greater values (even can return nan)

    After that the choice of direct or not  relies on probabilities
    computations:
    assuming that a vector contains k elements and that testing all
    values are in an interval takes c cycles and the probability of a value
    to be in interval [a, b] is p(a, b) the number of cycles used by a
    direct_i method is simply the reduction time 

                  N(direct_i)

    On the other side the number of cycles for the xxx method will have a more
    complicated expression :

             sum        ( p(Ai-1, A_i)^k N(direct_i)
               i = 1:m  

    So the non direct methods will be interesting only if you want accurate
    results everywhere and have anyhow a big proportion of small angles.
    This i even truer (if possible) in simd and the more k is big, because
    of the k power

    For instance in the medium float case:
       if angles are equidistributed  on [0 2^16*pi],  the p(0, 20*pi) will be
       less than 2^11 and thus in sse2 there will be 1 quadruple over
       1.759218604441600e+13 falling in the small case...
       Even sorting will do no good because the sort sint will be against 
       s1 over 2048 successful quadruplets

       Contrarily if your angles have a gaussian distribution with 0 mean and
       10*pi standard deviation,  80% of the intervals will be in the small
       case (95% of the values).

    Finally for those that are sure of their angles taking place in a fixed
    range and want speed,  they can use three other template tags

                 clipped_pio4,  clipped_small and clipped_medium

    that use the fastest adapted reduction and return Nan for any outsider.
    sine<clipped_pio4> have a perhaps faster equivalent fast_sin. 
*/
//////////////////////////////////////////////////////////////////////////////

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag sine_ of functor sine 
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    template <class T> struct sine_ : ext::elementwise_< sine_<T> > { typedef ext::elementwise_< sine_<T> > parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sine_<A0> , sine, (A1 const&), 2)
}

#endif

// modified by jt the 25/12/2010
