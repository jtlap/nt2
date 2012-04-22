//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_ISINSIDE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ISINSIDE_HPP_INCLUDED

#include <nt2/core/functions/isinside.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/zip_view.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isinside_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                              (fusion_sequence_<A2>)
                            )
  {
    ////TODO: Make isinside SIMD proof
    ////typedef typename boost::fusion::result_of::at_c<A0,0>::type at_t;
    ////typedef typename meta::strip<at_t>::type                    base_t;
    typedef bool                                                result_type;

    struct is_in
    {
      typedef bool result_type  ;
      template<typename T> bool operator()(bool res, const T& t) const
      {
        return res  &&  ( boost::fusion::at_c<0>(t) >= boost::fusion::at_c<2>(t)  )
                    &&  ( boost::fusion::at_c<0>(t) < boost::fusion::at_c<1>(t)
                                                    + boost::fusion::at_c<2>(t)
                        );
      }
    };

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0,const A1& a1,const A2& a2) const
    {
      typedef boost::fusion::vector<A0&,A1&,A2&> seq_t;

      return boost::fusion::fold( boost::fusion::zip_view<seq_t>(seq_t(a0,a1,a2))
                                , true
                                , is_in()
                                );
    }
  };
} }

#endif
