#include "test.h"
#include <iostream>
    
class Bodies : public Test
    {

public:
        Bodies() 
        { 
            b2BodyDef myBodyDef;
            myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
            myBodyDef.position.Set(0, 20); //set the starting position
            myBodyDef.angle = 0; //set the starting angle

            b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

            b2PolygonShape boxShape;
            boxShape.SetAsBox(1,1);

            b2FixtureDef boxFixtureDef;
            boxFixtureDef.shape = &boxShape;
            boxFixtureDef.density = 1;
            dynamicBody->CreateFixture(&boxFixtureDef);

            dynamicBody->SetTransform( b2Vec2( 10, 20 ), 1 );
            #define DEGTORAD 0.0174532925199432957f
            #define RADTODEG 57.295779513082320876f

            dynamicBody->SetTransform( b2Vec2( 10, 20 ), 45 * DEGTORAD ); //45 degrees counter-clockwis

            dynamicBody->SetLinearVelocity( b2Vec2( -5, 5 ) ); //moving up and left 5 units per second
            dynamicBody->SetAngularVelocity( -90 * DEGTORAD ); //90 degrees per second clockwise

            myBodyDef.type = b2_staticBody; //this will be a static body
            myBodyDef.position.Set(0, 10); //slightly lower position
            b2Body* staticBody = m_world->CreateBody(&myBodyDef); //add body to world
            staticBody->CreateFixture(&boxFixtureDef); //add fixture to body

            myBodyDef.type = b2_kinematicBody; //this will be a kinematic body
            myBodyDef.position.Set(-18, 11); // start from left side, slightly above the static body
            b2Body* kinematicBody = m_world->CreateBody(&myBodyDef); //add body to world
            kinematicBody->CreateFixture(&boxFixtureDef); //add fixture to body

            kinematicBody->SetLinearVelocity( b2Vec2( 4.5, 0 ) ); //move right 1 unit per second
            kinematicBody->SetAngularVelocity( 360 * DEGTORAD ); //1 turn per second counter-clockwis

            for ( b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
            {
                std::cout << b->GetType() << std::endl;
            }
        } 
    
        void Step(Settings& settings) override
        {
            //run the default physics and rendering
            Test::Step(settings); 
    
            //show some text in the main screen
            g_debugDraw.DrawString(5, m_textLine, "Bodies");
            m_textLine += 15;

            b2Body* dynamicBody;
            b2Vec2 pos = dynamicBody->GetPosition();
            float angle = dynamicBody->GetAngle();
            b2Vec2 vel = dynamicBody->GetLinearVelocity();
            float angularVel = dynamicBody->GetAngularVelocity();
            g_debugDraw.DrawString(5, m_textLine, 
              "Position:%.3f,%.3f Angle:%.3f", pos.x, pos.y, angle * RADTODEG);
            m_textLine += 15;
            g_debugDraw.DrawString(5, m_textLine, 
              "Velocity:%.3f,%.3f Angular velocity:%.3f", vel.x, vel.y, angularVel * RADTODEG);
            m_textLine += 15;


        }
    
        static Test* Create()
        {
            return new Bodies;
        }
    };
static int testIndex = RegisterTest("Tutorial", "Bodies", Bodies::Create);