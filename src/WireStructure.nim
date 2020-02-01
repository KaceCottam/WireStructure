# This is just an example to get you started. A typical binary package
# uses this file as the main entry point of the application.
import sdl2 as sdl
from system import quit

template sdlError(message: string): untyped =
  echo "SDL_ERROR> ", message, ": ", sdl.getError()
  sdlQuit(1)

proc sdlQuit(errorCode: uint = 0) {.inline.} =
  sdl.quit()
  system.quit()

const
  WindowPos: tuple[x, y: cint] = (x: sdl.SDL_WINDOWPOS_UNDEFINED, y: sdl.SDL_WINDOWPOS_UNDEFINED)
  ScreenSize: tuple[w, h: cint] = (w: 800.cint, h: 600.cint)

proc main() =
  echo "Starting SDL2..."
  var
    window: sdl.WindowPtr
    renderer: sdl.RendererPtr

  if sdl.init(sdl.INIT_VIDEO).toBool == false:
    sdlError"SDL_Init Error"

  window = sdl.createWindow("Hello, world!",
                             WindowPos.x, WindowPos.y,
                             ScreenSize.w, ScreenSize.h,
                             sdl.SDL_WINDOW_SHOWN)

  if window == nil:
    sdlError"SDL_CreateWindow Error"

  renderer = sdl.createRenderer(window, -1, 0)
  if renderer == nil:
    window.destroyWindow()
    sdlError"SDL_CreateRenderer Error"

  var e: sdl.Event
  var shouldQuit: bool = false
  while not shouldQuit:
    while sdl.pollEvent(e):
      case e.kind
      of QuitEvent: shouldQuit = true
      of KeyDown: shouldQuit = true
      of MouseButtonDown: shouldQuit = true
      else: discard
      renderer.clear()
      renderer.present()

  renderer.destroyRenderer()
  window.destroyWindow()
  sdlQuit()


when isMainModule:
  main()
