//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_COSINE_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_COSINE_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/trigonometric/include.hpp>
//////////////////////////////////////////////////////////////////////////////
/*
  cosine if a templated version of cos
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

    Note for float the big case if both early an hyper costly and
    shall be avoided whenever possible. To partially achieve this aim
    when double are available on the platform, this part of reduction
    is delegated to the double precision routines.

    Advices are :

    If there is no restrictions ever on your angles and you care for precision
    use
		                  nt2::cosine<big>
    which is equivalent to nt2::cos

    if you d'ont care for precision you can use
                nt2::cosine<medium> or cosine::nt2<small>

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
       Even sorting will do no good because the sort cost will be against 
       s1 over 2048 successful quadruplets
       
       Contrarily if your angles have a gaussian distribution with 0 mean and
       10*pi standard deviation,  80% of the intervals will be in the "small"
       case (95% of the values).

    Finally for those that are sure of their angles taking place in a fixed
    range and want speed,  they can use three other template tags

                 clipped_pio4,  clipped_small and clipped_medium

    that use the fastest adapted reduction and return Nan for any outsider.
    cose<clipped_pio4> have a perhaps faster equivalent fast_cos. 		  
    
*/
//////////////////////////////////////////////////////////////////////////////
/*
  for float values exhaustive test have been taken. All the values has been
  compared to the call to crlibm with the rounded to nearest cosine function
  provided by the library for double entries. I.E. nt2::cos(a0) is compared
  to float(nt2;::crlibm::cos_rn(double(a0))). The results are the following :
  
  **********************************************************************
  * range      *  nb of values *   0 ulp    *  0.5 ulp  * 1 ulp * 27ulp*
  **********************************************************************
  * [0, pi/4]  *  1061752796   * 1060453284 *  1299512  *   0   *   0  * 
  **********************************************************************
  * [0, 20*pi] *  1115378643   * 1103886629 * 11491888  *  1260 *   0  *
  **********************************************************************
  * [0, 64*pi] *  1128861660   * 1114841922 * 14018389  *  1330 *  19  *
  **********************************************************************
1128861660
for a0 = 64.40264893 error if of 1.5 ulps
for a0 = 83.2522049 error if of 3 ulps
for a0 = 86.39379883 error if of 1.5 ulps
for a0 = 98.96016693 error if of 1.5 ulps
for a0 = 102.1017609 error if of 4.5 ulps
for a0 = 105.2433548 error if of 2.5 ulps
for a0 = 117.8097229 error if of 1.5 ulps
for a0 = 120.9513168 error if of 6 ulps
for a0 = 124.0929108 error if of 3.5 ulps
for a0 = 139.8008728 error if of 8.5 ulps
for a0 = 146.0840607 error if of 1.5 ulps
for a0 = 155.5088348 error if of 2.5 ulps
for a0 = 161.7920227 error if of 3 ulps
for a0 = 168.0752106 error if of 1.5 ulps
for a0 = 171.2167969 error if of 1.5 ulps
for a0 = 177.4999847 error if of 27 ulps
for a0 = 183.7831726 error if of 2 ulps
for a0 = 193.2079468 error if of 4 ulps
for a0 = 199.4911346 error if of 4 ulps

1114841922 values with error less than 0 ulp(s)
14018389 values with error less than 0.5 ulp(s)
1330 values with error less than 1 ulp(s)
7 values with error less than 1.5 ulp(s)
1 values with error less than 2 ulp(s)
2 values with error less than 2.5 ulp(s)
2 values with error less than 3 ulp(s)
1 values with error less than 3.5 ulp(s)
2 values with error less than 4 ulp(s)
1 values with error less than 4.5 ulp(s)
3 values with error bigger than 5 ulp(s)

Other test with cosine<direct_small> on all float values
between 0 and 80.5*pi (that means 1132258802 values)
we have
           1106449463 values equal to crlibm value
             25804651 values at 0.5 ulp
                 4687 values at 1   ulp
		    1 value  at 11  ulps for 80.5*pi



  */ 
//////////////////////////////////////////////////////////////////////////////

namespace nt2 { namespace tag
  {         
    template <class T> struct cosine_ {};
  }

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cosine_<A0> , cosine, (A1 const&), 2)
}
 
 
#endif

// modified by jt the 25/12/2010
