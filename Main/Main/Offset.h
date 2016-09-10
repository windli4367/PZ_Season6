#pragma once

// Main Offsets
#define oMainAddress				0xE611B2			// Connect Main IP Address
#define oMainVersion				0xE61F68			// Main Version (22749)
#define oMainSerial					0xE61F70			// Main Serial (k1Pk2jcET48mxL3b)
#define oMainCSPort					0xE609E4			// Main CS Port (44405)
#define oMainWinTitle				0x4D0E09			// Main Title (MU)
#define oMainMapNumber				*(int*)0xE61E18		// Current Map Number
#define oMainState					*(int*)0xE609E8		// Current Main State

// Other Fixes (Fix.cpp)

// Disable CMStarter
#define oCMStarter1					0x40B4BA			// +2 (0x350)
#define oCMStarter2					0x40B4C3			// +2 (0x350)
#define oCMStarter3					0x40B4CD			// +2 (0x18)

#define oMUExeCall					0x4D1E69			// Disable MU.exe call
#define oConfigIni					0x4D2246			// Disable Config.ini
#define oWebCheck					0x4D9D24			// Disable web check
#define oAccountField				0x40AF09			// (+1) Enable account field

// Disable ResourceGuard Call
#define oResGuardCall1				0x4D556F
#define oResGuardCall2				0x633F4D
#define oResGuardCall3				0x6343D6
#define oResGuardCall4				0x63E697

// ResourceGuard Jumps
#define oResGuardJmps1				0x4D559C
#define oResGuardJmps2				0x633F7A
#define oResGuardJmps3				0x634403
#define oResGuardJmps4				0x63E6C4

// Bypass terrain files
#define oTerrainPass1				0x62EBF8			
#define oTerrainPass2				0x62EBFE
#define oTerrainPass3				0x62EE42
#define oTerrainPass4				0x62EE48
#define oTerrainPass5				0x62EEE5
#define oTerrainPass6				0x62EEEB

// Increase terrains amount to 105
#define oTerrainNum1				0x62EBF7
#define oTerrainNum2				0x62EE41
#define oTerrainNum3				0x62EEE4

// Bypass in Local folder text .bmd files
#define oTextBmdLocalPass			0x7E34EF

#define oFixTabKeyLogin				0x40B154			// Size 5
#define oAllowTabSwithLoginJMP		0x40B16F