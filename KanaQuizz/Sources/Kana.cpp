#include "Kana.h"
#include <sstream>


//CONSTRUCTORS
KanaTable::KanaTable(const eKanaType type) : _type(type)
{
	std::string	kana_type[eKanaType::SIZE_KANA_TYPE] = { "Hiragana", "Katakana" };
	std::cout << "Initializing " << kana_type[type] << std::endl;
}

KanaTable::~KanaTable()
{
}

Hiragana::Hiragana() : KanaTable(eKanaType::HIRAGANA)
{
	std::stringstream ss;

	// Hiragana romaji
	this->_romaji = std::vector<std::vector<std::string>> {
		{ "a", "" }, { "i", "" }, { "u", "" }, { "e", "" }, { "o", "" },
		{ "ka", "" }, { "ki", "" }, { "ku", "" }, { "ke", "" }, { "ko", "" },
		{ "ga", "" }, { "gi", "" }, { "gu", "" }, { "ge", "" }, { "go", "" },
		{ "sa", "" }, { "si", "shi" }, { "su", "" }, { "se", "" }, { "so", "" },
		{ "za", "" }, { "zi", "ji" }, { "zu", "" }, { "ze", "" }, { "zo", "" },
		{ "ta", "" }, { "ti", "chi" }, { "tu", "tsu" }, { "te", "" }, { "to", "" },
		{ "da", "" }, { "di", "" }, { "du", "" }, { "de", "" }, { "do", "" },
		{ "na", "" }, { "ni", "" }, { "nu", "" }, { "ne", "" }, { "no", "" },
		{ "ha", "" }, { "hi", "" }, { "hu", "fu" }, { "he", "" }, { "ho", "" },
		{ "ba", "" }, { "bi", "" }, { "bu", "" }, { "be", "" }, { "bo", "" },
		{ "pa", "" }, { "pi", "" }, { "pu", "" }, { "pe", "" }, { "po", "" },
		{ "ma", "" }, { "mi", "" }, { "mu", "" }, { "me", "" }, { "mo", "" },
		{ "ya", "" }, { "yu", "" }, { "yo", "" },
		{ "ra", "" }, { "ri", "" }, { "ru", "" }, { "re", "" }, { "ro", "" },
		{ "wa", "" }, { "wo", "" },
		{ "n", "" }
	};

	this->_textures = std::vector<sf::Texture>(eKana::KANA_SIZE);
	for (int i = eKana::A; i < eKana::KANA_SIZE; i++)
	{
		//std::cout << "Creating kana '" << this->_romaji[i][0] << "'" << std::endl;
		ss << HIRAGANA_DIR << "/" << this->_romaji[i][0] << ".png";
		this->_textures[i].loadFromFile(ss.str());
		ss.str("");
	}
}

