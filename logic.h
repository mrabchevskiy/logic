                                                                                                                              /*
 Copyright Mykola Rabchevskiy 2022.
 Distributed under the Boost Software License, Version 1.0.
 (See http://www.boost.org/LICENSE_1_0.txt)
 ______________________________________________________________________________

 Three-value (Łukasiewicz version) logic

 See `https://en.wikipedia.org/wiki/Three-valued_logic` for details

 Implemented as wrapper over `std::strong_ordering` that represents results
 of the three-way comparison operator `<=>`.

 Implication operator represented by the pseudo-operator `-->` that actually
 is a conbination of postfix `--` and `>`

 2022.01.31 Initial version

________________________________________________________________________________________________________________________________
                                                                                                                              */
#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include <compare>

namespace CoreAGI {

  class Logic {

    using O = std::strong_ordering;

    O value;

  public:

    constexpr          Logic(                ): value{ O::equal                 }{}
    constexpr          Logic( const Logic& x ): value{ x.value                  }{}
    constexpr explicit Logic( const O&     o ): value{ o                        }{}
    constexpr explicit Logic( const bool&  b ): value{ b ? O::greater : O::less }{}

    constexpr explicit operator bool() const { return value > 0; }

    constexpr Logic& operator= ( const Logic& x ){ value = x.value;                  return *this; }
    constexpr Logic& operator= ( const bool&  x ){ value = x ? O::greater : O::less; return *this; }

    constexpr const char* c_str() const {
      if( value < 0 ){ return "FALSE";  }
      if( value > 0 ){ return "TRUE";   }
                       return "UNKNOWN";
    }

    constexpr Logic operator not () const {
      if( value < 0 ){ return Logic{ O::greater }; }
      if( value > 0 ){ return Logic{ O::less    }; }
                       return Logic{ O::equal   };
    }

    constexpr Logic operator == ( const Logic& x ) const {
      if( value <  0 and x.value <  0 ){ return Logic{ O::greater }; }
      if( value == 0 and x.value == 0 ){ return Logic{ O::greater }; }
      if( value >  0 and x.value >  0 ){ return Logic{ O::greater }; }
                                         return Logic{ O::less    };
    }

    constexpr Logic operator and ( const Logic& x ) const {
      if( value <  0 or x.value  < 0 ){ return Logic{ O::less    }; }
      if( value == 0 or x.value == 0 ){ return Logic{ O::equal   }; }
                                        return Logic{ O::greater };
    }

    constexpr Logic operator or ( const Logic& x ) const {
      if( value >  0 or  x.value >  0 ){ return Logic{ O::greater }; }
      if( value == 0 or  x.value == 0 ){ return Logic{ O::equal   }; }
                                         return Logic{ O::less    };
    }

    Logic operator-- (int) const { return Logic( value ); } // :postfix `--` produces copy of the instance

    Logic operator > ( const Logic& L ) const {
      if( L.value < 0 ){
        if( value <  0 ) return Logic{ O::greater };
        if( value == 0 ) return Logic{ O::equal   };
        if( value >  0 ) return Logic{ O::less    };
      }
      if( L.value == 0 ){
        if( value <  0 ) return Logic{ O::greater };
        if( value == 0 ) return Logic{ O::greater };
        if( value >  0 ) return Logic{ O::equal   };
      }
      return Logic{ O::greater };
    }

  };//class Logic

  constexpr const Logic FALSE  { std::strong_ordering::less    };
  constexpr const Logic TRUE   { std::strong_ordering::greater };
  constexpr const Logic UNKNOWN{ std::strong_ordering::equal   };

}//namespace CoreAGI

#endif // LOGIC_H_INCLUDED
