//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_SORT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_SORT_HPP_INCLUDED

#include <nt2/core/functions/sort.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/table.hpp>
#include <algorithm>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <string>
#include <iostream>


namespace nt2 { namespace ext
{
  //============================================================================
  // This version of sort is called whenever a tie(...) = sort(...) is captured
  // before assign is resolved. As a tieable function, sort retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sort_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::sort_, N0>))
                              ((node_<A1, nt2::tag::tie_ , N1>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::strip<child0>::type                        st_child0; 
    typedef typename st_child0::value_type                           value_type;
    typedef typename st_child0::index_type                           index_type;
    typedef table<value_type,index_type>                                  res_t;
   
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy data in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      //     std::cout << display_type<ct>() << std::endl;
      size_t dim = 1; 
      bool up = true;
      //retrieve options
      choice(a0, up, dim, N0());
      // compute the sorted result
      compute(a0, a1, up,  dim, N0(), N1());
    }

  private:
    BOOST_FORCEINLINE void
    choice(A0 const &, bool& up, size_t & dim, boost::mpl::long_<1> const &) const
    {
      up = true;  dim = 1; 
    }

    BOOST_FORCEINLINE void 
    choice(A0 const & a0, bool& up, size_t & dim, boost::mpl::long_<2> const &) const
    {
      
      check(boost::proto::value(boost::proto::child_c<1>(a0)), up, dim); 
    }
    
    BOOST_FORCEINLINE void
    choice(A0 const & a0, bool& up, size_t & dim, boost::mpl::long_<3> const &) const
    {
      const char mode = boost::proto::value(boost::proto::child_c<2>(a0)); 
//       BOOST_ASSERT_MSG( std::strcmp("descend", mode) == 0 || std::strcmp("ascend", mode) == 0,
//                         "sorting direction must be 'ascend' or 'descend'"); 
      up = mode == 'a';
      dim = boost::proto::value(boost::proto::child_c<1>(a0)); 
    }
    
    //==============================================================================================
    // checking ascend or descend or dim
    // according to the type of boost::proto::value(boost::proto::child_c<1>(a0))
    // const char * or size_t
    //==============================================================================================
    BOOST_FORCEINLINE  void
    check(const char  mode, bool& up, size_t & dim) const
    {
//       BOOST_ASSERT_MSG( std::strcmp("descend", mode) == 0 || std::strcmp("ascend", mode) == 0,
//                         "sorting direction must be 'ascend' or 'descend'"); 
      std::cout << "check char " << mode << std::endl; 
      up = mode == 'a';
      dim = 1; 
    }
    
    BOOST_FORCEINLINE void
    check(const char * mode, bool& up, size_t & dim) const
    {
//       BOOST_ASSERT_MSG( std::strcmp("descend", mode) == 0 || std::strcmp("ascend", mode) == 0,
//                         "sorting direction must be 'ascend' or 'descend'"); 
      std::cout << "check char *" << mode << std::endl; 
      up = mode[0] == 'a';
      dim = 1; 
    }
    
    BOOST_FORCEINLINE  void
    check(const size_t d, bool& up, size_t & dim) const
    {
      std::cout << "check size_t " << d << std::endl; 
      up = true;
      dim = d; 
    }

    //==============================================================================================
    // computing the sorted array
    //==============================================================================================
    BOOST_FORCEINLINE
    void compute(A0 const&, A1 & a1, bool, size_t, boost::mpl::long_<1> const&, boost::mpl::long_<1> const&) const
    {
      // no options  -> up =  true,  dim = 1; 
      dosort(boost::proto::child_c<0>(a1)); 
    }
    
    BOOST_FORCEINLINE
    void compute(A0 const&, A1 & a1, bool up, size_t dim, boost::mpl::long_<2> const&, boost::mpl::long_<1> const&) const
    {
      dosort(boost::proto::child_c<0>(a1), up, dim);
    }
    
    BOOST_FORCEINLINE
    void compute(A0 const&, A1 & a1, bool up, size_t dim, boost::mpl::long_<3> const&, boost::mpl::long_<1> const&) const
    {
      dosort(boost::proto::child_c<0>(a1), up, dim);
    }
    static bool sort_up (value_type i,value_type j) { return (i<j); }
    static bool sort_dn (value_type i,value_type j) { return (i>j); }
    template <class T> BOOST_FORCEINLINE
      void dosort(T & res,  bool up = true, size_t dim = 1) const
    {
      
      std::cout << "up = " << up << "  dim = " << dim << std::endl; 
      //only dim = 1 is written up to now
      size_t h = nt2::size(res, dim);
      if (h <= 1) return; 
      int nbcol =  numel(res)/h; //TODO perhaps write nslice or/and nbcols
      value_type* beg = res.raw(); 
      value_type* fin = beg+h;                 
      for(int i=0; i < nbcol; i++)
        {
          std::sort(beg, fin, up?&sort_up:&sort_dn);
          beg = fin; fin+= h; 
        }
    }
  };
} }

#endif
