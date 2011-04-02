[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'type_defs' : [],
         'types' : ['real_', 'integer_'],
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
             'default' : [['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>(),nt2::Zero<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                },
             'integer_   ' : {
                 'nt2::Mone<T>(),nt2::Zero<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>(),nt2::Zero<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['nt2::bitwise_ornot(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['r_t(a0|(~a1))'],
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
