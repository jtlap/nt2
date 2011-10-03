[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "Constant $Fct$ = -0",
                           "This is a special constant as it can be used and considered",
                           "identical to zero, except that for floating point numbers,",
                           "there is two different representation of zero with different bit of sign."
                           "\par", "The existence of the sign can be used in special circumstances as",
                           "choosing between \\\\f$\pm\infty\\\\f$ instead of nan in computing 1/0.",
                           "\par", "The sign of zero can be accessed through the is_negative and is_positive predicates."],
         'return' : ["type T value"],
         'template' : True,   
         'module' : 'boost',
         'special' : ['constant'],   
         'arity' : '0',
         'call_types' : [],
         'ret_arity' : '0',
         'tpl' : '<T>',   
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_', 'signed_int_','unsigned_int_'],
         'type_defs' : [],
         'types' : ['real_',  'signed_int_','unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 02/10/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 02/10/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
            },
         'specific_values' : {
             'default' : {
                 '-' : {'result' : 'T(1)','ulp_thresh' : '0',},
                },
            },
        },
    },
]
