#include "test.h"
    
class TextTest : public Test
    {
        public:
        TextTest() { } //do nothing, no scene yet
    
        void Step(Settings& settings) override
        {
            //run the default physics and rendering
            Test::Step(settings); 
    
            //show some text in the main screen
            g_debugDraw.DrawString(5, m_textLine, "Test printing");
            m_textLine += 15;
        }
    
        static Test* Create()
        {
            return new TextTest;
        }
    };
static int testIndex = RegisterTest("Stacking", "TextTest", TextTest::Create);