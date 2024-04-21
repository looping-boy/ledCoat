/// @file    ArrayOfLedArrays.ino
/// @brief   Set up three LED strips, all running from an array of arrays
/// @example ArrayOfLedArrays.ino

// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with, only this time they're going
// to be all parts of an array of arrays.

#include <FastLED.h>

#define NUM_STRIPS 4
#define SIZE_ANIM 1856
#define BRIGHTNESS 20

CRGB leds[NUM_STRIPS][500];
#include "I2SClocklessVirtualLedDriver.h"

typedef struct {
    int pwmChannel;
    int numbersOfLeds;
    int indexInPwm;
    int indexTotal;
    bool isGoingUp;
} LedInfo;

typedef struct {
    int pwmChannel;
    int indexInPwm;
} LedInfoTest;

LedInfoTest ledMappingHorizontal[72][72] = {{{2 , 444}, {2 , 127}, {2 , 128}, {2 , 191}, {2 , 192}, {2 , 379}, {2 , 380}, {2 , 443}, {3 , 32}, {3 , 33}, {3 , 96}, {3 , 97}, {3 , 284}, {3 , 285}, {3 , 348}, {3 , 349}}, {{1 , 190}, {1 , 254}, {2 , 445}, {2 , 0}, {2 , 64}, {2 , 126}, {2 , 129}, {2 , 190}, {2 , 193}, {2 , 254}, {2 , 255}, {2 , 316}, {2 , 317}, {2 , 378}, {2 , 381}, {2 , 442}, {3 , 31}, {3 , 34}, {3 , 95}, {3 , 98}, {3 , 159}, {3 , 160}, {3 , 221}, {3 , 222}, {3 , 283}, {3 , 286}, {3 , 347}, {3 , 350}, {3 , 412}, {3 , 476}, {0 , 196}, {0 , 260}}, {{1 , 255}, {1 , 191}, {1 , 253}, {2 , 447}, {2 , 446}, {2 , 1}, {2 , 63}, {2 , 124}, {2 , 125}, {2 , 131}, {2 , 130}, {2 , 188}, {2 , 189}, {2 , 195}, {2 , 194}, {2 , 252}, {2 , 253}, {2 , 257}, {2 , 256}, {2 , 314}, {2 , 315}, {2 , 319}, {2 , 318}, {2 , 376}, {2 , 377}, {2 , 383}, {2 , 382}, {2 , 440}, {2 , 441}, {3 , 29}, {3 , 30}, {3 , 36}, {3 , 35}, {3 , 93}, {3 , 94}, {3 , 100}, {3 , 99}, {3 , 157}, {3 , 158}, {3 , 162}, {3 , 161}, {3 , 219}, {3 , 220}, {3 , 224}, {3 , 223}, {3 , 281}, {3 , 282}, {3 , 288}, {3 , 287}, {3 , 345}, {3 , 346}, {3 , 352}, {3 , 351}, {3 , 413}, {3 , 475}, {0 , 195}, {0 , 197}, {0 , 259}}, {{1 , 256}, {1 , 192}, {1 , 252}, {2 , 448}, {2 , 2}, {2 , 62}, {2 , 65}, {2 , 123}, {2 , 132}, {2 , 187}, {2 , 196}, {2 , 251}, {2 , 258}, {2 , 313}, {2 , 320}, {2 , 375}, {2 , 384}, {2 , 439}, {3 , 28}, {3 , 37}, {3 , 92}, {3 , 101}, {3 , 156}, {3 , 163}, {3 , 218}, {3 , 225}, {3 , 280}, {3 , 289}, {3 , 344}, {3 , 353}, {3 , 411}, {3 , 414}, {3 , 474}, {0 , 194}, {0 , 198}, {0 , 258}}, {{1 , 257}, {1 , 193}, {1 , 189}, {1 , 251}, {2 , 449}, {2 , 3}, {2 , 61}, {2 , 66}, {2 , 122}, {2 , 133}, {2 , 186}, {2 , 197}, {2 , 250}, {2 , 259}, {2 , 312}, {2 , 321}, {2 , 374}, {2 , 385}, {2 , 438}, {3 , 27}, {3 , 38}, {3 , 91}, {3 , 102}, {3 , 155}, {3 , 164}, {3 , 217}, {3 , 226}, {3 , 279}, {3 , 290}, {3 , 343}, {3 , 354}, {3 , 410}, {3 , 415}, {3 , 473}, {0 , 193}, {0 , 199}, {0 , 257}, {0 , 261}}, {{1 , 258}, {1 , 194}, {1 , 188}, {1 , 250}, {2 , 450}, {2 , 4}, {2 , 60}, {2 , 67}, {2 , 121}, {2 , 134}, {2 , 185}, {2 , 198}, {2 , 249}, {2 , 260}, {2 , 311}, {2 , 322}, {2 , 373}, {2 , 386}, {2 , 437}, {3 , 26}, {3 , 39}, {3 , 90}, {3 , 103}, {3 , 154}, {3 , 165}, {3 , 216}, {3 , 227}, {3 , 278}, {3 , 291}, {3 , 342}, {3 , 355}, {3 , 409}, {3 , 416}, {3 , 472}, {0 , 192}, {0 , 200}, {0 , 256}, {0 , 262}}, {{1 , 259}, {1 , 195}, {1 , 132}, {1 , 187}, {1 , 249}, {2 , 451}, {2 , 5}, {2 , 59}, {2 , 68}, {2 , 120}, {2 , 135}, {2 , 184}, {2 , 199}, {2 , 248}, {2 , 261}, {2 , 310}, {2 , 323}, {2 , 372}, {2 , 387}, {2 , 436}, {3 , 25}, {3 , 40}, {3 , 89}, {3 , 104}, {3 , 153}, {3 , 166}, {3 , 215}, {3 , 228}, {3 , 277}, {3 , 292}, {3 , 341}, {3 , 356}, {3 , 408}, {3 , 417}, {3 , 471}, {0 , 191}, {0 , 201}, {0 , 255}, {0 , 263}, {0 , 318}}, {{1 , 260}, {1 , 196}, {1 , 130}, {1 , 131}, {1 , 133}, {1 , 186}, {1 , 248}, {2 , 452}, {2 , 6}, {2 , 58}, {2 , 69}, {2 , 119}, {2 , 136}, {2 , 183}, {2 , 200}, {2 , 247}, {2 , 262}, {2 , 309}, {2 , 324}, {2 , 371}, {2 , 388}, {2 , 435}, {3 , 24}, {3 , 41}, {3 , 88}, {3 , 105}, {3 , 152}, {3 , 167}, {3 , 214}, {3 , 229}, {3 , 276}, {3 , 293}, {3 , 340}, {3 , 357}, {3 , 407}, {3 , 418}, {3 , 470}, {0 , 190}, {0 , 202}, {0 , 254}, {0 , 264}, {0 , 317}, {0 , 320}, {0 , 319}}, {{1 , 262}, {1 , 261}, {1 , 198}, {1 , 197}, {1 , 80}, {1 , 129}, {1 , 135}, {1 , 134}, {1 , 184}, {1 , 185}, {1 , 246}, {1 , 247}, {2 , 453}, {2 , 8}, {2 , 7}, {2 , 56}, {2 , 57}, {2 , 71}, {2 , 70}, {2 , 118}, {2 , 137}, {2 , 182}, {2 , 201}, {2 , 246}, {2 , 263}, {2 , 308}, {2 , 325}, {2 , 370}, {2 , 389}, {2 , 434}, {3 , 23}, {3 , 42}, {3 , 87}, {3 , 106}, {3 , 151}, {3 , 168}, {3 , 213}, {3 , 230}, {3 , 275}, {3 , 294}, {3 , 339}, {3 , 358}, {3 , 405}, {3 , 406}, {3 , 420}, {3 , 419}, {3 , 468}, {3 , 469}, {0 , 188}, {0 , 189}, {0 , 204}, {0 , 203}, {0 , 252}, {0 , 253}, {0 , 266}, {0 , 265}, {0 , 315}, {0 , 316}, {0 , 321}, {0 , 370}}, {{1 , 263}, {1 , 199}, {1 , 81}, {1 , 128}, {1 , 136}, {1 , 183}, {1 , 245}, {2 , 454}, {2 , 9}, {2 , 55}, {2 , 72}, {2 , 117}, {2 , 138}, {2 , 181}, {2 , 202}, {2 , 245}, {2 , 264}, {2 , 307}, {2 , 326}, {2 , 369}, {2 , 390}, {2 , 433}, {3 , 22}, {3 , 43}, {3 , 86}, {3 , 107}, {3 , 150}, {3 , 169}, {3 , 212}, {3 , 231}, {3 , 274}, {3 , 295}, {3 , 338}, {3 , 359}, {3 , 404}, {3 , 421}, {3 , 467}, {0 , 187}, {0 , 205}, {0 , 251}, {0 , 267}, {0 , 314}, {0 , 322}, {0 , 369}}, {{1 , 264}, {1 , 200}, {1 , 79}, {1 , 82}, {1 , 127}, {1 , 137}, {1 , 182}, {1 , 244}, {2 , 455}, {2 , 10}, {2 , 54}, {2 , 73}, {2 , 116}, {2 , 139}, {2 , 180}, {2 , 203}, {2 , 244}, {2 , 265}, {2 , 306}, {2 , 327}, {2 , 368}, {2 , 391}, {2 , 432}, {3 , 21}, {3 , 44}, {3 , 85}, {3 , 108}, {3 , 149}, {3 , 170}, {3 , 211}, {3 , 232}, {3 , 273}, {3 , 296}, {3 , 337}, {3 , 360}, {3 , 403}, {3 , 422}, {3 , 466}, {0 , 186}, {0 , 206}, {0 , 250}, {0 , 268}, {0 , 313}, {0 , 323}, {0 , 368}, {0 , 371}}, {{1 , 265}, {1 , 201}, {1 , 78}, {1 , 83}, {1 , 126}, {1 , 138}, {1 , 181}, {1 , 243}, {2 , 456}, {2 , 11}, {2 , 53}, {2 , 74}, {2 , 115}, {2 , 140}, {2 , 179}, {2 , 204}, {2 , 243}, {2 , 266}, {2 , 305}, {2 , 328}, {2 , 367}, {2 , 392}, {2 , 431}, {3 , 20}, {3 , 45}, {3 , 84}, {3 , 109}, {3 , 148}, {3 , 171}, {3 , 210}, {3 , 233}, {3 , 272}, {3 , 297}, {3 , 336}, {3 , 361}, {3 , 402}, {3 , 423}, {3 , 465}, {0 , 185}, {0 , 207}, {0 , 249}, {0 , 269}, {0 , 312}, {0 , 324}, {0 , 367}, {0 , 372}}, {{1 , 266}, {1 , 202}, {1 , 77}, {1 , 36}, {1 , 84}, {1 , 125}, {1 , 139}, {1 , 180}, {1 , 242}, {1 , 305}, {2 , 457}, {2 , 12}, {2 , 52}, {2 , 75}, {2 , 114}, {2 , 141}, {2 , 178}, {2 , 205}, {2 , 242}, {2 , 267}, {2 , 304}, {2 , 329}, {2 , 366}, {2 , 393}, {2 , 430}, {3 , 19}, {3 , 46}, {3 , 83}, {3 , 110}, {3 , 147}, {3 , 172}, {3 , 209}, {3 , 234}, {3 , 271}, {3 , 298}, {3 , 335}, {3 , 362}, {3 , 401}, {3 , 424}, {3 , 464}, {0 , 145}, {0 , 184}, {0 , 208}, {0 , 248}, {0 , 270}, {0 , 311}, {0 , 325}, {0 , 366}, {0 , 373}, {0 , 414}}, {{1 , 432}, {1 , 267}, {1 , 203}, {1 , 76}, {1 , 37}, {1 , 85}, {1 , 124}, {1 , 140}, {1 , 179}, {1 , 241}, {1 , 304}, {2 , 458}, {2 , 13}, {2 , 51}, {2 , 76}, {2 , 113}, {2 , 142}, {2 , 177}, {2 , 206}, {2 , 241}, {2 , 268}, {2 , 303}, {2 , 330}, {2 , 365}, {2 , 394}, {2 , 429}, {3 , 18}, {3 , 47}, {3 , 82}, {3 , 111}, {3 , 146}, {3 , 173}, {3 , 208}, {3 , 235}, {3 , 270}, {3 , 299}, {3 , 334}, {3 , 363}, {3 , 400}, {3 , 425}, {3 , 463}, {0 , 18}, {0 , 146}, {0 , 183}, {0 , 209}, {0 , 247}, {0 , 271}, {0 , 310}, {0 , 326}, {0 , 365}, {0 , 374}, {0 , 413}}, {{1 , 433}, {1 , 268}, {1 , 204}, {1 , 75}, {1 , 35}, {1 , 38}, {1 , 86}, {1 , 123}, {1 , 141}, {1 , 178}, {1 , 240}, {1 , 303}, {2 , 459}, {2 , 14}, {2 , 50}, {2 , 77}, {2 , 112}, {2 , 143}, {2 , 176}, {2 , 207}, {2 , 240}, {2 , 269}, {2 , 302}, {2 , 331}, {2 , 364}, {2 , 395}, {2 , 428}, {3 , 17}, {3 , 48}, {3 , 81}, {3 , 112}, {3 , 145}, {3 , 174}, {3 , 207}, {3 , 236}, {3 , 269}, {3 , 300}, {3 , 333}, {3 , 364}, {3 , 399}, {3 , 426}, {3 , 462}, {0 , 17}, {0 , 147}, {0 , 182}, {0 , 210}, {0 , 246}, {0 , 272}, {0 , 309}, {0 , 327}, {0 , 364}, {0 , 375}, {0 , 412}, {0 , 415}}, {{1 , 434}, {1 , 269}, {1 , 205}, {1 , 74}, {1 , 34}, {1 , 39}, {1 , 87}, {1 , 122}, {1 , 142}, {1 , 177}, {1 , 239}, {1 , 302}, {1 , 306}, {1 , 431}, {2 , 460}, {2 , 15}, {2 , 49}, {2 , 78}, {2 , 111}, {2 , 144}, {2 , 175}, {2 , 208}, {2 , 239}, {2 , 270}, {2 , 301}, {2 , 332}, {2 , 363}, {2 , 396}, {2 , 427}, {3 , 16}, {3 , 49}, {3 , 80}, {3 , 113}, {3 , 144}, {3 , 175}, {3 , 206}, {3 , 237}, {3 , 268}, {3 , 301}, {3 , 332}, {3 , 365}, {3 , 398}, {3 , 427}, {3 , 461}, {0 , 16}, {0 , 19}, {0 , 144}, {0 , 148}, {0 , 181}, {0 , 211}, {0 , 245}, {0 , 273}, {0 , 308}, {0 , 328}, {0 , 363}, {0 , 376}, {0 , 411}, {0 , 416}}, {{1 , 435}, {1 , 270}, {1 , 206}, {1 , 73}, {1 , 0}, {1 , 33}, {1 , 40}, {1 , 88}, {1 , 121}, {1 , 143}, {1 , 176}, {1 , 238}, {1 , 301}, {1 , 307}, {1 , 338}, {1 , 339}, {1 , 399}, {1 , 430}, {2 , 461}, {2 , 16}, {2 , 48}, {2 , 79}, {2 , 110}, {2 , 145}, {2 , 174}, {2 , 209}, {2 , 238}, {2 , 271}, {2 , 300}, {2 , 333}, {2 , 362}, {2 , 397}, {2 , 426}, {3 , 15}, {3 , 50}, {3 , 79}, {3 , 114}, {3 , 143}, {3 , 176}, {3 , 205}, {3 , 238}, {3 , 267}, {3 , 302}, {3 , 331}, {3 , 366}, {3 , 397}, {3 , 428}, {3 , 460}, {0 , 15}, {0 , 20}, {0 , 51}, {0 , 111}, {0 , 112}, {0 , 143}, {0 , 149}, {0 , 180}, {0 , 212}, {0 , 244}, {0 , 274}, {0 , 307}, {0 , 329}, {0 , 362}, {0 , 377}, {0 , 410}, {0 , 417}, {0 , 450}}, {{1 , 436}, {1 , 271}, {1 , 207}, {1 , 72}, {1 , 1}, {1 , 32}, {1 , 41}, {1 , 89}, {1 , 120}, {1 , 144}, {1 , 175}, {1 , 237}, {1 , 300}, {1 , 308}, {1 , 337}, {1 , 340}, {1 , 369}, {1 , 398}, {1 , 400}, {1 , 429}, {2 , 462}, {2 , 17}, {2 , 47}, {2 , 80}, {2 , 109}, {2 , 146}, {2 , 173}, {2 , 210}, {2 , 237}, {2 , 272}, {2 , 299}, {2 , 334}, {2 , 361}, {2 , 398}, {2 , 425}, {3 , 14}, {3 , 51}, {3 , 78}, {3 , 115}, {3 , 142}, {3 , 177}, {3 , 204}, {3 , 239}, {3 , 266}, {3 , 303}, {3 , 330}, {3 , 367}, {3 , 396}, {3 , 429}, {3 , 459}, {0 , 14}, {0 , 21}, {0 , 50}, {0 , 52}, {0 , 81}, {0 , 110}, {0 , 113}, {0 , 142}, {0 , 150}, {0 , 179}, {0 , 213}, {0 , 243}, {0 , 275}, {0 , 306}, {0 , 330}, {0 , 361}, {0 , 378}, {0 , 409}, {0 , 418}, {0 , 449}}, {{1 , 437}, {1 , 272}, {1 , 208}, {1 , 71}, {1 , 2}, {1 , 31}, {1 , 42}, {1 , 90}, {1 , 119}, {1 , 145}, {1 , 174}, {1 , 236}, {1 , 299}, {1 , 309}, {1 , 336}, {1 , 341}, {1 , 368}, {1 , 370}, {1 , 397}, {1 , 401}, {1 , 428}, {2 , 463}, {2 , 18}, {2 , 46}, {2 , 81}, {2 , 108}, {2 , 147}, {2 , 172}, {2 , 211}, {2 , 236}, {2 , 273}, {2 , 298}, {2 , 335}, {2 , 360}, {2 , 399}, {2 , 424}, {3 , 13}, {3 , 52}, {3 , 77}, {3 , 116}, {3 , 141}, {3 , 178}, {3 , 203}, {3 , 240}, {3 , 265}, {3 , 304}, {3 , 329}, {3 , 368}, {3 , 395}, {3 , 430}, {3 , 458}, {0 , 13}, {0 , 22}, {0 , 49}, {0 , 53}, {0 , 80}, {0 , 82}, {0 , 109}, {0 , 114}, {0 , 141}, {0 , 151}, {0 , 178}, {0 , 214}, {0 , 242}, {0 , 276}, {0 , 305}, {0 , 331}, {0 , 360}, {0 , 379}, {0 , 408},
{0 , 419}, {0 , 448}}, {{1 , 438}, {1 , 273}, {1 , 209}, {1 , 70}, {1 , 3}, {1 , 30}, {1 , 43}, {1 , 91}, {1 , 118}, {1 , 146}, {1 , 173}, {1 , 235}, {1 , 298}, {1 , 310}, {1 , 335}, {1 , 342}, {1 , 367}, {1 , 371}, {1 , 396}, {1 , 402}, {1 , 427}, {2 , 464}, {2 , 19}, {2 , 45}, {2 , 82}, {2 , 107}, {2 , 148}, {2 , 171}, {2 , 212}, {2 , 235}, {2 , 274}, {2 , 297}, {2 , 336}, {2 , 359}, {2 , 400}, {2 , 423}, {3 , 12}, {3 , 53}, {3 , 76}, {3 , 117}, {3 , 140}, {3 , 179}, {3 , 202}, {3 , 241}, {3 , 264}, {3 , 305}, {3 , 328}, {3 , 369}, {3 , 394}, {3 , 431}, {3 , 457}, {0 , 12}, {0 , 23}, {0 , 48}, {0 , 54}, {0 , 79}, {0 , 83}, {0 , 108}, {0 , 115}, {0 , 140}, {0 , 152}, {0 , 177}, {0 , 215}, {0 , 241}, {0 , 277}, {0 , 304}, {0 , 332}, {0 , 359}, {0 , 380}, {0 , 407}, {0 , 420}, {0 , 447}}, {{1 , 439}, {1 , 274}, {1 , 210}, {1 , 69}, {1 , 4}, {1 , 29}, {1 , 44}, {1 , 92}, {1 , 117}, {1 , 147}, {1 , 172}, {1 , 234}, {1 , 297}, {1 , 311}, {1 , 334}, {1 , 343}, {1 , 366}, {1 , 372}, {1 , 395}, {1 , 403}, {1 , 426}, {2 , 465}, {2 , 20}, {2 , 44}, {2 , 83}, {2 , 106}, {2 , 149}, {2 , 170}, {2 , 213}, {2 , 234}, {2 , 275}, {2 , 296}, {2 , 337}, {2 , 358}, {2 , 401}, {2 , 422}, {3 , 11}, {3 , 54}, {3 , 75}, {3 , 118}, {3 , 139}, {3 , 180}, {3 , 201}, {3 , 242}, {3 , 263}, {3 , 306}, {3 , 327}, {3 , 370}, {3 , 393}, {3 , 432}, {3 , 456}, {0 , 11}, {0 , 24}, {0 , 47}, {0 , 55}, {0 , 78}, {0 , 84}, {0 , 107}, {0 , 116}, {0 , 139}, {0 , 153}, {0 , 176}, {0 , 216}, {0 , 240}, {0 , 278}, {0 , 303}, {0 , 333}, {0 , 358}, {0 , 381}, {0 , 406}, {0 , 421}, {0 , 446}}, {{1 , 440}, {1 , 275}, {1 , 211}, {1 , 68}, {1 , 5}, {1 , 28}, {1 , 45}, {1 , 93}, {1 , 116}, {1 , 148}, {1 , 171}, {1 , 233}, {1 , 296}, {1 , 312}, {1 , 333}, {1 , 344}, {1 , 365}, {1 , 373}, {1 , 394}, {1 , 404}, {1 , 425}, {2 , 466}, {2 , 21}, {2 , 43}, {2 , 84}, {2 , 105}, {2 , 150}, {2 , 169}, {2 , 214}, {2 , 233}, {2 , 276}, {2 , 295}, {2 , 338}, {2 , 357}, {2 , 402}, {2 , 421}, {3 , 10}, {3 , 55}, {3 , 74}, {3 , 119}, {3 , 138}, {3 , 181}, {3 , 200}, {3 , 243}, {3 , 262}, {3 , 307}, {3 , 326}, {3 , 371}, {3 , 392}, {3 , 433}, {3 , 455}, {0 , 10}, {0 , 25}, {0 , 46}, {0 , 56}, {0 , 77}, {0 , 85}, {0 , 106}, {0 , 117}, {0 , 138}, {0 , 154}, {0 , 175}, {0 , 217}, {0 , 239}, {0 , 279}, {0 , 302}, {0 , 334}, {0 , 357}, {0 , 382}, {0 , 405}, {0 , 422}, {0 , 445}}, {{1 , 441}, {1 , 276}, {1 , 212}, {1 , 67}, {1 , 6}, {1 , 27}, {1 , 46}, {1 , 94}, {1 , 115}, {1 , 149}, {1 , 170}, {1 , 232}, {1 , 295}, {1 , 313}, {1 , 332}, {1 , 345}, {1 , 364}, {1 , 374}, {1 , 393}, {1 , 405}, {1 , 424}, {2 , 467}, {2 , 22}, {2 , 42}, {2 , 85}, {2 , 104}, {2 , 151}, {2 , 168}, {2 , 215}, {2 , 232}, {2 , 277}, {2 , 294}, {2 , 339}, {2 , 356}, {2 , 403}, {2 , 420}, {3 , 9}, {3 , 56}, {3 , 73}, {3 , 120}, {3 , 137}, {3 , 182}, {3 , 199}, {3 , 244}, {3 , 261}, {3 , 308}, {3 , 325}, {3 , 372}, {3 , 391}, {3 , 434}, {3 , 454}, {0 , 9}, {0 , 26}, {0 , 45}, {0 , 57}, {0 , 76}, {0 , 86}, {0 , 105}, {0 , 118}, {0 , 137}, {0 , 155}, {0 , 174}, {0 , 218}, {0 , 238}, {0 , 280}, {0 , 301}, {0 , 335}, {0 , 356}, {0 , 383}, {0 , 404}, {0 , 423}, {0 , 444}}, {{1 , 442}, {1 , 277}, {1 , 213}, {1 , 66}, {1 , 7}, {1 , 26}, {1 , 47}, {1 , 95}, {1 , 114}, {1 , 150}, {1 , 169}, {1 , 231}, {1 , 294}, {1 , 314}, {1 , 331}, {1 , 346}, {1 , 363}, {1 , 375}, {1 , 392}, {1 , 406}, {1 , 423}, {2 , 468}, {2 , 23}, {2 , 41}, {2 , 86}, {2 , 103}, {2 , 152}, {2 , 167}, {2 , 216}, {2 , 231}, {2 , 278}, {2 , 293}, {2 , 340}, {2 , 355}, {2 , 404}, {2 , 419}, {3 , 8}, {3 , 57}, {3 , 72}, {3 , 121}, {3 , 136}, {3 , 183}, {3 , 198}, {3 , 245}, {3 , 260}, {3 , 309}, {3 , 324}, {3 , 373}, {3 , 390}, {3 , 435}, {3 , 453}, {0 , 8}, {0 , 27}, {0 , 44}, {0 , 58}, {0 , 75}, {0 , 87}, {0 , 104}, {0 , 119}, {0 , 136}, {0 , 156}, {0 , 173}, {0 , 219}, {0 , 237}, {0 , 281}, {0 , 300}, {0 , 336}, {0 , 355}, {0 , 384}, {0 , 403}, {0 , 424}, {0 , 443}}, {{1 , 443}, {1 , 278}, {1 , 214}, {1 , 65}, {1 , 8}, {1 , 25}, {1 , 48}, {1 , 96}, {1 , 113}, {1 , 151}, {1 , 168}, {1 , 230}, {1 , 293}, {1 , 315}, {1 , 330}, {1 , 347}, {1 , 362}, {1 , 376}, {1 , 391}, {1 , 407}, {1 , 422}, {2 , 469}, {2 , 24}, {2 , 40}, {2 , 87}, {2 , 102}, {2 , 153}, {2 , 166}, {2 , 217}, {2 , 230}, {2 , 279}, {2 , 292}, {2 , 341}, {2 , 354}, {2 , 405}, {2 , 418}, {3 , 7}, {3 , 58}, {3 , 71}, {3 , 122}, {3 , 135}, {3 , 184}, {3 , 197}, {3 , 246}, {3 , 259}, {3 , 310}, {3 , 323}, {3 , 374}, {3 , 389}, {3 , 436}, {3 , 452}, {0 , 7}, {0 , 28}, {0 , 43}, {0 , 59}, {0 , 74}, {0 , 88}, {0 , 103}, {0 , 120}, {0 , 135}, {0 , 157}, {0 , 172}, {0 , 220}, {0 , 236}, {0 , 282}, {0 , 299}, {0 , 337}, {0 , 354}, {0 , 385}, {0 , 402}, {0 , 425}, {0 , 442}}, {{1 , 444}, {1 , 279}, {1 , 215}, {1 , 64}, {1 , 9}, {1 , 24}, {1 , 49}, {1 , 97}, {1 , 112}, {1 , 152}, {1 , 167}, {1 , 229}, {1 , 292}, {1 , 316}, {1 , 329}, {1 , 348}, {1 , 361}, {1 , 377}, {1 , 390}, {1 , 408}, {1 , 421}, {2 , 470}, {2 , 25}, {2 , 39}, {2 , 88}, {2 , 101}, {2 , 154}, {2 , 165}, {2 , 218}, {2 , 229}, {2 , 280}, {2 , 291}, {2 , 342}, {2 , 353}, {2 , 406}, {2 , 417}, {3 , 6}, {3 , 59}, {3 , 70}, {3 , 123}, {3 , 134}, {3 , 185}, {3 , 196}, {3 , 247}, {3 , 258}, {3 , 311}, {3 , 322}, {3 , 375}, {3 , 388}, {3 , 437}, {3 , 451}, {0 , 6}, {0 , 29}, {0 , 42}, {0 , 60}, {0 , 73}, {0 , 89}, {0 , 102}, {0 , 121}, {0 , 134}, {0 , 158}, {0 , 171}, {0 , 221}, {0 , 235}, {0 , 283}, {0 , 298}, {0 , 338}, {0 , 353}, {0 , 386}, {0 , 401}, {0 , 426}, {0 , 441}}, {{1 , 445}, {1 , 280}, {1 , 216}, {1 , 63}, {1 , 10}, {1 , 23}, {1 , 50}, {1 , 98}, {1 , 111}, {1 , 153}, {1 , 166}, {1 , 228}, {1 , 291}, {1 , 317}, {1 , 328}, {1 , 349}, {1 , 360}, {1 , 378}, {1 , 389}, {1 , 409}, {1 , 420}, {2 , 471}, {2 , 26}, {2 , 38}, {2 , 89}, {2 , 100}, {2 , 155}, {2 , 164}, {2 , 219}, {2 , 228}, {2 , 281}, {2 , 290}, {2 , 343}, {2 , 352}, {2 , 407}, {2 , 416}, {3 , 5}, {3 , 60}, {3 , 69}, {3 , 124}, {3 , 133}, {3 , 186}, {3 , 195}, {3 , 248}, {3 , 257}, {3 , 312}, {3 , 321}, {3 , 376}, {3 , 387}, {3 , 438}, {3 , 450}, {0 , 5}, {0 , 30}, {0 , 41}, {0 , 61}, {0 , 72}, {0 , 90}, {0 , 101}, {0 , 122}, {0 , 133}, {0 , 159}, {0 , 170}, {0 , 222}, {0 , 234}, {0 , 284}, {0 , 297}, {0 , 339}, {0 , 352}, {0 , 387}, {0 , 400}, {0 , 427}, {0 , 440}}, {{1 , 446}, {1 , 281}, {1 , 217}, {1 , 62}, {1 , 11}, {1 , 22}, {1 , 51}, {1 , 99}, {1 , 110}, {1 , 154}, {1 , 165}, {1 , 227}, {1 , 290}, {1 , 318}, {1 , 327}, {1 , 350}, {1 , 359}, {1 , 379}, {1 , 388}, {1 , 410}, {1 , 419}, {2 , 472}, {2 , 27}, {2 , 37}, {2 , 90}, {2 , 99}, {2 , 156}, {2 , 163}, {2 , 220}, {2 , 227}, {2 , 282}, {2 , 289}, {2 , 344}, {2 , 351}, {2 , 408}, {2 , 415}, {3 , 4}, {3 , 61}, {3 , 68}, {3 , 125}, {3 , 132}, {3 , 187}, {3 , 194}, {3 , 249}, {3 , 256}, {3 , 313}, {3 , 320}, {3 , 377}, {3 , 386}, {3 , 439}, {3 , 449}, {0 , 4}, {0 , 31}, {0 , 40}, {0 , 62}, {0 , 71}, {0 , 91}, {0 , 100}, {0 , 123}, {0 , 132}, {0 , 160}, {0 , 169}, {0 , 223}, {0 , 233}, {0 , 285}, {0 , 296}, {0 , 340}, {0 , 351}, {0 , 388}, {0 , 399}, {0 , 428}, {0 , 439}}, {{1 , 447}, {1 , 282}, {1 , 218}, {1 , 61}, {1 , 12}, {1 , 21}, {1 , 52}, {1 , 100}, {1 , 109}, {1 , 155}, {1 , 164}, {1 , 226}, {1 , 289}, {1 , 319}, {1 , 326}, {1 , 351}, {1 , 358}, {1 , 380}, {1 , 387}, {1 , 411}, {1 , 418}, {2 , 473}, {2 , 28}, {2 , 36}, {2 , 91}, {2 , 98}, {2 , 157}, {2 , 162}, {2 , 221}, {2 , 226}, {2 , 283}, {2 , 288}, {2 , 345}, {2 , 350}, {2 , 409}, {2 , 414}, {3 , 3}, {3 , 62}, {3 , 67}, {3 , 126}, {3 , 131}, {3 , 188}, {3 , 193}, {3 , 250}, {3 , 255}, {3 , 314}, {3 , 319}, {3 , 378}, {3 , 385}, {3 , 440}, {3 , 448}, {0 , 3}, {0 , 32}, {0 , 39}, {0 , 63}, {0 , 70}, {0 , 92}, {0 , 99}, {0 , 124}, {0 , 131}, {0 , 161}, {0 , 168}, {0 , 224}, {0 , 232}, {0 , 286}, {0 , 295}, {0 , 341}, {0 , 350}, {0 , 389}, {0 , 398}, {0 , 429}, {0 , 438}}, {{1 , 448}, {1 , 283}, {1 , 219}, {1 , 60}, {1 , 13}, {1 , 20}, {1 , 53}, {1 , 101}, {1 , 108}, {1 , 156}, {1 , 163}, {1 , 225}, {1 , 288}, {1 , 320}, {1 , 325}, {1 , 352}, {1 , 357}, {1 , 381}, {1 , 386}, {1 , 412}, {1 , 417}, {2 , 474}, {2 , 29}, {2 , 35}, {2 , 92}, {2 , 97}, {2 , 158}, {2 , 161}, {2 , 222}, {2 , 225}, {2 , 284}, {2 , 287}, {2 , 346}, {2 , 349}, {2 , 410}, {2 , 413}, {3 , 2}, {3 , 63}, {3 , 66}, {3 , 127}, {3 , 130}, {3 , 189}, {3 , 192}, {3 , 251}, {3 , 254}, {3 , 315}, {3 , 318}, {3 , 379}, {3 , 384}, {3 , 441}, {3 , 447}, {0 , 2}, {0 , 33}, {0 , 38}, {0 , 64}, {0 , 69}, {0 , 93}, {0 , 98}, {0 , 125}, {0 , 130}, {0 , 162}, {0 , 167}, {0 , 225}, {0 , 231}, {0 , 287}, {0 , 294}, {0 , 342}, {0 , 349}, {0 , 390}, {0 , 397}, {0 , 430}, {0 , 437}}, {{1 , 449}, {1 , 284}, {1 , 220}, {1 , 59}, {1 , 14}, {1 , 19}, {1 , 54}, {1 , 102}, {1 , 107}, {1 , 157}, {1 , 162}, {1 , 224}, {1 , 287}, {1 , 321}, {1 , 324}, {1 , 353}, {1 , 356}, {1 , 382}, {1 , 385}, {1 , 413}, {1 , 416}, {2 , 475}, {2 , 30}, {2 , 34}, {2 , 93}, {2 , 96}, {2 , 159}, {2 , 160}, {2 , 223}, {2 , 224}, {2 , 285}, {2 , 286}, {2 , 347}, {2 , 348}, {2 , 411}, {2 , 412}, {3 , 1}, {3 , 64}, {3 , 65}, {3 , 128}, {3 , 129}, {3 , 190}, {3 , 191}, {3 , 252}, {3 , 253}, {3 , 316}, {3 , 317}, {3 , 380}, {3 , 383}, {3 , 442}, {3 , 446}, {0 , 1}, {0 , 34}, {0 , 37}, {0 , 65}, {0 , 68}, {0 , 94}, {0 , 97}, {0 , 126}, {0 , 129}, {0 , 163}, {0 , 166}, {0 , 226}, {0 , 230}, {0 , 288}, {0 , 293}, {0 , 343}, {0 , 348}, {0 , 391}, {0 , 396}, {0 , 431}, {0 , 436}}, {{1 , 450}, {1 , 285}, {1 , 221}, {1 , 58}, {1 , 15}, {1 , 18}, {1 , 55}, {1 , 103}, {1 , 106}, {1 , 158}, {1 , 161}, {1 , 223}, {1 , 286}, {1 , 322}, {1 , 323}, {1 , 354}, {1 , 355}, {1 , 383}, {1 , 384}, {1 , 414}, {1 , 415}, {2 , 476}, {2 , 31}, {2 , 33}, {2 , 94}, {2 , 95}, {3 , 0}, {3 , 381}, {3 , 382}, {3 , 443}, {3 , 445}, {0 , 0}, {0 , 35}, {0 , 36}, {0 , 66}, {0 , 67}, {0 , 95}, {0 , 96}, {0 , 127}, {0 , 128}, {0 , 164}, {0 , 165}, {0 , 227}, {0 , 229}, {0 , 289}, {0 , 292}, {0 , 344}, {0 , 347}, {0 , 392}, {0 , 395}, {0 , 432}, {0 , 435}}};

