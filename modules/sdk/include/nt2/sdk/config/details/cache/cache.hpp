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

#include <boost/simd/sdk/config/details/get_vendor.hpp>
#include <boost/simd/sdk/config/details/detector/cpuid.hpp>
#include <nt2/sdk/config/details/cache/detect_cache.hpp>
#include <nt2/sdk/config/details/cache/cache_exception.hpp>
#include <nt2/sdk/error/assert.hpp>
#include <nt2/sdk/config/arch.hpp>
#include <boost/array.hpp>
#include <boost/fusion/include/boost_array.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <vector>

namespace nt2{ namespace config{ namespace details{

  struct cache_infos
  {
    typedef int result_type;
    typedef boost::array<int, NT2_MAX_CACHE_LEVEL>                   vector_type;
    typedef boost::fusion::result_of::begin<vector_type>::type begin_iterator;
    typedef boost::fusion::result_of::end<vector_type>::type   end_iterator;

    inline void init() const
    {
      if(!is_init_)
      {
        detect_cache<vector_type>(cache_sizes_, cache_line_sizes_);
        is_init_ = true;
      }
    }

    inline result_type cache_size(int const& level) const
    {
      BOOST_ASSERT_MSG(is_init_ == true, 
                      "The class cache_infos needs to be initialized via the "
                      "function cache_init before accessing its members.");
      if(level > cache_sizes_.size())
        throw cache_exc("This level of cache is not available on the current target.");
      else return cache_sizes_[level-1];
    }

    inline result_type cache_line_size(int const& level) const
    {
      BOOST_ASSERT_MSG(is_init_ == true, 
                      "The class cache_infos needs to be initialized via the "
                      "function cache_init before accessing its members.");
      if(level > cache_line_sizes_.size())
        throw cache_exc("This level of cache is not available on the current target.");
      else return cache_line_sizes_[level-1];
    }

    inline result_type get_max_level() const
    {
      BOOST_ASSERT_MSG(is_init_ == true,
                       "The class cache_infos needs to be initialized via the "
                       "function cache_init before accessing its members.");
      return cache_sizes_.size();
    }

    inline begin_iterator cache_size_begin() const
    {
      BOOST_ASSERT_MSG(is_init_ == true,
                      "The class cache_infos needs to be initialized via the "
                      "function cache_init before accessing its members.");
      begin_iterator it = boost::fusion::begin(cache_sizes_);
      return it;
    }

    inline begin_iterator cache_line_size_begin() const
    {
      BOOST_ASSERT_MSG(is_init_ == true,
                      "The class cache_infos needs to be initialized via the "
                      "function cache_init before accessing its members.");
      begin_iterator it = boost::fusion::begin(cache_line_sizes_);
      return it;
    }

    inline end_iterator cache_size_end() const
    {
      BOOST_ASSERT_MSG(is_init_ == true, 
                      "The class cache_infos needs to be initialized via the "
                      "function cache_init before accessing its members.");
      end_iterator it = boost::fusion::end(cache_sizes_);
      return it;
    }

    inline end_iterator cache_line_size_end() const
    {
      BOOST_ASSERT_MSG(is_init_ == true, 
                      "The class cache_infos needs to be initialized via the "
                      "function cache_init before accessing its members.");
      end_iterator it = boost::fusion::end(cache_line_sizes_);
      return it;
    }

    mutable bool is_init_;
    mutable vector_type cache_sizes_;
    mutable vector_type cache_line_sizes_;

  };

  inline bool cache_init(cache_infos const& c)
  {
    if(!c.is_init_)
    {
      detect_cache<cache_infos::vector_type>(c.cache_sizes_, c.cache_line_sizes_);
      return true;
    }
    else return false;
  }

  const cache_infos detected_cache = { cache_init(detected_cache) };

} } }


#endif /* NT2_SDK_CONFIG_DETAILS_CACHE_CACHE_HPP */
