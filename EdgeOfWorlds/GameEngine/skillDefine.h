/**
* //////  skillDefine.h  //////
*
* Ce fichier constient la classe Character, classe principale de la gestion arrière du jeu.
*
* \author Cossec Estéban
*
*/

#pragma once
/// Décrit la zone ciblée par une attaque
enum SkillRange{
	R_AREA,
	R_TEAM,
	R_OTHERS,
	R_ALL
};

/// décrit les personnages ciblés par une attaque
enum TargetTeam {
	T_ALLY,
	T_ENEMY,
	T_BOTH,
	T_SELF,
};

/// troisième dimention nécessaire à la particularité du jeu
/// détermine sur quel plan agit l'attaque
enum EdgeSide {
	S_MEDIEVAL,
	S_TECH,
	S_BOTH,
	S_EITHER,
	S_SAME,
	S_OTHER
};