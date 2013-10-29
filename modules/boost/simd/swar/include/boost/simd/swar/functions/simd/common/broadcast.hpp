//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_BROADCAST_HPP_INCLUDED

#include <boost/simd/swar/functions/broadcast.hpp>
#include <boost/simd/include/functions/simd/shuffle.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::simd_
                                    , (A0)(X)(A1)
                                    , ((simd_< unspecified_<A0>, X >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    struct bcast_
    {
      template<typename Index, typename Cardinal>
      struct apply
      {
        typedef boost::mpl::int_<A1::value> type;
      };
    };

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return shuffle<bcast_>(a0);
    }
  };
} } }

#endif
