#ifndef JEUSTATE_H
#define JEUSTATE_H

#include "GameState.h"

state_t * JS_get();

static char *FirstLevelMap[] = {
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        "0                                                                                    w                                                               0",
        "0                   w                                  w                   w                                                       w                 0",
        "0                                      w                                                                        w                                    0",
        "0                                                                                                                                                    0",
        "0                                                                                             w                                                      0",
        "0                                                                                                                   w                                0",
        "0                                                                                                               r          eEEEEE                    0",
        "0                                                                                                              rr          EEEEEE             w      0",
        "0                    kkckk                                      kkk    kkck                                   rrr          EEEEEE                    0",
        "0                                      t0       kk              k k                 k          t0            rrrr          EEEEEE                    0",
        "0G                                     00              t0                     t0    kG         00           rrrrr          EEEEEE                    0",
        "0           d    g       d             00              00                     00    k          00    g     rrrrrr          EEEEEE                    0",
        "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
        "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};

#endif
