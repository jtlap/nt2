#ifndef NT2_SDK_OPENMP_WORKER_HPP_INCLUDED
#define NT2_SDK_OPENMP_WORKER_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker/worker.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct transform_;
    struct outer_fold_;
    struct inner_fold_step_;
    template<class T> struct openmp_;
  }

  // Transform Worker
  template<class Site, class Out, class In>
  struct worker<tag::transform_,tag::openmp_<Site>,Out,In>
  {

    worker(Out & out, In & in)
    :out_(out),in_(in)
    {}

    void operator()(std::size_t begin, std::size_t size)
    {
      work(out_,in_,begin,size);
    };

    Out & out_;
    In & in_;

    nt2::functor<tag::transform_,Site> work;

    private:
    worker& operator=(worker const&);
  };

  // Inner Fold worker
  template<class Site, class Out, class In, class Neutral, class Bop>
  struct worker<tag::inner_fold_step_,tag::openmp_<Site>,Out,In,Neutral,Bop>
  {
    worker(In & in, Neutral const & neutral, Bop const & bop)
          :in_(in),neutral_(neutral),bop_(bop)
    {
      out_ = neutral_(nt2::meta::as_<Out>());
    }

    void operator()(std::size_t begin, std::size_t size)
    {
      work(out_,in_,neutral_,bop_,begin,size);
    };

    Out out_;
    In & in_;
    Neutral const & neutral_;
    Bop const & bop_;

    nt2::functor<tag::inner_fold_step_,Site> work;

    private:
    worker& operator=(worker const&);
  };

  // Outer Fold worker
  template<class Site, class Out, class In, class Neutral,class Bop>
  struct worker<tag::outer_fold_,tag::openmp_<Site>,Out,In,Neutral,Bop>
  {
    worker(Out& out, In& in, Neutral const& n, Bop const& bop)
    : out_(out), in_(in), neutral_(n), bop_(bop)
    {}

    void operator()(std::size_t begin, std::size_t size) const
    {
      work(out_,in_,neutral_,bop_,begin,size);
    }

    Out&                     out_;
    In&                      in_;
    Neutral const &          neutral_;
    Bop const &              bop_;

    nt2::functor<tag::outer_fold_,Site> work;

    private:
    worker& operator=(worker const&);
   };

}

#endif

