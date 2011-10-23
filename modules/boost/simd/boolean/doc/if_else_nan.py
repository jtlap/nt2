[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['The function conditionnaly to a0 returns a1 or nan,',
                          'or more exactly the value of type A1 with all bits set'],
         'return' : ['always of the type of the second parameter'],   
         'module' : 'boolean',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_', 'signed_int_','unsigned_int_'],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_','unsigned_int_'],
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
             'default' : [['T(0)', 'T(1)'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
            },
         'specific_values' : {
             'unsigned_int_' : {
                 'T(0),T(1)' : {'result' : 'boost::simd::Valmax<T>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Valmax<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 'T(0),T(1)' : {'result' : 'boost::simd::Nan<T>()','ulp_thresh' : '0.5',},
                 'T(1),T(1)' : {'result' : '1','ulp_thresh' : '0.5',},
                 'boost::simd::Inf<T>(),T(1)' : {'result' : '1','ulp_thresh' : '0.5',},
                 'boost::simd::Minf<T>(),T(1)' : {'result' : '1','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>(),T(1)' : {'result' : '1','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>(),T(1)' : {'result' : 'boost::simd::Nan<T>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'T(0),T(1)' : {'result' : '1','-1' : '0.5',},
                 'T(1),T(1)' : {'result' : '1','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : '-1','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::if_else_nan(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['a0?r_t(a1):boost::simd::Allbits<A1>()'],
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
