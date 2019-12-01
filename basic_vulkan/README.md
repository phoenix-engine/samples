# Sample 1: BasicVulkan

Sections:
- [Phoenix Setup](#phoenix-setup)
- [Game Loop](#game-loop)

## Phoenix setup

[src/main.cxx](src/main.cxx)

This sample introduces the Window, Renderer, Graphics, Input, and Phoenix types.

Window and Renderer are system-specific.  Graphics, Input, and Phoenix are
generic wrappers for system-specific types.  That way, the same game logic will
be able to run on whatever system you like.

When you build a Phoenix object, you must plug in a Graphics and Input object.
These may be customized by you, or you may use existing ones.  You can even use
mock or debugger-enabled ones for testing purposes.

### Code

We launch the game thread, and then we begin to run the Input polling loop.
This continually pumps input events into the engine.

Once the `poll` loop returns (when the user indicates they would like to quit),
we will exit the program.

## Game Loop

[src/sample/sample.cxx](src/sample/sample.cxx)

First, we launch the render thread.  In this thread, we first try to `render`,
and if it fails we attempt to recover, or we log a failure message to tell the
user what happened.  We keep doing that as frequently as possible until the game
is over.

Then, we enter a blocking loop, awaiting the next input event, and checking
whether it means that the user wanted to quit.  Notice that the input event is
not a keyboard or mouse event, but rather a special Phoenix event type
indicating some _intent_.  Intentions are "parsed" from the user behavior
internally to the Input type.  

Notice that we always call Phoenix methods and functions ourselves, so we will
be in control of the events that happen.  This means that nothing unexpected
will happen, but it also means that we always need to start and manage our own
event loops.
