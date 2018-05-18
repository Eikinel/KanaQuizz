#include "Kana.h"

//Hiragana symbols
const wchar_t Hiragana::_kana[eKana::KANA_SIZE] = {
	L'\u3042', L'\u3044', L'\u3046', L'\u3048', L'\u304A',	// A, I, U, E, O
	L'\u304B', L'\u304D', L'\u304F', L'\u3051', L'\u3053',	// KA, KI, KU, KE, KO
	L'\u304C', L'\u304E', L'\u3050', L'\u3052', L'\u3054',	// GA, GI, GU, GE, GO
	L'\u3055', L'\u3057', L'\u3059', L'\u305B', L'\u305D',	// SA, SI, SU, SE, SO
	L'\u3056', L'\u3058', L'\u305A', L'\u305C', L'\u305E',	// ZA, ZI, ZU, ZE, ZO
	L'\u305F', L'\u3061', L'\u3064', L'\u3066', L'\u3068',	// TA, TI, TU, TE, TO
	L'\u3060', L'\u3062', L'\u3065', L'\u3067', L'\u3069',	// DA, DI, DU, DE, DO
	L'\u306A', L'\u306B', L'\u306C', L'\u306D', L'\u306E',	// NA, NI, NU, NE, NO
	L'\u306F', L'\u3072', L'\u3075', L'\u3078', L'\u307B',	// HA, HI, HU, HE, HO
	L'\u3070', L'\u3073', L'\u3076', L'\u3079', L'\u307C',	// BA, BI, BU, BE, BO
	L'\u3071', L'\u3074', L'\u3077', L'\u307A', L'\u307D',	// PA, PI, PU, PE, PO
	L'\u307E', L'\u307F', L'\u3080', L'\u3081', L'\u3082',	// MA, MI, MU, ME, MO
	L'\u3084', L'\u3086', L'\u3088',						// YA, YU, YO
	L'\u3089', L'\u308A', L'\u308B', L'\u308C', L'\u308D',	// RA, RI, RU, RE, RO
	L'\u308F', L'\u3092',									// WA, WO
	L'\u3093'												// N
};

// Romaji
// Because there are multiple forms of romaji for some kana, I'm forced to add an extra table
const char* Hiragana::_romaji[eKana::KANA_SIZE][MAX_ROMAJI] = {
	{ "a", NULL }, { "i", NULL }, { "u", NULL }, { "e", NULL }, { "o", NULL },
	{ "ka", NULL }, { "ki", NULL }, { "ku", NULL }, { "ke", NULL }, { "ko", NULL },
	{ "ga", NULL }, { "gi", NULL }, { "gu", NULL }, { "ge", NULL }, { "go", NULL },
	{ "sa", NULL }, { "si", "shi" }, { "su", NULL }, { "se", NULL }, { "so", NULL },
	{ "za", NULL }, { "zi", "ji" }, { "zu", NULL }, { "ze", NULL }, { "zo", NULL },
	{ "ta", NULL }, { "ti", "chi" }, { "tu", "tsu" }, { "te", NULL }, { "to", NULL },
	{ "da", NULL }, { "di", NULL }, { "du", NULL }, { "de", NULL }, { "do", NULL },
	{ "na", NULL }, { "ni", NULL }, { "nu", NULL }, { "ne", NULL }, { "no", NULL },
	{ "ha", NULL }, { "hi", NULL }, { "hu", "fu" }, { "he", NULL }, { "ho", NULL },
	{ "ba", NULL }, { "bi", NULL }, { "bu", NULL }, { "be", NULL }, { "bo", NULL },
	{ "pa", NULL }, { "pi", NULL }, { "pu", NULL }, { "pe", NULL }, { "po", NULL },
	{ "ma", NULL }, { "mi", NULL }, { "mu", NULL }, { "me", NULL }, { "mo", NULL },
	{ "ya", NULL }, { "yu", NULL }, { "yo", NULL },
	{ "ra", NULL }, { "ri", NULL }, { "ru", NULL }, { "re", NULL }, { "ro", NULL },
	{ "wa", NULL }, { "wo", NULL },
	{ "n", NULL }
};


//GETTERS
const wchar_t&	IKana::kana(const eKana kana)
{
	return (_kana[kana]);
}

const wchar_t*	IKana::allKana()
{
	return (_kana);
}

const char**	IKana::toRomaji(const eKana kana)
{
	return (_romaji[kana]);
}