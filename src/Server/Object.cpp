//
// Object.cpp for  in /home/berger_t//CodeA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Sun Oct 28 12:04:50 2012 thierry berger
// Last update Sun Oct 28 12:13:46 2012 thierry berger
//

#include "Object.hpp"

GameData::Physics Server::Object::getPhysics() const
{
  GameData::Physics physics;
  b2Vec2 position = _body->GetPosition();
  physics.x = position.x;
  physics.y = position.y;

  /// assuming that shapes are polygons (real simple, center 0;0 is x;y)
  const b2PolygonShape* shape = static_cast<const b2PolygonShape*>(_body->GetFixtureList()->GetShape());
  for (int i = 0; i < shape->GetVertexCount(); ++i)
    {
      b2Vec2 vertice = shape->GetVertex(i);

      physics.vertices.push_back(GameData::Physics::Coord(vertice.x, vertice.y));
    }
  physics.angle = _body->GetAngle() * 57.2957795;
  physics.angle = (int)physics.angle % (int)360;
  physics.angle = physics.angle  < 0 ? -physics.angle : physics.angle;
  return physics;
}
