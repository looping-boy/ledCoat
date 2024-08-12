#ifndef LED_MAP_H
#define LED_MAP_H

typedef struct {
    uint8_t pwmChannel;
    uint8_t numbersOfLeds;
    uint16_t indexInPwm;
    uint16_t indexTotal;
    uint8_t offset;
    bool isGoingUp;
} LedInfo;

LedInfo ledMappingVertical[72] = {
    {1, 17, 0, 0, 5, false}, 
    {1, 19, 17, 17, 5, true}, 
    {1, 21, 36, 36, 5, false}, 
    {1, 23, 57, 57, 5, true},
    {1, 25, 80, 80, 5, false}, 
    {1, 27, 105, 105, 5, true}, 
    {1, 28, 132, 132, 4, false}, 
    {1, 30, 160, 160, 4, true},
    {1, 33, 190, 190, 4, false}, 

    {2, 33, 0, 223, 4, false}, 
    {1, 32, 223, 256, 3, true}, 
    {2, 32, 33, 288, 3, true},
    {1, 31, 255, 320, 3, false}, 
    {2, 30, 65, 351, 3, false},

    {1, 20, 286, 381, 2, true}, 
    {1, 17, 306, 401, 2, false},
    {1, 16, 323, 418, 2, true}, 
    {1, 16, 339, 434, 2, false}, 
    {1, 15, 355, 450, 2, true}, 
    {1, 14, 370, 465, 1, false},
    {1, 15, 384, 479, 1, true}, 
    {1, 16, 399, 494, 1, false}, 
    {1, 17, 415, 510, 1, true}, 
    {1, 19, 432, 527, 1, false}, // END 1 to 451

    {2, 33, 95, 546, 1, true}, 
    {3, 33, 0, 579, 1, true}, 
    {2, 32, 128, 612, 0, false}, 
    {3, 32, 33, 644, 0, false},
    {2, 32, 160, 676, 0, true}, 
    {3, 32, 65, 708, 0, true}, 
    {2, 32, 192, 740, 0, false}, 
    {3, 32, 97, 772, 0,false},

    {2, 31, 224, 804, 0, true}, 
    {3, 31, 129, 835, 0, true}, 
    {2, 31, 255, 866, 0, false}, 
    {3, 31, 160, 897, 0, false},
    {2, 31, 286, 928, 0, true}, 
    {3, 31, 191, 959, 0, true}, 
    {2, 31, 317, 990, 0, false}, 
    {3, 31, 222, 1021, 0, false},

    {2, 32, 348, 1052, 0, true}, 
    {3, 32, 253, 1084, 0, true}, 
    {2, 32, 380, 1116, 0, false}, 
    {3, 32, 285, 1148, 0, false},
    {2, 32, 412, 1180, 0, true}, 
    {3, 32, 317, 1212, 0, true}, 
    {2, 33, 444, 1244, 1, false}, // END OF 2
    {3, 33, 349, 1277, 1, false},

    {0, 19, 0, 1310, 1, true}, 
    {0, 17, 19, 1329, 1, false}, 
    {0, 16, 36, 1346, 1, true}, 
    {0, 15, 52, 1362, 1, false},
    {0, 14, 67, 1377, 1, true}, 
    {0, 15, 81, 1391, 2, false}, 
    {0, 16, 96, 1406, 2, true}, 
    {0, 16, 112, 1422, 2, false},
    {0, 17, 128, 1438, 2, true}, 
    {0, 20, 145, 1455, 3, false}, 

    {3, 30, 382, 1475, 3, true}, 
    {0, 31, 165, 1505, 3, true},
    {3, 32, 412, 1536, 3, false}, 
    {0, 32, 196, 1568, 3, false}, 
    {3, 33, 444, 1600, 4, true}, 

    {0, 33, 228, 1633, 4, true},
    {0, 30, 261, 1666, 4, false}, 
    {0, 28, 291, 1696, 4, true}, 
    {0, 27, 319, 1724, 5, false}, 
    {0, 25, 346, 1751, 5, true},
    {0, 23, 371, 1776, 5, false}, 
    {0, 21, 394, 1799, 5, true}, 
    {0, 19, 415, 1820, 5, false}, 
    {0, 17, 434, 1839, 5, true} // TOTAL 1856
};

#endif 