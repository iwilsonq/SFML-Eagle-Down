#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"


class Entity : public SceneNode
{
	public:
        explicit            Entity(int hitpoints);
    
        void                repair(int points);
        void                damage(int points);
        void                destroy();
        virtual void		remove();
        int                 getHitpoints() const;
        void				setHitpoints(int points);
        virtual bool        isDestroyed() const;
    
    
		void				setVelocity(sf::Vector2f velocity);
		void				setVelocity(float vx, float vy);
        void				accelerate(sf::Vector2f velocity);
        void				accelerate(float vx, float vy);
		sf::Vector2f		getVelocity() const;


    protected:
        virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);
    
	private:
        int                 mHitpoints;
		sf::Vector2f		mVelocity;
};

#endif // ENTITY_HPP