LedInfo ledMappingVertical[72] = {
    {1, 17, 0, 0, false}, 
    {1, 19, 17, 17, true}, 
    {1, 21, 36, 36, false}, 
    {1, 23, 57, 57, true},
    {1, 25, 80, 80, false}, 
    {1, 27, 105, 105, true}, 
    {1, 28, 132, 132, false}, 
    {1, 30, 160, 160, true},
    {1, 33, 190, 190, false}, 

    {2, 33, 0, 223, false}, 
    {1, 32, 223, 256, true}, 
    {2, 32, 33, 288, true},
    {1, 31, 255, 320, false}, 
    {2, 30, 65, 351, false},

    {1, 20, 286, 381, true}, 
    {1, 17, 306, 401, false},
    {1, 16, 323, 418, true}, 
    {1, 16, 339, 434, false}, 
    {1, 15, 355, 450, true}, 
    {1, 14, 370, 465, false},
    {1, 15, 384, 479, true}, 
    {1, 16, 399, 494, false}, 
    {1, 17, 415, 510, true}, 
    {1, 19, 432, 527, false}, // END 1 to 451

    {2, 33, 95, 546, true}, 
    {3, 33, 0, 579, true}, 
    {2, 32, 128, 612, false}, 
    {3, 32, 33, 644, false},
    {2, 32, 160, 676, true}, 
    {3, 32, 65, 708, true}, 
    {2, 32, 192, 740, false}, 
    {3, 32, 97, 772, false},

    {2, 31, 224, 804, true}, 
    {3, 31, 129, 835, true}, 
    {2, 31, 255, 866, false}, 
    {3, 31, 160, 897, false},
    {2, 31, 286, 928, true}, 
    {3, 31, 191, 959, true}, 
    {2, 31, 317, 990, false}, 
    {3, 31, 222, 1021, false},

    {2, 32, 348, 1052, true}, 
    {3, 32, 253, 1084, true}, 
    {2, 32, 380, 1116, false}, 
    {3, 32, 285, 1148, false},
    {2, 32, 412, 1180, true}, 
    {3, 32, 317, 1212, true}, 
    {2, 33, 444, 1244, false}, // END OF 2
    {3, 33, 349, 1277, false},

    {0, 19, 0, 1310, true}, 
    {0, 17, 19, 1329, false}, 
    {0, 16, 36, 1346, true}, 
    {0, 15, 52, 1362, false},
    {0, 14, 67, 1377, true}, 
    {0, 15, 81, 1391, false}, 
    {0, 16, 96, 1406, true}, 
    {0, 16, 112, 1422, false},
    {0, 17, 128, 1438, true}, 
    {0, 20, 145, 1455, false}, 

    {3, 30, 382, 1475, true}, 
    {0, 31, 165, 1505, true},
    {3, 32, 412, 1536, false}, 
    {0, 32, 196, 1568, false}, 
    {3, 33, 444, 1600, true}, 

    {0, 33, 228, 1633, true},
    {0, 30, 261, 1666, false}, 
    {0, 28, 291, 1696, true}, 
    {0, 27, 319, 1724, false}, 
    {0, 25, 346, 1751, true},
    {0, 23, 371, 1776, false}, 
    {0, 21, 394, 1799, true}, 
    {0, 19, 415, 1820, false}, 
    {0, 17, 434, 1839, true} // TOTAL 1856
};



// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, 2>(leds[1], 451);
  FastLED.addLeds<NEOPIXEL, 4>(leds[2], 477);
  FastLED.addLeds<NEOPIXEL, 5>(leds[3], 477);
  FastLED.addLeds<NEOPIXEL, 23>(leds[0], 451);
  // FastLED.addLeds<NEOPIXEL, 21>(leds[4], 70);
}

long time1,time2,time3;
void loop() {
  FastLED.setBrightness(BRIGHTNESS);
  //rainbowCycle(1);
  verticalRainbowCycle(1);
  //breathing();
}

void breathing() {
  for(uint16_t j=0; j<256; j++) {
    for(uint16_t i=300; i<400; i++) {
      for (int l = 3; l >= 0; l--) {
        leds[l][i] = CRGB(Wheel(((5 * 256 / SIZE_ANIM) + j) & 255));
      }
    }
    FastLED.show();
    //delay(1);
  }
}

void verticalRainbowCycle(uint8_t wait) {
  for(uint16_t j=0; j<256; j++) {
    for (int i = 0; i < 72; i++) {
        for (int k = 0; k < 72; k++) {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel((((i) * 256 / 72) + j) & 255));
        }
    }
    FastLED.show();
    delay(wait);
  }
}

void diagonalRainbowCycle(uint8_t wait) {
  for(uint16_t j=0; j<256; j++) {
    for (int i = 0; i < 72; i++) {
        for (int k = 0; k < 72; k++) {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel((((i) * 256 / 72) + j) & 255));
        }
    }
    FastLED.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  for(uint16_t j=0; j<256; j++) { 


    // for(uint16_t i=0; i<70; i++) {
    //   leds[4][i] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
    // }
    

    time1=ESP.getCycleCount();
    uint16_t pwm1Index = 220;
    uint16_t pwm2Index = 0;
    uint16_t pwm3Index = 0;
    uint16_t pwm4Index = 0;
    int l = 0; 
    for(uint16_t i=0; i<72; i++) {
      if (!ledMappingVertical[i].isGoingUp) {
        for (int k = 0; k < ledMappingVertical[i].numbersOfLeds; k++) {
          leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(Wheel((((ledMappingVertical[i].indexTotal + k) * 256 / SIZE_ANIM) + j) & 255));
        }
      } else {
        for (int k = ledMappingVertical[i].numbersOfLeds - 1; k >= 0 ; k--) {
          leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(Wheel((((ledMappingVertical[i].indexTotal - k + ledMappingVertical[i].numbersOfLeds - 1) * 256 / SIZE_ANIM) + j) & 255));
        }
      }
    }
    FastLED.show();
    time3=ESP.getCycleCount();
    Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    delay(wait);
  
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos; // Reverse direction for smoother color transition
  if (WheelPos < 85) {
    // For the first third of the spectrum
    return rgbToUint32(255 - WheelPos * 3, WheelPos * 3, 0); // Red to Yellow
  } else if (WheelPos < 170) {
    // For the second third of the spectrum
    WheelPos -= 85;
    return rgbToUint32(0, 255 - WheelPos * 3, WheelPos * 3); // Yellow to Blue
  } else {
    // For the final third of the spectrum
    WheelPos -= 170;
    // Ensure smooth transition between full blue and full red
    return rgbToUint32(WheelPos * 3, 0, 255 - WheelPos * 3); // Blue to Red
  }
}

// uint32_t Wheel(byte value) {
//     //Serial.printf("Byte : %d", value);
//     // Ensure the input value is within the valid range
//     if (value > 255) {
//         value = 255;
//     }
    
//     // Calculate the red component based on the input value
//     uint8_t red = value;

//     // Return the RGB color as a 32-bit integer
//     return rgbToUint32(red, 0, 0);
// }

uint32_t rgbToUint32(uint8_t red, uint8_t green, uint8_t blue) {
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}
