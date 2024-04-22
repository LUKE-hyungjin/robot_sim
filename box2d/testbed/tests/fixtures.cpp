#include "test.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
    
class Fixtures : public Test
    {

public:
        Fixtures() 
        {   
            //Step1
            // b2BodyDef myBodyDef;
            // myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
            // myBodyDef.position.Set(-10, 20); //set the starting position

            // b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);

            // b2CircleShape circleShape;
            // circleShape.m_p.Set(0, 0); //position, relative to body position
            // circleShape.m_radius = 1; //radius

            // b2FixtureDef myFixtureDef;
            // myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
            // myFixtureDef.density = 1;

            // dynamicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body

            // //Polygon
            // //set each vertex of polygon in an array
            // b2Vec2 vertices[5];
            // vertices[0].Set(-1,  2);
            // vertices[1].Set(-1,  0);
            // vertices[2].Set( 0, -3);
            // vertices[3].Set( 1,  0);
            // vertices[4].Set( 1,  1);

            // b2PolygonShape polygonShape;
            // polygonShape.Set(vertices, 5); //pass array to the shape

            // myBodyDef.position.Set(0, 20); //in the middle
            // b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
            // myFixtureDef.shape = &polygonShape; //change the shape of the fixture
            // dynamicBody2->CreateFixture(&myFixtureDef); //add a fixture to the body

            // //Rectangle
            // polygonShape.SetAsBox(2, 1); //a 4x2 rectangle
            // myBodyDef.position.Set(10,20); //a bit to the right
  
            // b2Body* dynamicBody3 = m_world->CreateBody(&myBodyDef);
            // dynamicBody3->CreateFixture(&myFixtureDef); //add a fixture to the body

            // //Ground
            // myBodyDef.type = b2_staticBody; //change body type
            // myBodyDef.position.Set(0,0); //middle, bottom
            // b2Body* staticBody = m_world->CreateBody(&myBodyDef);

            // b2EdgeShape edgeShape;
            // edgeShape.SetTwoSided( b2Vec2(-15.0f,0.0f), b2Vec2(15.0f,0.0f) ); //ends of the line

            // myFixtureDef.shape = &edgeShape;
            // staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body

            //Step 2
            //set up a dynamic body
            b2BodyDef myBodyDef;
            myBodyDef.type = b2_dynamicBody;
            myBodyDef.position.Set(24, 20); //middle
            b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

            //prepare a shape definition
            b2PolygonShape polygonShape;
            b2FixtureDef myFixtureDef;
            myFixtureDef.shape = &polygonShape;
            myFixtureDef.density = 1;
            myFixtureDef.friction = 1.5; //new code
            myFixtureDef.restitution = 0.7; //new code

            //add four square shaped fixtures around the body center
            for ( int i = 0; i < 4; i++) {
                b2Vec2 pos( sinf(i*90*DEGTORAD), cosf(i*90*DEGTORAD) ); //radial placement
                polygonShape.SetAsBox(1, 1, pos, 0 ); //a 2x2 rectangle
                dynamicBody->CreateFixture(&myFixtureDef); //add a fixture to the body
            }

            //make a static floor to drop things on
            myBodyDef.type = b2_staticBody;
            b2EdgeShape edgeShape;
            myBodyDef.position.Set(0, 0); //middle, bottom
            b2Body* staticBody = m_world->CreateBody(&myBodyDef);  
            edgeShape.SetTwoSided( b2Vec2(-26.0f,0.0f), b2Vec2(25.0f,1.0f) ); 
            myFixtureDef.shape = &edgeShape;            
            staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body
        } 
    
        void Step(Settings& settings) override
        {
            //run the default physics and rendering
            Test::Step(settings); 
    
            //show some text in the main screen
            g_debugDraw.DrawString(5, m_textLine, "Fixtures");
            m_textLine += 15;


        }
    
        static Test* Create()
        {
            return new Fixtures;
        }
    };
static int testIndex = RegisterTest("Tutorial", "Fixtures", Fixtures::Create);