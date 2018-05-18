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

class	IKana
{
public:
	//GETTERS
	//Probably needs a change
	static const wchar_t&	kana(const eKana kana);
	static const wchar_t*	allKana();
	static const char**		toRomaji(const eKana kana);

	static const wchar_t	_kana[eKana::KANA_SIZE];
	static const char*		_romaji[eKana::KANA_SIZE][MAX_ROMAJI];
};

class	Hiragana : public IKana
{
};