using org.ogre;

namespace CitySim.Workarounds {
    public class FLRedirect : FrameListener, IFrameListener {
        private readonly IFrameListener frameListener;
        public FLRedirect(IFrameListener frameListener) {
            this.frameListener = frameListener;
        }

        public override bool frameEnded(FrameEvent evt) =>
            this.frameListener.frameEnded(evt);
        
        public override bool frameRenderingQueued(FrameEvent evt) =>
            this.frameListener.frameRenderingQueued(evt);

        public override bool frameStarted(FrameEvent evt) =>
            this.frameListener.frameStarted(evt);
    }
}
