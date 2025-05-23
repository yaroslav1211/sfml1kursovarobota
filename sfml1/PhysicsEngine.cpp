#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(Player* player, std::vector<Platform*>& platforms)
    : m_player(player), m_platforms(platforms)
{

}

void PhysicsEngine::update(float dt)
{
    const float EPSILON = 10.0f;

    for (Platform* platform : m_platforms)
    {
        const sf::FloatRect bottomBox = platform->getBoundingBox();
        const sf::FloatRect topBox = m_player->getBoundingBox();

        // Check if the bottom of topSprite is close to the top of bottomSprite
        const bool verticalAlignment = std::fabs((topBox.position.y + topBox.size.y) - bottomBox.position.y) < EPSILON;

        // Check if there is horizontal overlap
        const bool horizontalOverlap =
            (topBox.position.x < (bottomBox.position.x + bottomBox.size.x)) &&
            ((topBox.position.x + topBox.size.x) > bottomBox.position.x);

        if (verticalAlignment && horizontalOverlap)
        {
            m_player->onCollision(platform);
            platform->onCollision(m_player);
        }
    }
}