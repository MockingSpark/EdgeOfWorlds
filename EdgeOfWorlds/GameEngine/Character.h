/**
  * //////  Character.h  //////
  * 
  * Ce fichier constient la classe Character, classe principale de la gestion arrière du jeu.
  *
  * \author Cossec Estéban
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
  * Représente les personnages du jeu. Les personnages sont décrits tel que suit :
  *
  * - Un nom
  * - Un niveau (still useless)
  * - des HP actuels
  * - Des statistiques de base, qui sont les statistiques du personnage sans equipement ou modifications
  * - Des statistiques mises à jour
  * - Des faiblesses élémentaires de base, sans equipement 
  * - Des faiblesses élémentaires mises à jour
  * - Des équipements
  * - Des compétences
  * - Des altérations d'état (Statut)
  *
  *
  */
class Character
{
public:

	/// \enum Team
	/// décrit l'équipe dans laquelle le personnage est
	enum Team {
		RED,
		BLUE
	};

	/// pas de personnage vide
	Character() = delete;

	/// Ce constructeur prend en argument un noeud XML. L'architecture de ce noeud est décrit dans Player.xml
	Character( pugi::xml_node );

	/// Fonction de gestion après s'être fait attaquer
	void  getHit(int const);
	/// Fonction de gestion d'une attaque sur un autre parsonnage
	void  hit(int const& , Character* );

	/// Fonction permettant d'apprendre une compétence à un personnage
	void setSkill( int, pugi::xml_node& );
	/// Fonction permettant de faire porter un équipement à un personnage
	void addEquipement(pugi::xml_node&);
	/// Fonction permettant d'appliquer une altération d'état à un personnage
	void addStatut(Statut);

	/// Fonction d'assignation de son équipe à un personnage
	void setTeam(Team t) { m_team = t; };

	/// Les trois fonctions ci-dessous contiennest les mises à jour à faire respectivement
	/// à la mort du personnage, lorsqu'il se fait frapper et à la fin d'un tour.
	/// A la différence de getHit, elles contiennent des éléments graphiques
	void onDeath();
	void onHit() {};
	void onTurnEnd();

	/// Accesseurs directs
	Stats const & getStats() const;
	Stats const & getBaseStats() const;
	std::string const & getName() const;
	Skill const * getSkill(int) const;	///< Le pointeur renvoyé doit servir à l'observation uniquement.

	Armor const * getArmor() const { return m_armor.get(); };
	Weapon const * getWeapon() const { return m_weapon.get(); };
	Equipement const * getMiscEquipement() const { return m_miscEquipement.get(); };

	int const & getHP() const;
	std::vector<std::unique_ptr<Statut>> const & getActiveStatuts() const;
	int const getIncreaseness(Element) const;   /// retourne les forces élémentaire i.e. les éléments améliorés par l'équipement.
	int const getWeakness(Element e) const { return m_weaknesses[e]; };
	Team const & getTeam() const { return m_team; };
	bool isDead() const { return m_dead; };

protected:
	/// Fonction de travail permettant de mettre à jour les statistiques du personnage après une modification
	void updateStats();

protected:
	std::string m_name;	///< le nom du personnage
	int m_level;	///< son niveau (still useless)
	int m_actualHP;	///< ses HP actuels
	/// Les skills : stoqués sous forme de pointeurs car peuvent ne pas exister.
	/// Capés à 4, avec les deux représentant les attaques de base
	std::unique_ptr<Skill> m_skills[NB_SKILLS +2]; // nb skills + 2 base attck
	/// les équipements, capés à 3 : 1 armure, 1 arme, 1 divers. Peuvent ne pas exister
	std::unique_ptr<Equipement> m_miscEquipement;
	std::unique_ptr<Weapon> m_weapon;
	std::unique_ptr<Armor> m_armor;

	/// Les altérations d'état du personnage. Une fois dépassés, il sont supprimés.
	std::vector<std::unique_ptr<Statut>> m_activeStatuts;
	Stats m_stats;	///< les stats à jour du personnage
	Stats m_baseStats;	///< les stats de base
	/// Les faiblesses élémentaires du personnages, indentés sur l'éléement concerné
	Weakness m_weaknesses[NB_ELEMENTS];
	/// Les faiblesses élémentaires de base
	Weakness m_baseWeaknesses[NB_ELEMENTS];
	/// L'équipe du personnage
	Team m_team = RED;
	/// compteur vérifiant la mort du personnage.
	bool m_dead = false;

	//////// Gestion de altérations d'état ////////

private:
	/// applique une altération d'état dans le tableau m_activeStatut
	void applyUniqueStatut(int i);

	/// liste des effets possibles pour une altération d'état
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
	/// Elements d'affichages de la SFML : le Sprite et la texture associée.
	/// Il y a deux sprites possibles, selon le côté de la map où le personnage est.
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Sprite m_spriteGohst;
	sf::Texture m_textureGohst;
	/// compteurs de gestion des animations : on compte la ligne et la colone sur le set
	int m_animationLine = 8; int m_animationIterator = 0;
	/// tailles d'un sprite, calculées une fois seulement.
	int m_spriteWidth, m_spriteHeight;

public:
	/// fonctions d'affichage des sprites respectifs
	void draw(sf::RenderTarget & t);
	void drawGohst(sf::RenderTarget & t);
	/// setter de la position du sprite sur la cible de rendu
	void setPosition(sf::Vector2f v);
	/// initialisateur de la texture, à appeler avant toute tentative d'affichage. 
	/// Un unique appel par personnage est nécessaire
	void setTexture();
	/// fonction de mise à jour graphique à appeler à chaque frame
	void update();
	/// animation de déplacement de 1 case (useless car pas encore de pathfinding)
	void move(Direction);
	/// animation de frappe
	void HitAnimation(Direction);
	/// animation de mort
	void die();
	/// change la direction du personnage
	void changeDirection(Direction);
};
