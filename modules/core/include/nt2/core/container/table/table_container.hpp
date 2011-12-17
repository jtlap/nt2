//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_TABLE_TABLE_CONTAINER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_TABLE_TABLE_CONTAINER_HPP_INCLUDED

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/shape.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/container/category.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <nt2/core/container/meta/is_container.hpp>
#include <nt2/core/container/meta/container_of.hpp>
#include <nt2/core/container/meta/make_block.hpp>
#include <nt2/core/container/memory/dense_block.hpp>

namespace nt2 { namespace container
{
  //============================================================================
  /*!
   * table_container is the base class handling a table semantic, layout and
   * memory used by the table proto terminal class. It is built from a value
   * \c Type and a list of \c Settings describing how it should behave both at
   * runtime and compile-time.
   * 
   * Note that contrary to user defined table terminals, table_container only
   * require a few layout related options to be able to build a proper terminal
   * expression. Other layout like static ID are used by table_container to
   * select a proper block implementation but don't make sense when used in
   * larger expressions.
   *
   * \tparam Type Value type to store in the table
   * \tparam Setting Compound options list describing the behavior of the table
   **/
  //============================================================================
  template<class T, class S> struct table_container
  {
    typedef typename meta::option<S, tag::of_size_, _4D>::type          extent_type;
    typedef typename meta::option<S, tag::index_, matlab_index_>::type  index_type;
    typedef typename meta::option<S, tag::storage_order_, matlab_order_>::type  storage_order_type;

    typedef nt2::settings settings_type(index_type,extent_type, storage_order_type, dense_);

    typedef typename make_block<T, settings_type>::type block_type;
    
    BOOST_MPL_ASSERT_MSG( (!boost::is_same<_0D,extent_type>::value)
                        , INVALID_CONTAINER_CONSTRUCTION
                        , (table_container)
                        );
    
    typedef typename block_type::reference        reference;
    typedef typename block_type::const_reference  const_reference;

    template<class Sz>
    void resize( Sz const& sz ) 
    { 
      if(size_ != sz)
      {
        size_ = sz;
        block_.resize(size_); 
      }
    }
        
    //==========================================================================
    // Random Access operators hub - forward to potential 1D specialisation
    //==========================================================================
    template<class Position> BOOST_DISPATCH_FORCE_INLINE
    reference operator()(Position const& pos)
    {
      return access ( pos
                    , boost::mpl::bool_<boost::mpl::size<Position>::value == 1>()
                    , boost::mpl::bool_<extent_type::static_size == 1>()                    
                    );
    }

    template<class Position> BOOST_DISPATCH_FORCE_INLINE
    const_reference operator()(Position const& pos) const
    {
      return access ( pos
                    , boost::mpl::bool_<boost::mpl::size<Position>::value == 1>()
                    , boost::mpl::bool_<extent_type::static_size == 1>()                    
                    );
    }

    index_type          bases()   const { return index_type();  }
    extent_type const&  extent()  const { return size_;         }
    
    block_type&         data()          { return block_;  }    
    block_type const&   data()  const   { return block_;  }

    protected:
    //==========================================================================
    // Random Access target
    //==========================================================================
    template<class Position,class Dims> BOOST_DISPATCH_FORCE_INLINE
    reference access(Position const& pos, boost::mpl::false_ const&, Dims const&)
    {
      return block_(pos);
    }

    template<class Position,class Dims> BOOST_DISPATCH_FORCE_INLINE 
    const_reference 
    access(Position const& pos, boost::mpl::false_ const&, Dims const&)  const
    {
      return block_(pos);
    }
    
    //==========================================================================
    // Random Access target for 1D target on nD table
    //==========================================================================
    template<class Position> BOOST_DISPATCH_FORCE_INLINE
    reference access( Position const& pos
                    , boost::mpl::true_ const&
                    , boost::mpl::false_ const&
                    )
    {
      boost::array<std::ptrdiff_t,2> p;
      p[0]  = ( boost::fusion::at_c<0>(pos) 
              - boost::mpl::at_c<typename index_type::type,0>::type::value
              )
              % boost::fusion::at_c<0>(size_)
              + boost::mpl::at_c<typename index_type::type,0>::type::value;

      p[1]  = ( boost::fusion::at_c<0>(pos) 
              - boost::mpl::at_c<typename index_type::type,0>::type::value
              )
              / boost::fusion::at_c<0>(size_)
              + boost::mpl::at_c<typename index_type::type,1>::type::value;

      return block_(p);
    }

    template<class Position> BOOST_DISPATCH_FORCE_INLINE
    const_reference access( Position const& pos
                          , boost::mpl::true_ const&
                          , boost::mpl::false_ const&
                          ) const
    {
      boost::array<std::ptrdiff_t,2> p;
      p[0]  = ( boost::fusion::at_c<0>(pos) 
              - boost::mpl::at_c<typename index_type::type,0>::type::value
              )
              % boost::fusion::at_c<0>(size_)
              + boost::mpl::at_c<typename index_type::type,0>::type::value;

      p[1]  = ( boost::fusion::at_c<0>(pos) 
              - boost::mpl::at_c<typename index_type::type,0>::type::value
              )
              / boost::fusion::at_c<0>(size_)
              + boost::mpl::at_c<typename index_type::type,1>::type::value;

      return block_(p);
    }

    //==========================================================================
    // Random Access target for 1D target on 1D table
    //==========================================================================
    template<class Position> BOOST_DISPATCH_FORCE_INLINE
    reference access( Position const& pos
                    , boost::mpl::true_ const&
                    , boost::mpl::true_ const&
                    )
    {
      return block_(pos);
    }

    template<class Position> BOOST_DISPATCH_FORCE_INLINE
    const_reference access( Position const& pos
                          , boost::mpl::true_ const&
                          , boost::mpl::true_ const&
                          ) const
    {
      return block_(pos);
    }

    private:
    block_type  block_;
    extent_type size_;
  };
}

namespace meta
{
  //============================================================================
  // Register table_container as a proper container
  //============================================================================
  template<class T, class S>
  struct is_container< container::table_container<T, S> > : boost::mpl::true_
  {};
  
  template<>
  struct container_of<container::domain>
  {
    struct type
    {
      template<class T, class S>
      struct apply
      {
        typedef container::table_container<T, S> type;
      };
    };
  };
  
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Register table_container as a proper Hierarchizable
  //============================================================================
  template<class T, class S>
  struct value_of< nt2::container::table_container<T, S> >
  {
    typedef T type;
  };

  template<class T, class S, class Origin>
  struct hierarchy_of< nt2::container::table_container<T, S>, Origin >
  {
    typedef table_< typename property_of< typename value_of<T>::type
                                        , Origin
                                        >::type
                  , S
                  >                                   type;
  };

  //============================================================================
  // table_container produce container expression from proper type and settings.
  //============================================================================
  template<class T, class S>
  struct terminal_of< nt2::container::table_container<T, S> >
  {
    // Retrieve normalized settings
    typedef typename nt2::container::
            table_container<T, S>::settings_type                  settings_type;

    typedef nt2::container::table_container<T, settings_type>         container;

    typedef nt2::container::
            expression< typename boost::proto::terminal< container >::type
                      , container
                      >                                                    type;
  };

  //============================================================================
  // table use table_container to do its biddings
  //============================================================================
  template<class T, class S> struct semantic_of< nt2::container::table<T, S> >
  {
    typedef nt2::container::table_container<T, S> type;
  };
} } }

#endif
