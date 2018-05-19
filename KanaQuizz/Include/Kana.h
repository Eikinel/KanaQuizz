#pragma once

#include "Constants.h"

enum	eKana
{
	A, I, U, E, O,
	KA, KI, KU, KE, KO,
	GA, GI, GU, GE, GO,
	SA, SI, SU, SE, SO,
	ZA, ZI, ZU, ZE, ZO,
	TA, TI, TU, TE, TO,
	DA, DI, DU, DE, DO,
	NA, NI, NU, NE, NO,
	HA, HI, HU, HE, HO,
	BA, BI, BU, BE, BO,
	PA, PI, PU, PE, PO,
	MA, MI, MU, ME, MO,
	YA, YU, YO,
	RA, RI, RU, RE, RO,
	WA, WO,
	N,
	KANA_SIZE
};

enum	eKanaType
{
	HIRAGANA,
	KATAKANA,
	SIZE_KANA_TYPE
};

class	IKana
{
public:
	//GETTERS
	static const wchar_t&		kana(const eKana kana, const eKanaType type);
	static const wchar_t*		allKanaByType(const eKanaType type);
	static const std::string*	toRomaji(const eKana kana, const eKanaType type);
	static const std::string*	toRomajiUppercase(const std::string romaji[MAX_ROMAJI]);

	static const std::string	_romaji[eKana::KANA_SIZE][MAX_ROMAJI];
};

class	Hiragana : public IKana
{
public:
	static const wchar_t	_hiragana[eKana::KANA_SIZE];
};

class	Katakana : public IKana
{
public:
	static const wchar_t	_katakana[eKana::KANA_SIZE];
};