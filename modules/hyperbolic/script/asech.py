[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['hyperbolic secant argument \\\\f$\mathop{\\\\textrm{acosh}}(1/a_0)\\\\f$'] ,
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 20/02/2011',
             'included' : ['#include <nt2/toolbox/exponential/constants.hpp>'],
             'cover_included' :
                ['#include <nt2/toolbox/boost_math/include/functions/acosh.hpp>',
                 'extern "C" { long double cephes_acoshl(long double); }',
                 '#include <nt2/include/functions/rec.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 20/02/2011',
            },
         'ranges' : {
             'default' : [['T(0)', 'T(0.9)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::Zero<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::Zero<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::asech(a0)','nt2::asech(a0)'],
                },
             'property_value' : {
                 'real_' : ['nt2::boost_math::acosh(nt2::rec(a0))','::cephes_acoshl(nt2::rec(a0))'],
                },
             'ulp_thresh' : {
                 'real_' : ['5.0','1.0'],
                },
            },
        },
    },
]
