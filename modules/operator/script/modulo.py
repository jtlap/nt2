[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'r_t',
            },
         'type_defs' : [],
         'simd_types' : ['signed_int_', 'unsigned_int_'],
         'types' : ['signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [
                [['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['nt2::One<T>()', 'nt2::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Two<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),nt2::Two<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>(),nt2::Two<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Two<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),nt2::Two<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'unsigned_int_' : {
                 'nt2::Four<T>(),nt2::Two<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Two<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),nt2::Two<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['nt2::modulo(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['a0%a1'],
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
