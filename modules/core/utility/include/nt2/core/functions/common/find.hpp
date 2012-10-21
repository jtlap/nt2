//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_FIND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_FIND_HPP_INCLUDED

#include <nt2/core/functions/find.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <nt2/include/functions/findi.hpp>
#include <nt2/include/functions/findj.hpp>
#include <nt2/include/functions/globalfind.hpp>
#include <nt2/include/functions/tie.hpp>
#include <boost/fusion/include/make_vector.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::find_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::find_, N0>))
                                ((node_<A1, nt2::tag::tie_ , N1>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type       child0;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child1;
    typedef typename boost::dispatch::meta::
      terminal_of< typename boost::dispatch::meta::
      semantic_of<child0>::type
      >::type                                            in0_t;
    typedef typename in0_t::value_type              value_type;
    typedef typename boost::dispatch::meta::
      terminal_of< typename boost::dispatch::meta::
      semantic_of<child1>::type
      >::type                                            out_t;
    typedef typename out_t::value_type              index_type;
    typedef typename boost::dispatch::meta::as_integer<value_type, unsigned>::type  idx_t;      

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      bool    first =  true;
      ptrdiff_t k = 0;
      getparams(a0, first, k, N0());
      compute(a0, a1, first, k, N1()); 
    }
  private :

    BOOST_FORCEINLINE  //    i = find(x, ...)
      void compute(A0 const &a0, A1 & a1, bool& first, ptrdiff_t& k, 
                     boost::mpl::long_<1> const &//number of outputs
                     ) const
    {
       child1& idx = boost::proto::child_c<0>(a1);
       child0& a = boost::proto::child_c<0>(a0);
       idx.resize(of_size(0, 1)); 
       std::size_t m = nt2::numel(a);
       if(k)
         {
           ptrdiff_t z = 0;
           if(first)
             {
               for(std::size_t i=0; i!=m; ++i)
                 {
                   value_type value = nt2::run(a, i, meta::as_<value_type>());
                   if(value)
                     {
                       boost::proto::value(idx).push_back(index_type(i+1));
                       ++z;
                       if(z == k) break; 
                     }
                 }
             }
           else
             {
               for(std::size_t i=m-1; i!=0; --i)
                 {
                   value_type value = nt2::run(a, i, meta::as_<value_type>());
                   if(value)
                     {
                       boost::proto::value(idx).push_back(index_type(i+1));
                       ++z;
                       if(z == k) break; 
                     }
                 }
             }
         }
       else if(first)
         {
           for(std::size_t i=0; i!=m; ++i)
             {
               value_type value = nt2::run(a, i, meta::as_<value_type>());
               if(value)
                 boost::proto::value(idx).push_back(index_type(i+1));
             }
         }
       else
         {
           for(std::size_t i=m-1; i!=0; --i)
             {
               value_type value = nt2::run(a, i, meta::as_<value_type>());
               if(value)
                 boost::proto::value(idx).push_back(index_type(i+1));
             }
         }
    }

    BOOST_FORCEINLINE  //    [i, j]= find(x)
      void compute(A0 const &a0, A1 & a1, bool& first, ptrdiff_t& k, 
                     boost::mpl::long_<2> const &//number of outputs
                     ) const
    {
       child1& idx = boost::proto::child_c<0>(a1);
       child1& jdx = boost::proto::child_c<1>(a1);
       child0& a = boost::proto::child_c<0>(a0);
       idx.resize(of_size(0, 1));
       jdx.resize(of_size(0, 1));
       std::size_t t = nt2::numel(a);
       std::size_t m = nt2::size(a, 1);
       std::size_t n = t/m; 
       if(k)
         {
           ptrdiff_t z = 0;
           if(first)
             {
               for(std::size_t i=0; i!=t; ++i)
                 {
                   value_type value = nt2::run(a, i, meta::as_<value_type>());
                   if(value)
                     {
                       boost::array<idx_t, 2> a = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
                       boost::proto::value(idx).push_back(index_type(a[1]+1));
                       boost::proto::value(jdx).push_back(index_type(a[0]+1));
                       ++z;
                       if(z == k) break; 
                     }
                 }
             }
           else
             {
               for(std::size_t i=t-1; i!=0; --i)
                 {
                   value_type value = nt2::run(a, i, meta::as_<value_type>());
                   if(value)
                     {
                       boost::array<idx_t, 2> a = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
                       boost::proto::value(idx).push_back(index_type(a[1]+1));
                       boost::proto::value(jdx).push_back(index_type(a[0]+1));
                       ++z;
                       if(z == k) break; 
                     }
                 }
             }
         }
       else if(first)
         {
           for(std::size_t i=0; i!=t; ++i)
             {
               value_type value = nt2::run(a, i, meta::as_<value_type>());
               if(value)
                 {
                   boost::array<idx_t, 2> a = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
                   boost::proto::value(idx).push_back(index_type(a[1]+1));
                   boost::proto::value(jdx).push_back(index_type(a[0]+1));
                 }
             }
         }
       else
         {
           for(std::size_t i=t-1; i!=0; --i)
             {
               value_type value = nt2::run(a, i, meta::as_<value_type>());
               if(value)
                 {
                   boost::array<idx_t, 2> a = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
                   boost::proto::value(idx).push_back(index_type(a[1]+1));
                   boost::proto::value(jdx).push_back(index_type(a[0]+1));
                 }
             }
         }
    }


    BOOST_FORCEINLINE  //    [i, j]= find(x)
      void compute(A0 const &a0, A1 & a1, bool& first, ptrdiff_t& k, 
                   boost::mpl::long_<3> const &//number of outputs
                   ) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,1>::type       child2;
      typedef typename boost::proto::result_of::child_c<A1&,2>::type       child3;
      child1& idx = boost::proto::child_c<0>(a1);
      child2& jdx = boost::proto::child_c<1>(a1);
      child3& v = boost::proto::child_c<2>(a1); 
      child0& a = boost::proto::child_c<0>(a0);
      idx.resize(of_size(0, 1));
      jdx.resize(of_size(0, 1));
      v.resize(of_size(0, 1));
      std::size_t t = nt2::numel(a);
      std::size_t m = nt2::size(a, 1);
      std::size_t n = t/m; 
      if(k)
        {
          ptrdiff_t z = 0;
          if(first)
            {
              for(std::size_t i=0; i!=t; ++i)
                {
                  value_type value = nt2::run(a, i, meta::as_<value_type>());
                  if(value)
                    {
                      boost::array<idx_t, 2> a = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
                      boost::proto::value(idx).push_back(index_type(a[1]+1));
                      boost::proto::value(jdx).push_back(index_type(a[0]+1));
                      boost::proto::value(v  ).push_back(value); 
                      ++z;
                      if(z == k) break; 
                    }
                }
            }
          else
            {
              for(std::size_t i=t-1; i!=0; --i)
                {
                  value_type value = nt2::run(a, i, meta::as_<value_type>());
                  if(value)
                    {
                      boost::array<idx_t, 2> a = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
                      boost::proto::value(idx).push_back(index_type(a[1]+1));
                      boost::proto::value(jdx).push_back(index_type(a[0]+1));
                      boost::proto::value(v  ).push_back(value); 
                     ++z;
                      if(z == k) break; 
                    }
                }
            }
        }
      else if(first)
        {
          for(std::size_t i=0; i!=t; ++i)
            {
              value_type value = nt2::run(a, i, meta::as_<value_type>());
              if(value)
                {
                  boost::array<idx_t, 2> a = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
                  boost::proto::value(idx).push_back(index_type(a[1]+1));
                  boost::proto::value(jdx).push_back(index_type(a[0]+1));
                  boost::proto::value(v  ).push_back(value); 
                }
            }
        }
      else
        {
          for(std::size_t i=t-1; i!=0; --i)
            {
              value_type value = nt2::run(a, i, meta::as_<value_type>());
              if(value)
                {
                  boost::array<idx_t, 2> a = nt2::as_subscript(boost::fusion:: make_vector(idx_t(m),idx_t(n)), idx_t(i) );
                  boost::proto::value(idx).push_back(index_type(a[1]+1));
                  boost::proto::value(jdx).push_back(index_type(a[0]+1));
                  boost::proto::value(v  ).push_back(value); 
                }
            }
        }
    }
    
    BOOST_FORCEINLINE  //    i = find(x)
      void getparams(A0 const &a0, bool&, ptrdiff_t& , 
                     boost::mpl::long_<1> const &//number of inputs
                     ) const
    { }
    BOOST_FORCEINLINE  //    i = find(x, 'f') or i = find(x, 'l') or  i = find(x, k)
      void getparams(A0 const &a0, bool& first, ptrdiff_t& k, 
                     boost::mpl::long_<2> const &//number of inputs
                     ) const
    {
      get(a0, boost::proto::value(boost::proto::child_c<1>(a0)), first, k); 
    }
    BOOST_FORCEINLINE  //    i = find(x, 'f') or i = find(x, 'l') or  i = find(x, k)
      void getparams(A0 const &a0, bool& first, ptrdiff_t& k, 
                     boost::mpl::long_<3> const &//number of inputs
                     ) const
    {
      first = boost::proto::value(boost::proto::child_c<1>(a0));
      k = boost::proto::value(boost::proto::child_c<2>(a0));
      BOOST_ASSERT_MSG(k > 0, "Second parameter must be greater than 0"); 
    }

    
    BOOST_FORCEINLINE  
      void get(A0 const &a0, const bool &dir, bool& first, ptrdiff_t& )const
    {
      first = dir; 
    }
    template < class T > 
    BOOST_FORCEINLINE  
      void get(A0 const &a0, const T &nb, bool&, ptrdiff_t& k )const
    {
      BOOST_ASSERT_MSG(nb > 0, "Second parameter must be greater than 0"); 
      k = nb; 
    }

  }; 
} }

#endif
