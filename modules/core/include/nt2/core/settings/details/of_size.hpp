//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_OF_SIZE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_OF_SIZE_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/at.hpp>
#include <boost/mpl/vector_c.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/meta/align_on.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  //============================================================================
  /*! of_size_<D0,..,Dn> is a size value containing up to n dimensions.
   **/
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS ( NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  struct of_size_
  {
    //==========================================================================
    // Count non-trivial size values
    //==========================================================================
    #define M0(z,n,t) + ((BOOST_PP_CAT(D,n) > -2) ? 1 : 0)
    static const std::size_t 
    static_size = ((D0 > -2) ? 1 : 0)
                  BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_DIMENSIONS,M0,~);
    #undef M0

    //==========================================================================
    // The inner data is aligned and padded so SIMD operations are enabled on
    // size values.
    //==========================================================================
    static const std::size_t 
    stored_size = nt2::meta::align_on_c < sizeof(std::ptrdiff_t) * static_size
                                        >::value / sizeof(std::ptrdiff_t);    

    //==========================================================================
    // Static size values used internally by MPL/Fusion
    //==========================================================================
    typedef boost::mpl::
            vector_c< std::ptrdiff_t
                    , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)
                    >                                               values_type;

    //==========================================================================
    // Size values storage
    //==========================================================================
    NT2_ALIGNED_TYPE(std::ptrdiff_t) data_[stored_size];

    //==========================================================================
    // Default constructor either generate [0 1 .. 1] or [D0 ... Dn]
    //==========================================================================
    of_size_()
    {
      data_[0] = (D0 < 0 ) ? 0 : D0;
      default_(boost::mpl::size_t<static_size-1>());
    }

    std::ptrdiff_t& operator[](std::size_t i)       { return data_[i]; }
    std::ptrdiff_t  operator[](std::size_t i) const { return data_[i]; }

    static std::size_t size() { return static_size; }
    
    private:

    template<std::size_t N> inline void default_(boost::mpl::size_t<N> const&)
    {
      typedef typename boost::mpl::at_c<values_type,N>::type value;
      data_[N] = (value::value < 0) ? 1 : value::value;
      default_(boost::mpl::size_t<N-1>());
    }

    inline void default_(boost::mpl::size_t<0> const&) {}
  };

  //============================================================================
  // Defines some usual short-cuts for runtime of_size_
  //============================================================================
  #define M1(z,n,t) t
  #define M0(z,n,t)                                                           \
  typedef of_size_<BOOST_PP_ENUM(n,M1,-1)> BOOST_PP_CAT(BOOST_PP_CAT(_,n),D); \
  /**/

  BOOST_PP_REPEAT_FROM_TO(0,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

  #undef M0
  #undef M1
}

#endif
