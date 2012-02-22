//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_ID_HPP_INCLUDED
#define NT2_CORE_SETTINGS_ID_HPP_INCLUDED



#include <boost/cstdint.hpp>
#include <boost/mpl/string.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/forward/id.hpp>


namespace nt2 
{ 

  namespace meta
  {
    //==========================================================================
    // Make options extracting the ID from id_
    //==========================================================================
    template<boost::uint32_t ID, class Default>
    struct option<id_<ID>, tag::id_, Default>
    {
      typedef id_<ID> type;
    };
  } 
}



#endif
