[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename nt2::meta::as_integer<T, unsigned>::type',
            },
         'type_defs' : [],
         'types' : ['float', 'double', 'signed_int_', 'unsigned_int_'],
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
             'default' : [['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2']],
            },
         'specific_values' : {
             'double' : {
                 'nt2::Inf<T>()' : {'result' : '53u','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : '53u','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Signmask<T>()' : {'result' : 'sizeof(T)*8','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'float' : {
                 'nt2::Inf<T>()' : {'result' : '24u','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : '24u','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Signmask<T>()' : {'result' : 'sizeof(T)*8','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Signmask<T>()' : {'result' : 'sizeof(T)*8','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                },
             'property_value' : {
                },
             'simd' : {
                },
             'ulp_thresh' : {
                },
            },
        },
    },
]
