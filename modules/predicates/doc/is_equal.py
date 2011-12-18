[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename nt2::meta::as_logical<T>::type',
            },
         'special' : ['predicate'],
         'type_defs' : [],
         'types' : ['integer_','real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ['#include <nt2/sdk/simd/logical.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [
                [['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
             'integer_' : {
                 'nt2::Mone<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'nt2::Minf<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['nt2::eq(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['a0==a1'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'integer_' : ['0'],
                },
            },
        },
    },
]
