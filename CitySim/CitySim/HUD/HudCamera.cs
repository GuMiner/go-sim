using CitySim.Config;
using CitySim.Workarounds;
using org.ogre;
using System.Collections.Generic;

namespace CitySim.HUD {
    public class HudCamera : InputListener, IFrameListener {
        public readonly SceneNode cameraNode;

        private static HashSet<int> hudKeys = new HashSet<int>()
        {
            Keymap.MoveLeft, Keymap.MoveRight, Keymap.MoveUp, Keymap.MoveDown, Keymap.MoveForward, Keymap.MoveBackward,
            Keymap.RotateClockwise, Keymap.RotateCounterClockwise, Keymap.RotateLeft, Keymap.RotateRight, Keymap.RotateUp, Keymap.RotateDown
        };

        private HashSet<int> pressedKeys = new HashSet<int>();

        public HudCamera(SceneManager sceneManager) {
            Camera = sceneManager.createCamera("HUD");
            Camera.setAutoAspectRatio(true);
            Camera.setNearClipDistance(5); // TODO configurable?
            Camera.setFarClipDistance(0);

            cameraNode = sceneManager.getRootSceneNode().createChildSceneNode();
            cameraNode.attachObject(Camera);
            cameraNode.setPosition(0, 5, 10);
        }

        public Camera Camera { get; }

        public override bool keyPressed(KeyboardEvent evt) {
            if (hudKeys.Contains(evt.keysym.sym)) {
                pressedKeys.Add(evt.keysym.sym);
                return true;
            }

            return false;
        }

        public override bool keyReleased(KeyboardEvent evt) {
            if (hudKeys.Contains(evt.keysym.sym)) {
                pressedKeys.Remove(evt.keysym.sym);
                return true;
            }

            return false;
        }

        public bool frameEnded(FrameEvent evt) {
            // throw new System.NotImplementedException();
            return true;
        }

        public bool frameRenderingQueued(FrameEvent evt) {
            Vector3 movement = new Vector3(0.0f, 0.0f, 0.0f);
            Quaternion rotation = Quaternion.IDENTITY;
            bool translated = false;
            bool rotated = false;
            foreach (int key in pressedKeys) {
                if (key == Keymap.MoveLeft) { movement -= Camera.getRealRight(); translated = true; }
                if (key == Keymap.MoveRight) { movement += Camera.getRealRight(); translated = true; }
                if (key == Keymap.MoveUp) { movement += Camera.getRealUp(); translated = true; }
                if (key == Keymap.MoveDown) { movement -= Camera.getRealUp(); translated = true; }
                if (key == Keymap.MoveForward) { movement += Camera.getRealDirection(); translated = true; }
                if (key == Keymap.MoveBackward) { movement -= Camera.getRealDirection(); translated = true; }
                if (key == Keymap.RotateClockwise) { rotation = rotation.__mul__(new Quaternion(new Radian(CameraConfig.RotateRollSpeed), Camera.getRealDirection())); rotated = true; }
                if (key == Keymap.RotateCounterClockwise) { rotation = rotation.__mul__(new Quaternion(new Radian(-CameraConfig.RotateRollSpeed), Camera.getRealDirection())); rotated = true; }
                if (key == Keymap.RotateLeft) { rotation = rotation.__mul__(new Quaternion(new Radian(-CameraConfig.RotateSidewaysSpeed), Camera.getRealUp())); rotated = true; }
                if (key == Keymap.RotateRight) { rotation = rotation.__mul__(new Quaternion(new Radian(CameraConfig.RotateSidewaysSpeed), Camera.getRealUp())); rotated = true; }
                if (key == Keymap.RotateUp) { rotation = rotation.__mul__(new Quaternion(new Radian(-CameraConfig.RotateUpSpeed), Camera.getRealRight())); rotated = true; }
                if (key == Keymap.RotateDown) { rotation = rotation.__mul__(new Quaternion(new Radian(CameraConfig.RotateUpSpeed), Camera.getRealRight())); rotated = true; }
            }

            // TODO scaling by frame rate has weird effects on rotation. 
            // Possibly zeroing the quaternion / movement?
            movement.normalise();
            if (translated) {
                cameraNode.translate(movement.__mul__(CameraConfig.MovementSpeed));
            }

            if (rotated) {
                cameraNode.rotate(rotation, Node.TransformSpace.TS_WORLD);
            }

            return true;
        }

        public bool frameStarted(FrameEvent evt) {
            // throw new System.NotImplementedException();
            return true;
        }
    }
}