Katakana::Katakana() : KanaTable(eKanaType::KATAKANA)
{
	std::stringstream ss;

	// Katakana romaji
	this->_romaji = std::vector<std::vector<std::string>> {
		{ "A", "" },{ "I", "" },{ "U", "" },{ "E", "" },{ "O", "" },
		{ "KA", "" },{ "KI", "" },{ "KU", "" },{ "KE", "" },{ "KO", "" },
		{ "GA", "" },{ "GI", "" },{ "GU", "" },{ "GE", "" },{ "GO", "" },
		{ "SA", "" },{ "SI", "SHI" },{ "SU", "" },{ "SE", "" },{ "SO", "" },
		{ "ZA", "" },{ "ZI", "JI" },{ "ZU", "" },{ "ZE", "" },{ "ZO", "" },
		{ "TA", "" },{ "TI", "CHI" },{ "TU", "TSU" },{ "TE", "" },{ "TO", "" },
		{ "DA", "" },{ "DI", "" },{ "DU", "" },{ "DE", "" },{ "DO", "" },
		{ "NA", "" },{ "NI", "" },{ "NU", "" },{ "NE", "" },{ "NO", "" },
		{ "HA", "" },{ "HI", "" },{ "HU", "FU" },{ "HE", "" },{ "HO", "" },
		{ "BA", "" },{ "BI", "" },{ "BU", "" },{ "BE", "" },{ "BO", "" },
		{ "PA", "" },{ "PI", "" },{ "PU", "" },{ "PE", "" },{ "PO", "" },
		{ "MA", "" },{ "MI", "" },{ "MU", "" },{ "ME", "" },{ "MO", "" },
		{ "YA", "" },{ "YU", "" },{ "YO", "" },
		{ "RA", "" },{ "RI", "" },{ "RU", "" },{ "RE", "" },{ "RO", "" },
		{ "WA", "" },{ "WO", "" },
		{ "N", "" }
	};

	this->_textures = std::vector<sf::Texture>(eKana::KANA_SIZE);
	for (int i = eKana::A; i < eKana::KANA_SIZE; i++)
	{
		//std::cout << "Creating katakana '" << this->_romaji[i][0] << "'" << std::endl;
		ss << KATAKANA_DIR << "/" << this->_romaji[i][0] << ".png";
		this->_textures[i].loadFromFile(ss.str());
		ss.str("");
	}
}


//GETTERS
const eKanaType		KanaTable::getType() const
{
	return (this->_type);
}

const std::vector<std::string>&	KanaTable::getRomajiByID(const eKana kana) const
{
	return (this->_romaji[kana]);
}

const sf::Texture&		KanaTable::getTextureByID(const eKana kana) const
{
	return (this->_textures[kana]);
}


///Old version of the class, using unicode
//Hiragana symbols
/*const wchar_t Hiragana::_hiragana[eKana::KANA_SIZE] = {
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

//Katakana symbols
const wchar_t Katakana::_katakana[eKana::KANA_SIZE] = {
L'\u30A2', L'\u30A4', L'\u30A6', L'\u30A8', L'\u30AA',	// A, I, U, E, O
L'\u30AB', L'\u30AD', L'\u30AF', L'\u30B1', L'\u30B3',	// KA, KI, KU, KE, KO
L'\u30AC', L'\u30AE', L'\u30B0', L'\u30B2', L'\u30B4',	// GA, GI, GU, GE, GO
L'\u30B5', L'\u30B7', L'\u30B9', L'\u30BB', L'\u30BD',	// SA, SI, SU, SE, SO
L'\u30B6', L'\u30B8', L'\u30BA', L'\u30BC', L'\u30BE',	// ZA, ZI, ZU, ZE, ZO
L'\u30BF', L'\u30C1', L'\u30C4', L'\u30C6', L'\u30C8',	// TA, TI, TU, TE, TO
L'\u30C0', L'\u30C2', L'\u30C5', L'\u30C7', L'\u30C9',	// DA, DI, DU, DE, DO
L'\u30CA', L'\u30CB', L'\u30CC', L'\u30CD', L'\u30CE',	// NA, NI, NU, NE, NO
L'\u30CF', L'\u30D2', L'\u30D5', L'\u30D8', L'\u30DB',	// HA, HI, HU, HE, HO
L'\u30D0', L'\u30D3', L'\u30D6', L'\u30D9', L'\u30DC',	// BA, BI, BU, BE, BO
L'\u30D1', L'\u30D4', L'\u30D7', L'\u30DA', L'\u30DD',	// PA, PI, PU, PE, PO
L'\u30DE', L'\u30DF', L'\u30E0', L'\u30E1', L'\u30E2',	// MA, MI, MU, ME, MO
L'\u30E4', L'\u30E6', L'\u30E8',						// YA, YU, YO
L'\u30E9', L'\u30EA', L'\u30EB', L'\u30EC', L'\u30ED',	// RA, RI, RU, RE, RO
L'\u30EF', L'\u30F2',									// WA, WO
L'\u30F3'												// N
};*/