using System;
using org.ogre;

namespace CitySim
{


    public class KeyListener : InputListener
    {
        ApplicationContext ctx;

        public KeyListener(ApplicationContext ctx)
        {
            this.ctx = ctx;
        }

        public override bool keyPressed(KeyboardEvent evt)
        {
            if (evt.keysym.sym == 27)
                ctx.getRoot().queueEndRendering();
            return true;
        }
    }

    public class Example : ApplicationContext
    {
        InputListener listener;

        public Example()
        {
            listener = new KeyListener(this);
        }

        public override void setup()
        {
            base.setup();
            addInputListener(listener);

            var root = getRoot();
            var scnMgr = root.createSceneManager();

            var shadergen = ShaderGenerator.getSingleton();
            shadergen.addSceneManager(scnMgr); // must be done before we do anything with the scene

            scnMgr.setAmbientLight(new ColourValue(.1f, .1f, .1f));

            var light = scnMgr.createLight("MainLight");
            var lightnode = scnMgr.getRootSceneNode().createChildSceneNode();
            lightnode.setPosition(0f, 10f, 15f);
            lightnode.attachObject(light);
            Camera cam = CreateCamera(scnMgr);

            var vp = getRenderWindow().addViewport(cam);
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

        private Camera CreateCamera(SceneManager scnMgr)
        {
            var cam = scnMgr.createCamera("myCam");
            cam.setAutoAspectRatio(true);
            cam.setNearClipDistance(5);
            cam.setFarClipDistance(0);
            var camnode = scnMgr.getRootSceneNode().createChildSceneNode();
            camnode.attachObject(cam);

            var camman = new CameraMan(camnode);
            camman.setStyle(CameraStyle.CS_ORBIT);
            camman.setYawPitchDist(new Radian(0), new Radian(0.3f), 15f);
            addInputListener(camman);
            return cam;
        }

        static void Main()
        {
            Console.WriteLine(Environment.CurrentDirectory);
            var app = new Example();
            app.initApp();
            app.getRoot().startRendering();
            app.closeApp();
        }
    }
}