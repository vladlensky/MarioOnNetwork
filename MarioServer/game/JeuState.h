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
        "0                                                                                                               r          e                         0",
        "0                                                                                                              rr                             w      0",
        "0                    kkckk                                      kkk    kkck                                   rrr                                    0",
        "0                                      t0       kk              k k                 k          t0            rrrr                                    0",
        "0G                                     00              t0                     t0    kG         00           rrrrr                                    0",
        "0           d    g       d             00              00                     00    k          00    g     rrrrrr                                    0",
        "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
        "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};

#endif
