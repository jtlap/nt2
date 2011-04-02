#define NT2_UNIT_MODULE "nt2 matlab toolbox - sin"

#include <nt2/toolbox/matlab/function/sin.hpp>
#include <nt2/toolbox/trigonometric/include/constants.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE(sin)
{
    NT2_TEST_LESSER_EQUAL(nt2::details::ulpdist(nt2::matlab::sin(-nt2::Pi<double>()/2), nt2::Mone<double>()), 0.5);
}
