/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_PACK_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_PACK_HPP_INCLUDED

namespace nt2 { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // pack, implemented in terms of simd::expr
  ////////////////////////////////////////////////////////////////////////////
  template<class Type,std::size_t Cardinal,class BP>
  struct  pack
        : expression_facade<Type,boost::mpl::size_t<Cardinal> >::type
  {
    NT2_STATIC_ASSERT ( (meta::is_power_of_2_c<Cardinal>::value)
                      , INVALID_SIMD_PACK_CARDINAL
                      , "SIMD pqck instanciated with non-power of 2 Cardinal."
                      );

    typedef typename
    expression_facade<Type,boost::mpl::size_t<Cardinal> >::type parent;
    typedef data<Type,boost::mpl::size_t<Cardinal> >            data_type;

    typedef typename data_type::parent          base_type;
    typedef typename data_type::value_type      value_type;
    typedef typename data_type::reference       reference;
    typedef typename data_type::const_reference const_reference;
    typedef typename data_type::size_type       size_type;
    typedef typename data_type::iterator        iterator;
    typedef typename data_type::const_iterator  const_iterator;

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    BOOST_STATIC_CONSTANT(size_type, static_size = base_type::static_size);

    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////
    pack() : parent() {}

    pack(pack const& src) { boost::proto::value(*this) = boost::proto::value(src);}

    explicit pack(Type const& a0)
    {
      boost::proto::value(*this).fill(a0);
    }

    pack(base_type const& a0)
    {
      boost::proto::value(*this) = a0;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Assignments
    ////////////////////////////////////////////////////////////////////////////
    pack& operator=(pack const& src)
    {
      boost::proto::value(*this) = boost::proto::value(src);
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Array Interface
    ////////////////////////////////////////////////////////////////////////////
    reference  operator[](int i)
    {
      return boost::proto::value(*this)[i];
    }

    const_reference  operator[](int i) const
    {
      return boost::proto::value(*this)[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    iterator        begin()         { return boost::proto::value(*this).begin(); }
    iterator        end()           { return boost::proto::value(*this).end();   }
    const_iterator  begin()  const  { return boost::proto::value(*this).begin(); }
    const_iterator  end()    const  { return boost::proto::value(*this).end();   }

    ////////////////////////////////////////////////////////////////////////////
    // SIMD expression evaluates as pack
    ////////////////////////////////////////////////////////////////////////////
    template<class X>
    pack( X const& xpr
        , typename boost::disable_if< boost::is_convertible<X,Type> >::type* = 0
        )
    {
      // TODO: check that X can be put in a pack via evaluation
      boost::proto::value(*this).evaluate(xpr);
    }

    template<class X> pack& operator=(X const& xpr )
    {
      // TODO: check that X can be put in a pack via evaluation
      boost::proto::value(*this).evaluate(xpr);
      return *this;
    }
  };
} }

#endif
