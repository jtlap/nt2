//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_STORAGE_DURATION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_STORAGE_DURATION_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/container/memory/array_buffer.hpp>
#include <nt2/core/container/memory/buffer.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/padding.hpp>
#include <nt2/core/settings/allocator.hpp>

namespace nt2 
{ 
  //============================================================================
   /*! Default storage duration settings. Current container will use dynamic 
    *  allocation for handling its data.
   **/
  //============================================================================
  struct dynamic_{

    template <typename Type, typename Settings, typename Default = void>
    struct apply
    {
      typedef typename meta::option<Settings, tag::allocator_, Default>::type  allocator_type;
      typedef memory::buffer<Type, typename allocator_type::type >    type;
    };  

  };

  //============================================================================
   /*! Current container will use a stack allocated memory block for handling 
    *  its data
   **/
  //============================================================================
  struct automatic_{
    template <typename Type, typename Settings, typename Default = void>
    struct apply
    {

    };  
  };


}



#endif
