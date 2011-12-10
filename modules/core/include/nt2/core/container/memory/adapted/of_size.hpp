//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_OF_SIZE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_OF_SIZE_HPP_INCLUDED

#include <boost/mpl/size.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  // of_size are dereferencable
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)
          , typename Position
          >
  typename of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)>::reference
  dereference ( of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)>& b
              , Position const& pos
              )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value <= 2)
                    , POSITION_SIZE_MISMATCH_IN_OF_SIZE_ACCESS
                    , (Position)
                    );
                    
    return b[boost::fusion::at_c<boost::mpl::size<Position>::value-1>(pos)];
  }
  
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)
          , typename Position
          >
  typename of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)>::const_reference
  dereference ( of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)> const& b
              , Position const& pos
              )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value <= 2)
                    , POSITION_SIZE_MISMATCH_IN_OF_SIZE_ACCESS
                    , (Position)
                    );
                    
    return b[boost::fusion::at_c<boost::mpl::size<Position>::value-1>(pos)];
  }
} } 

namespace nt2 { namespace meta
{
  //============================================================================
  // dimensions_of specialization
  //============================================================================
  template<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)>
  struct  dimensions_of< of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)> >
        : boost::mpl::size_t<2>
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)>
  struct value_of< nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)> >
  {
    typedef typename
    nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)>::value_type type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)>
  struct model_of< nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)> type;
      };
    };
  };
} } }

#endif
