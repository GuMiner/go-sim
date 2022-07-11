using System;
using CitySim.HUD;
using CitySim.Workarounds;
using org.ogre;

namespace CitySim {
    public class KeyListener : InputListener {
        private readonly Action stopRendering;
        public KeyListener(Action stopRendering) {
            this.stopRendering = stopRendering;
        }

        public override bool keyPressed(KeyboardEvent evt) {
            if (evt.keysym.sym == 27) {
                stopRendering();
            }
            return true;
        }
    }

    public class Example : ApplicationContext {
        public override void setup() {
            base.setup();

            var root = getRoot();
            this.addInputListener(new KeyListener(() => root.queueEndRendering()));

            var scnMgr = root.createSceneManager();

            var shadergen = ShaderGenerator.getSingleton();
            shadergen.addSceneManager(scnMgr); // must be done before we do anything with the scene

            scnMgr.setAmbientLight(new ColourValue(.1f, .1f, .1f));

            var light = scnMgr.createLight("MainLight");
            var lightnode = scnMgr.getRootSceneNode().createChildSceneNode();
            lightnode.setPosition(0f, 10f, 15f);
            lightnode.attachObject(light);

            HudCamera cam = new HudCamera(scnMgr);
            this.addInputListener(cam);
            root.addFrameListener(new FLRedirect(cam));

            var vp = getRenderWindow().addViewport(cam.Camera);
            vp.setBackgroundColour(new ColourValue(.3f, .3f, .3f));

            var ent = scnMgr.createEntity(@"Sinbad.mesh");

            //TerrainGlobalOptions.getSingleton().
            //TerrainGroup(scnMgr, Terrain.Alignment.ALIGN_X_Z)
            Plane plain = new Plane(new Vector3(0, 1, 0), 0);
            var plane = MeshManager.getSingleton().createPlane("GroundPlane", ResourceGroupManager.DEFAULT_RESOURCE_GROUP_NAME, plain,
                1400, 1400, 40, 40, true, 1, 4, 4, new Vector3(0, 0, 1));

            Entity groundEntity = scnMgr.createEntity("GroundObject", "GroundPlane");
            groundEntity.setCastShadows(false);
            groundEntity.setMaterialName("Examples/Rockwall");

            scnMgr.setSkyBox(true, "Examples/SpaceSkyBox");

            var node = scnMgr.getRootSceneNode().createChildSceneNode();
            node.attachObject(ent);
            node.attachObject(groundEntity);
        }

        static void Main() {
            Console.WriteLine(Environment.CurrentDirectory);
            var app = new Example();
            app.initApp();
            app.getRoot().startRendering();
            app.closeApp();
        }
    }
}