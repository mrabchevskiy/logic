                                                                                                                              /*
 Copyright Mykola Rabchevskiy 2022.
 Distributed under the Boost Software License, Version 1.0.
 (See http://www.boost.org/LICENSE_1_0.txt)
 ______________________________________________________________________________

 Unit test for three-value (Łukasiewicz version) logic class CoreAGI::Logic

 See `https://en.wikipedia.org/wiki/Three-valued_logic` for details

 2022.01.30 Initial version

________________________________________________________________________________________________________________________________
                                                                                                                              */
#include <cstdlib>
#include <cstdio>
#include <cassert>

#include <compare>
#include <typeinfo>

#include "logic.h"

int main(){

  using namespace CoreAGI;

  bool correct{ true };

  auto sure = [&]( const char* expr, const Logic& expected, const Logic& actual ){
    const bool ok{ expected == actual };
    if( not ok ) correct = false;
    printf( "\n %-30s expected %-8s   got %-8s   [%s]", expr, expected.c_str(), actual.c_str(), ok ? "ok" : "fail" );
  };

  printf( "\n\n UNIT TEST FOR `CoreAGI::Logic` class" );

  printf( "\n\n   Size of Logic: %lu byte (implementation dependent)", sizeof( Logic ) );
  printf(   "\n   Size of bool:  %lu byte (implementation dependent)", sizeof( bool  ) );

  printf( "\n\n Test `not` operator\n" );

  sure(  "not( FALSE   )", not FALSE   , TRUE    );
  sure(  "not( UNKNOWN )", not UNKNOWN , UNKNOWN );
  sure(  "not( TRUE    )", not TRUE    , FALSE   );

  printf( "\n\n Test `and` operator\n" );

  sure( "  FALSE and FALSE",     FALSE and FALSE   , FALSE   );
  sure( "  FALSE and UNKNOWN",   FALSE and UNKNOWN , FALSE   );
  sure( "  FALSE and TRUE",      FALSE and TRUE    , FALSE   );

  sure( "UNKNOWN and FALSE",   UNKNOWN and FALSE   , FALSE   );
  sure( "UNKNOWN and UNKNOWN", UNKNOWN and UNKNOWN , UNKNOWN );
  sure( "UNKNOWN and TRUE",    UNKNOWN and TRUE    , UNKNOWN );

  sure( "   TRUE and FALSE",      TRUE and FALSE   , FALSE   );
  sure( "   TRUE and UNKNOWN",    TRUE and UNKNOWN , UNKNOWN );
  sure( "   TRUE and TRUE",       TRUE and TRUE    , TRUE    );

  printf( "\n\n Test `or` operator\n" );

  sure( "  FALSE or FALSE",       FALSE or FALSE   , FALSE   );
  sure( "  FALSE or UNKNOWN",     FALSE or UNKNOWN , UNKNOWN );
  sure( "  FALSE or TRUE",        FALSE or TRUE    , TRUE    );

  sure( "UNKNOWN or FALSE",     UNKNOWN or FALSE   , UNKNOWN );
  sure( "UNKNOWN or UNKNOWN",   UNKNOWN or UNKNOWN , UNKNOWN );
  sure( "UNKNOWN or TRUE",      UNKNOWN or TRUE    , TRUE    );

  sure( "   TRUE or FALSE",        TRUE or FALSE   , TRUE    );
  sure( "   TRUE or UNKNOWN",      TRUE or UNKNOWN , TRUE    );
  sure( "   TRUE or TRUE",         TRUE or TRUE    , TRUE    );

  printf( "\n\n Test implication operator `-->`\n" );

  sure( "  FALSE --> FALSE",     FALSE --> FALSE   , TRUE    );
  sure( "  FALSE --> UNKNOWN",   FALSE --> UNKNOWN , TRUE    );
  sure( "  FALSE --> TRUE",      FALSE --> TRUE    , TRUE    );

  sure( "UNKNOWN --> FALSE",   UNKNOWN --> FALSE   , UNKNOWN );
  sure( "UNKNOWN --> UNKNOWN", UNKNOWN --> UNKNOWN , TRUE    );
  sure( "UNKNOWN --> TRUE",    UNKNOWN --> TRUE    , TRUE    );

  sure( "   TRUE --> FALSE",      TRUE --> FALSE   , FALSE   );
  sure( "   TRUE --> UNKNOWN",    TRUE --> UNKNOWN , UNKNOWN );
  sure( "   TRUE --> TRUE",       TRUE --> TRUE    , TRUE    );

  printf( "\n\n Test `<=>` operator\n" );

  sure( " 2 <=> 3", Logic( 2 <=> 3 ), FALSE   );
  sure( " 2 <=> 2", Logic( 2 <=> 2 ), UNKNOWN );
  sure( " 2 <=> 1", Logic( 2 <=> 1 ), TRUE    );

  printf( "\n\n Verdict: %s\n", correct ? "CORRECT" : "FAILED" );

  return correct ? EXIT_SUCCESS : EXIT_FAILURE;
}
