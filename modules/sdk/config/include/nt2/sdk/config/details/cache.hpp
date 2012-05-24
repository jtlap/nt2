//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONFIG_DETAILS_CACHE_CACHE_HPP_INCLUDED
#define NT2_SDK_CONFIG_DETAILS_CACHE_CACHE_HPP_INCLUDED

#include <boost/array.hpp>
#include <nt2/sdk/config/details/detect_cache.hpp>

namespace nt2{ namespace config{ namespace details{

  inline
  boost::array< boost::array<int, NT2_MAX_CACHE_LEVEL>
              , 2
              >& init_cache()
  {
    typedef boost::array<int, NT2_MAX_CACHE_LEVEL> vector_type;
    static  boost::array<vector_type, 2> cache_infos;
    static  bool is_init = false;
    if(!is_init)
    {
      for(int i = 0; i < NT2_MAX_CACHE_LEVEL; i++)
        cache_infos[0][i] = cache_infos[1][i] = 0;
      details::detect_cache<vector_type>(cache_infos[0], cache_infos[1]);
      is_init = true;
      return cache_infos;
    }
    else return cache_infos;
  }

} } }


#endif
