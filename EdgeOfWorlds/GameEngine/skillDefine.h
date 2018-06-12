/**
* //////  skillDefine.h  //////
*
* Ce fichier constient la classe Character, classe principale de la gestion arri�re du jeu.
*
* \author Cossec Est�ban
*
*/

#pragma once
/// D�crit la zone cibl�e par une attaque
enum SkillRange{
	R_AREA,
	R_TEAM,
	R_OTHERS,
	R_ALL
};

/// d�crit les personnages cibl�s par une attaque
enum TargetTeam {
	T_ALLY,
	T_ENEMY,
	T_BOTH,
	T_SELF,
};

/// troisi�me dimention n�cessaire � la particularit� du jeu
/// d�termine sur quel plan agit l'attaque
enum EdgeSide {
	S_MEDIEVAL,
	S_TECH,
	S_BOTH,
	S_EITHER,
	S_SAME,
	S_OTHER
};