/**
  * //////  Character.h  //////
  * 
  * Ce fichier constient la classe Character, classe principale de la gestion arri�re du jeu.
  *
  * \author Cossec Est�ban
  *
  */

#pragma once
#include <vector>
#include <memory>
#include "PersoDefines.h"
#include "mapDefines.h" 
#include "pugixml.hpp"
#include "Skill.h"
#include "Equipement.h"
#include "Statut.h"
#include "Elements.h"
#include <SFML/Graphics.hpp>

#define NB_SKILLS 4


/**
  * \class Character
  *
  * Repr�sente les personnages du jeu. Les personnages sont d�crits tel que suit :
  *
  * - Un nom
  * - Un niveau (still useless)
  * - des HP actuels
  * - Des statistiques de base, qui sont les statistiques du personnage sans equipement ou modifications
  * - Des statistiques mises � jour
  * - Des faiblesses �l�mentaires de base, sans equipement 
  * - Des faiblesses �l�mentaires mises � jour
  * - Des �quipements
  * - Des comp�tences
  * - Des alt�rations d'�tat (Statut)
  *
  *
  */
class Character
{
public:

	/// \enum Team
	/// d�crit l'�quipe dans laquelle le personnage est
	enum Team {
		RED,
		BLUE
	};

	/// pas de personnage vide
	Character() = delete;

	/// Ce constructeur prend en argument un noeud XML. L'architecture de ce noeud est d�crit dans Player.xml
	Character( pugi::xml_node );

	/// Fonction de gestion apr�s s'�tre fait attaquer
	void  getHit(int const);
	/// Fonction de gestion d'une attaque sur un autre parsonnage
	void  hit(int const& , Character* );

	/// Fonction permettant d'apprendre une comp�tence � un personnage
	void setSkill( int, pugi::xml_node& );
	/// Fonction permettant de faire porter un �quipement � un personnage
	void addEquipement(pugi::xml_node&);
	/// Fonction permettant d'appliquer une alt�ration d'�tat � un personnage
	void addStatut(Statut);

	/// Fonction d'assignation de son �quipe � un personnage
	void setTeam(Team t) { m_team = t; };

	/// Les trois fonctions ci-dessous contiennest les mises � jour � faire respectivement
	/// � la mort du personnage, lorsqu'il se fait frapper et � la fin d'un tour.
	/// A la diff�rence de getHit, elles contiennent des �l�ments graphiques
	void onDeath();
	void onHit() {};
	void onTurnEnd();

	/// Accesseurs directs
	Stats const & getStats() const;
	Stats const & getBaseStats() const;
	std::string const & getName() const;
	Skill const * getSkill(int) const;	///< Le pointeur renvoy� doit servir � l'observation uniquement.

	Armor const * getArmor() const { return m_armor.get(); };
	Weapon const * getWeapon() const { return m_weapon.get(); };
	Equipement const * getMiscEquipement() const { return m_miscEquipement.get(); };

	int const & getHP() const;
	std::vector<std::unique_ptr<Statut>> const & getActiveStatuts() const;
	int const getIncreaseness(Element) const;   /// retourne les forces �l�mentaire i.e. les �l�ments am�lior�s par l'�quipement.
	int const getWeakness(Element e) const { return m_weaknesses[e]; };
	Team const & getTeam() const { return m_team; };
	bool isDead() const { return m_dead; };

protected:
	/// Fonction de travail permettant de mettre � jour les statistiques du personnage apr�s une modification
	void updateStats();

protected:
	std::string m_name;	///< le nom du personnage
	int m_level;	///< son niveau (still useless)
	int m_actualHP;	///< ses HP actuels
	/// Les skills : stoqu�s sous forme de pointeurs car peuvent ne pas exister.
	/// Cap�s � 4, avec les deux repr�sentant les attaques de base
	std::unique_ptr<Skill> m_skills[NB_SKILLS +2]; // nb skills + 2 base attck
	/// les �quipements, cap�s � 3 : 1 armure, 1 arme, 1 divers. Peuvent ne pas exister
	std::unique_ptr<Equipement> m_miscEquipement;
	std::unique_ptr<Weapon> m_weapon;
	std::unique_ptr<Armor> m_armor;

	/// Les alt�rations d'�tat du personnage. Une fois d�pass�s, il sont supprim�s.
	std::vector<std::unique_ptr<Statut>> m_activeStatuts;
	Stats m_stats;	///< les stats � jour du personnage
	Stats m_baseStats;	///< les stats de base
	/// Les faiblesses �l�mentaires du personnages, indent�s sur l'�l�ement concern�
	Weakness m_weaknesses[NB_ELEMENTS];
	/// Les faiblesses �l�mentaires de base
	Weakness m_baseWeaknesses[NB_ELEMENTS];
	/// L'�quipe du personnage
	Team m_team = RED;
	/// compteur v�rifiant la mort du personnage.
	bool m_dead = false;

	//////// Gestion de alt�rations d'�tat ////////

private:
	/// applique une alt�ration d'�tat dans le tableau m_activeStatut
	void applyUniqueStatut(int i);

	/// liste des effets possibles pour une alt�ration d'�tat
	void effect(int) {};
	void poison(int);
	void weak(int);
	void brittle(int);
	void mute(int);
	void slow(int);
	void softHeal(int);
	void strong(int);
	void unbreakable(int);
	void quick(int);
	void freeze(int);

	//////// Graphic Management ////////
private:
	/// Elements d'affichages de la SFML : le Sprite et la texture associ�e.
	/// Il y a deux sprites possibles, selon le c�t� de la map o� le personnage est.
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Sprite m_spriteGohst;
	sf::Texture m_textureGohst;
	/// compteurs de gestion des animations : on compte la ligne et la colone sur le set
	int m_animationLine = 8; int m_animationIterator = 0;
	/// tailles d'un sprite, calcul�es une fois seulement.
	int m_spriteWidth, m_spriteHeight;

public:
	/// fonctions d'affichage des sprites respectifs
	void draw(sf::RenderTarget & t);
	void drawGohst(sf::RenderTarget & t);
	/// setter de la position du sprite sur la cible de rendu
	void setPosition(sf::Vector2f v);
	/// initialisateur de la texture, � appeler avant toute tentative d'affichage. 
	/// Un unique appel par personnage est n�cessaire
	void setTexture();
	/// fonction de mise � jour graphique � appeler � chaque frame
	void update();
	/// animation de d�placement de 1 case (useless car pas encore de pathfinding)
	void move(Direction);
	/// animation de frappe
	void HitAnimation(Direction);
	/// animation de mort
	void die();
	/// change la direction du personnage
	void changeDirection(Direction);
};
