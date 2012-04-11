[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "The function always returns a value of the same type than the entry.",
                           "Take care that for integers the value returned can differ by one unit",
                           "from \c ceil((a+b)/2.0) or \c floor((a+b)/2.0), but is always one of",
                           "the two"
                           ],
          'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 28/11/2010',
             'included' : [],
             'notes' : ['for integer values average does not,coincide with (a0+a1)/2 by at most one unit.'],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-100)', 'T(100)'], ['T(-100)', 'T(100)']],
             'signed_int_' : [['T(-100)', 'T(100)'], ['T(-100)', 'T(100)']],
             'unsigned_int_' : [['T(0)', 'T(100)'], ['T(0)', 'T(100)']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : 'boost::simd::Inf<T>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Minf<T>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<T>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::average(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['(a0+a1)/2'],
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                 'real_' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
