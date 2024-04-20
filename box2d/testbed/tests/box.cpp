#include "test.h"

class Box : public Test
{
public:

    enum
	{
		e_columnCount = 1,
		e_rowCount = 2
		//e_columnCount = 1,
		//e_rowCount = 1
	};

    Box()
    {
        {
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
        float xs[5] = {0.0f, -10.0f, -5.0f, 5.0f, 10.0f};

		for (int32 j = 0; j < e_columnCount; ++j)
		{
			b2PolygonShape shape;
			shape.SetAsBox(2.0f, 2.0f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 1.0f;
			fd.friction = 0.3f;

			for (int i = 0; i < e_rowCount; ++i)
			{
				b2BodyDef bd;
				bd.type = b2_dynamicBody;

				int32 n = j * e_rowCount + i;
				b2Assert(n < e_rowCount * e_columnCount);
				m_indices[n] = n;
				bd.userData.pointer = n;

				//float x = 0.0f;
				//float x = RandomFloat(-5.0f, 5.0f);
				float x = i % 2 == 0 ? -1.1f : 1.1f;
				bd.position.Set(xs[j] + x, 3.0f + 10.0f * i);
				b2Body* body = m_world->CreateBody(&bd);

				m_bodies[n] = body;

				body->CreateFixture(&fd);
			}
		}
    }
    void Step(Settings& settings) override
    {
        Test::Step(settings);
    }
    static Test* Create(){
        return new Box;
    }
    b2Body* m_bodies[e_rowCount * e_columnCount];
    int32 m_indices[e_rowCount * e_columnCount];
};
static int testIndex = RegisterTest("Stacking", "Box", Box::Create);