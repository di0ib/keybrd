/* keybrd_3e_sublayerNestedScSc.ino

This sketch:
    is firmware for layout 2 layers plus 1 sublayer.
    runs on the first three columns of a breadboard keyboard

| Layout | **0** | **1** | **2** |
|:------:|:-----:|:-----:|:-----:|
|  **0** | a - 1 | b =   | c Num |
|  **1** |Normal | Sym   | Enter |

*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Keys
#include <Code_Sc.h>
#include <LayerState.h>
#include <Code_LayerLock.h>
#include <Code_LayerHold.h>
#include <Key_LayeredKeys.h>
#include <Key_LayeredScSc.h>

//Matrix
#include <Row.h>
#include <Scanner_uC.h>
#include <ScanDelay.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================== SCANNER ==================
uint8_t readPins[] = {14, 15, 16};
uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner(LOW, readPins, readPinCount);

// =================== CODES ===================
// ---------------- LAYER CODE -----------------
enum layers { NORMAL, SYM };

LayerState layerState;

Code_LayerLock l_normal(NORMAL, layerState);
Code_LayerLock l_sym(SYM, layerState);

LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

// ---------------- SUBLAYER CODE --------------
enum subLayers { SUBSYM, SUBNUM };

LayerState sublayerState;

Code_LayerHold l_num(SUBNUM, sublayerState);

LayerStateInterface& Key_LayeredScSc::refLayerState = sublayerState;

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);

Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_enter(KEY_ENTER);

Code_Sc s_1(KEY_1);

/* =================== KEYS ====================
The key k_sub00 contains codes for layerIds SUBSYM and SUBNUM.
Key_LayeredScSc takes two scancode arguments.
(The Num sublayer only has one key because small example.  Usually sublayers have multiple keys.)
*/
Key_LayeredScSc sub_00(KEY_MINUS, KEY_1);

/*
k_sub00 is nested in k_00.
The key k_00 contains code and key for layerIds NORMAL and SYS.
Notice that k_sub00 is of type Key_LayeredKeys1, while k_00 is of type Key_LayeredKeys.
k_sub00 and k_00 are associated with distinct LayerStates.
*/
Key* const ptrsCodes_00[] = { &s_a, &sub_00 };
Key_LayeredKeys k_00(ptrsCodes_00);

Key* const ptrsCodes_01[] = { &s_b, &s_equal };
Key_LayeredKeys k_01(ptrsCodes_01);

Key* const ptrsCodes_02[] = { &s_c, &l_num };
Key_LayeredKeys k_02(ptrsCodes_02);

// =================== ROWS ====================
Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* const ptrsKeys_1[] = { &l_normal, &l_sym, &s_enter };
uint8_t keyCount_1 = sizeof(ptrsKeys_1)/sizeof(*ptrsKeys_1);
Row row_1(scanner, 1, ptrsKeys_1, keyCount_1);

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
}

void loop()
{
    row_0.process();
    row_1.process();
    scanDelay.delay();
}
