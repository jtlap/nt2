//==============================================================================
//         Copyright 2015 - J.T. Lapreste
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_ROUND_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_ROUND_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/round.hpp>
#include <boost/simd/include/functions/simd/tenpower.hpp>
#include <boost/simd/include/functions/simd/copysign.hpp>
#include <boost/simd/include/functions/simd/seldec.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/functions/simd/ceil.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT          ( round_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<integer_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( round_, boost::simd::tag::simd_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type absa0 = boost::simd::abs(a0);
      result_type c =  boost::simd::ceil(absa0);
      return copysign(seldec(gt(c-Half<result_type>(), absa0), c), a0);
    }
  };

  BOOST_DISPATCH_IMPLEMENT          ( round_, boost::simd::tag::simd_
                                    , (A0)(X)(A1)
                                    , ((simd_< floating_<A0>,X>))
                                      ((simd_< integer_<A1>,X>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      A0 fac = tenpower(a1);
      return round(a0*fac)/fac;
    }
  };

} } }

#endif
