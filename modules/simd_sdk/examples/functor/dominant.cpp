#include <iostream>
#include <nt2/sdk/meta/unknown.hpp>
#include <nt2/sdk/meta/category.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/functor/meta/dominant.hpp>

////////////////////////////////////////////////////////////////////////////////
// Define some arbitrary types and their respective category
////////////////////////////////////////////////////////////////////////////////
struct foo_tag {};
struct bar_tag {};
struct chu_tag {};

struct foo_category : nt2::tag::category<foo_category,0,1> { typedef foo_tag tag; };
struct bar_category : nt2::tag::category<bar_category,0,2> { typedef bar_tag tag; };
struct chu_category : nt2::tag::category<chu_category,1,1> { typedef chu_tag tag; };

struct foo_ { typedef foo_category nt2_category_tag; };
struct bar_ { typedef bar_category nt2_category_tag; };
struct chu_ { typedef chu_category nt2_category_tag; };

struct unk {};

int main()
{
  using nt2::meta::dominant;

  std::cout << "dominant<foo_,foo_,foo_> : " << nt2::type_id<dominant<foo_,foo_,foo_>::type>() << "\n";
  std::cout << "dominant<foo_,unk ,chu_> : " << nt2::type_id<dominant<foo_,unk ,chu_>::type>() << "\n";
  std::cout << "dominant<foo_,bar_,bar_> : " << nt2::type_id<dominant<foo_,bar_,bar_>::type>() << "\n";
  std::cout << "dominant<foo_,bar_,chu_> : " << nt2::type_id<dominant<foo_,bar_,chu_>::type>() << "\n";
}
