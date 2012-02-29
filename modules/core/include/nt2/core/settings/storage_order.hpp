//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_STORAGE_ORDER_HPP_INCLUDED
#define NT2_CORE_SETTINGS_STORAGE_ORDER_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/forward/storage_order.hpp>

namespace nt2 
{ 
  namespace meta
  {
    template<class SO, class Default>
    struct option < storage_order_<SO>
                  , tag::storage_order_, Default
                  >
    {    
       typedef storage_order_<SO>  type;
    };
  }

}


#endif
