# Sample 2: BasicPushConstants

This sample introduces a simple Scene that uses Vulkan Push Constants.

[src/pushconst/pushconst.cxx]

As before, we first create a Phoenix object.  This time, we pass a Scene to it.
This Scene (`DefaultScenes::pushconstants`) supplies the shader resource IDs and
draw encoder for the Renderer.

In the main loop, this sample demonstrates the use of two new features:
`VKRenderer::Metrics` and `std::visit` across multiple `event_cases`.  This
models how `Event` enum values can be used in the input loop.

The shaders for the `PushConstants` can be seen in the `res` subdirectory of
[Phoenix](https://github.com/phoenix-engine/phoenix).  Review the
[Phoenix developer doc](https://github.com/phoenix-engine/phoenix/blob/dev/doc/developer.md#shaders)
on the topic for more details or to hack on your own shaders.
