[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['iT','T'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'scalar_ints' : True,  
         'simd_types' : ['real_'],
         'special' : ["polynomials"],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 06/03/2011',
             'cover_included' : ['#include <nt2/toolbox/boost_math/include/functions/legendre_p.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 06/03/2011',
            },
         'ranges' : {
             'default' : [['iT(0)', 'iT(10)'], ['T(-1)', 'T(1)']],
            },
         'specific_values' : {
             'unsigned_int_' : {
                 '1,nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 '1,nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '1,nt2::Half<T>()' : {'result' : 'nt2::Half<r_t>()','ulp_thresh' : '0.5',},
                 '1,nt2::Inf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 '1,nt2::Minf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 '1,nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 '1,nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 '1,nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 '1,nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 '1,nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::legendre(a0,a1)'],
                },
             'property_value' : {
                 'real_' : ['nt2::boost_math::legendre_p(a0,a1)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'real_' : ['50'],
                },
            },
        },
    },
]
