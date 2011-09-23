//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_COMPOSITE_BUFFER_HPP
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_COMPOSITE_BUFFER_HPP

#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include <nt2/core/container/meta/reference.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace memory
{
  template< typename Buffer > struct composite_buffer;
  
  template<std::size_t Level, typename Buffer, typename Position>
  inline typename meta::dereference_<Buffer&,Level>::type 
  dereference( Buffer& b, Position const& p );

  template<std::size_t Level, typename Buffer, typename Position>
  inline typename meta::dereference_<Buffer const& ,Level>::type 
  dereference( Buffer const& b, Position const& p );
} }

//==============================================================================
// Fill out the Buffer concepts
//==============================================================================
namespace nt2 { namespace meta
{  
  template<typename B>
  struct  dimensions_of< memory::composite_buffer<B> >
        : dimensions_of< B >
  {};

  //============================================================================
  // dereference_ specialization
  //============================================================================
  template<typename B, std::size_t Level>
  struct dereference_<memory::composite_buffer<B>&,Level>
  {
    struct local
    {
      template<class T> struct apply
      {
        typedef typename dereference_<T&,Level>::type type;
      };
    };

    typedef typename boost::mpl::
            transform < typename memory::composite_buffer<B>::data_type
                      , local
                      >::type                                             type;
  };

  template<typename B, std::size_t Level>
  struct dereference_<memory::composite_buffer<B> const&,Level>
  {
    struct local
    {
      template<class T> struct apply
      {
        typedef typename dereference_<T const&,Level>::type type;
      };
    };

    typedef typename boost::mpl::
            transform < typename memory::composite_buffer<B>::data_type
                      , local
                      >::type                                             type;
  };
} }

namespace nt2 { namespace details
{
  template<class Position, std::size_t Level>
  struct deref_
  {
    deref_( Position const& p) : pos(p) {}
    Position const& pos;
    
    template<class Sig> struct result;
    
    template<class This,class Elem>
    struct result<This(Elem const&)>        
    {
      typedef typename meta::dereference_<Elem const&,Level>::type type;
    };

    template<class This,class Elem>
    struct result<This(Elem&)>        
    {
      typedef typename meta::dereference_<Elem&,Level>::type type;
    };

    template<class Element>
    inline typename result<deref_(Element const&)>::type 
    operator()(Element const& t) const
    {
      return memory::dereference<Level>(t,pos);
    };

    template<class Element>
    inline typename result<deref_(Element&)>::type 
    operator()(Element& t) const
    {
      return memory::dereference<Level>(t,pos);
    };    
  };

  //============================================================================
  // Recursively apply [] on the buffer
  //============================================================================
  template<typename B, std::size_t Level>
  struct dereference< memory::composite_buffer<B>, Level>
  {
    template<typename Position>
    static inline typename 
    meta::dereference_<memory::composite_buffer<B>&,Level>::type 
    apply( memory::composite_buffer<B>& b, Position const& p )
    {
      typedef deref_<Position,Level> functor_type;
      typedef typename memory::composite_buffer<B>::data_type data_type;
      
      return  boost::fusion::
              transform_view< data_type
                            , functor_type
                            >(b.data_, functor_type(p));
    }

    template<typename Position>
    static inline typename 
    meta::dereference_<memory::composite_buffer<B> const&,Level>::type 
    apply( memory::composite_buffer<B> const& b, Position const& p )
    {
      typedef deref_<Position,Level> functor_type;
      typedef typename memory::composite_buffer<B>::data_type data_type;
      
      return  boost::fusion::
              transform_view< data_type const
                            , functor_type
                            >(b.data_, functor_type(p));
    }
  };
  
  template<typename B>
  struct dereference< memory::composite_buffer<B>, 1>
  {
    template<typename Position>
    static inline typename 
    meta::dereference_<memory::composite_buffer<B>&,1>::type 
    apply( memory::composite_buffer<B>& b, Position const& p )
    {
      typedef deref_<Position,1> functor_type;
      typedef typename memory::composite_buffer<B>::data_type data_type;
      
      return  boost::fusion::
              transform_view< data_type
                            , functor_type
                            >(b.data_, functor_type(p));
    }

    template<typename Position>
    static inline typename 
    meta::dereference_<memory::composite_buffer<B> const&,1>::type 
    apply( memory::composite_buffer<B> const& b, Position const& p )
    {
      typedef deref_<Position,1> functor_type;
      typedef typename memory::composite_buffer<B>::data_type data_type;
      
      return  boost::fusion::
              transform_view< data_type const
                            , functor_type
                            >(b.data_, functor_type(p));
    }
  };  
} }

namespace nt2 { namespace memory
{
  //============================================================================
  // composite_buffer initialize - Part of Buffer Concept
  //============================================================================
  template<typename B, typename Sizes, typename Bases,typename Padding>
  inline void initialize( composite_buffer<B>& v
                        , Sizes const& s, Bases const& b, Padding const& p
                        )
  {
    v.initialize(s,b,p);
  }

  //============================================================================
  // composite_buffer share - Part of SharingBuffer Concept
  //============================================================================
  template< typename B
          , typename Sizes, typename Bases
          , typename Padding, typename Target
          >
  inline void share( composite_buffer<B>& v
                   , Sizes const& s, Bases const& b, Padding const& p
                   , Target const& t
                   )
  {
    v.initialize(s,b,p,t);
  }
} }

#endif
