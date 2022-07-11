using org.ogre;

namespace CitySim.Workarounds {
    public interface IFrameListener {
        bool frameEnded(FrameEvent evt);
        bool frameRenderingQueued(FrameEvent evt);
        bool frameStarted(FrameEvent evt);
    }
}
