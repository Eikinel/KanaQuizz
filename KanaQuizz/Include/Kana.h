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

class	KanaTable
{
public:
	KanaTable(const eKanaType type);
	~KanaTable();

	//GETTERS
	virtual const eKanaType					getType() const;
	virtual const std::vector<std::string>&	getRomajiByID(const eKana kana) const;
	virtual const sf::Texture&				getTextureByID(const eKana kana) const;

protected:
	const eKanaType							_type;
	std::vector<std::vector<std::string>>	_romaji;
	std::vector<sf::Texture>				_textures;
};

class	Hiragana : public KanaTable
{
public:
	Hiragana();
	~Hiragana() { }
};

class	Katakana : public KanaTable
{
public:
	Katakana();
	~Katakana() {}
};