# Sample 2: BasicPushConstants

This sample introduces a simple Scene that uses Vulkan Push Constants.

[src/pushconst/pushconst.cxx]

As before, we first create a Phoenix object.  This time, we pass a Scene.  This
Scene (`DefaultScenes::pushconstants`) supplies the shader resource IDs and draw
encoder for the Renderer.

This sample also demonstrates the use of `VKRenderer::Metrics`.
