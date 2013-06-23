#ifndef LOCAL_SEMANTIC_HPP
#define LOCAL_SEMANTIC_HPP

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/shape.hpp>
#include <nt2/core/settings/buffer.hpp>
#include <nt2/core/settings/sharing.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/core/settings/alignment.hpp>
#include <nt2/core/settings/interleaving.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/settings/storage_scheme.hpp>
#include <nt2/core/settings/storage_duration.hpp>

#include <vector>
#include <nt2/core/utility/of_size.hpp>

struct some_kind_
{
  template<typename Settings, typename Option>
  struct option
  {
    typedef Settings type;
  };

  template<typename Option, typename Dummy=void> struct default_;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::of_size_, Dummy>
{
  typedef nt2::_4D type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::index_, Dummy>
{
  typedef nt2::matlab_index_ type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::allocator_, Dummy>
{
  typedef std::allocator<void*> type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::interleaving_, Dummy>
{
  typedef nt2::interleaved_ type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::alignment_, Dummy>
{
  typedef nt2::aligned_ type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::storage_order_, Dummy>
{
  typedef nt2::column_major_ type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::shape_, Dummy>
{
  typedef nt2::rectangular_ type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::storage_scheme_, Dummy>
{
  typedef nt2::conventional_ type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::storage_duration_, Dummy>
{
  typedef nt2::dynamic_ type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::buffer_, Dummy>
{
  typedef nt2::built_in_ type;
};

template<typename Dummy>
struct some_kind_::default_<nt2::tag::sharing_, Dummy>
{
  typedef nt2::owned_ type;
};

namespace nt2 { namespace tag
{
  /// INTERNAL ONLY some_kind_ is a semantic
  template<class Dummy>
  struct kind_::apply<some_kind_, Dummy>
                      : boost::mpl::true_
  {};
} }

#endif
