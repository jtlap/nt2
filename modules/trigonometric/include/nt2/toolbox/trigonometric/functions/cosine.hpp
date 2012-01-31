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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COSINE_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COSINE_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_cosine cosine
 *
 * \par Description
 * templated cosine.
 * \par
 * cosine is a templated version of cos
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
 * use nt2::cosine<big> which is equivalent to nt2::cos
 * \arg if you do not care for precision you can use
 * nt2::cosine<medium> or nt2::cosine<small>
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
 * cosine<clipped_pio4> have a perhaps still faster equivalent the non template
 * nt2::fast_cos. 
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/cosine.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class T,class A0>
 *     meta::call<tag::cosine_(A0)>::type
 *     cosine(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of cosine
 * 
 * \param T template parameter of cosine, used to control accuracy and speed
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag cosine_ of functor cosine 
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    template <class T> struct cosine_ : ext::elementwise_< cosine_<T> > {};
  }

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cosine_<A0> , cosine, (A1 const&), 2)
}

#endif

// modified by jt the 25/12/2010
