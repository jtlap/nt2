[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename nt2::meta::as_logical<T>::type',
            },
         'simd_types' : ['real_'],
         'special' : ['predicate'],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : ['#include <nt2/sdk/simd/logical.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'default' : [['T(-10000)', 'T(10000)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : 'nt2::False<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Two<T>()' : {'result' : 'nt2::False<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::True<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '-nt2::Zero<T>()' : {'result' : 'nt2::True<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Half<T>()' : {'result' : 'nt2::False<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::False<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::True<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::True<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::True<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::False<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Quarter<T>()' : {'result' : 'nt2::False<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Two<T>()' : {'result' : 'nt2::False<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::True<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : 'nt2::True<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::False<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Two<T>()' : {'result' : 'nt2::False<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::True<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::is_ngtz(a0)'],
                },
             'property_value' : {
                 'default' : ['a0<=0'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
    },
]