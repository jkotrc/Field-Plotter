#include "scene.h"
#include <gtest/gtest.h>

/*
** Tests for the scene object. This object
** should (for now) live on its own screen
** until tabbing capabilities are implemented.
** It can host drawable objects, being given a linear
** endomorphism over the graphical space for
** camera controls.
*/

class SceneTest : public testing::Test {
    public:
        Scene* scene;
        virtual void SetUp() {
            Scene::Configuration options;
            options.projectionMatrix = matrices
            scene = new Scene(/*Scene::Configuration const&*/ options);
        }
};
