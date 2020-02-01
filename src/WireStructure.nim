# This is just an example to get you started. A typical binary package
# uses this file as the main entry point of the application.
import sdl2 as sdl

template sdlError(message: string): untyped =
  echo "SDL_ERROR> ", message, ": ", sdl.getError()
  sdl.quit()

const
  WindowPos: tuple[x, y: cint] = (x: sdl.SDL_WINDOWPOS_UNDEFINED, y: sdl.SDL_WINDOWPOS_UNDEFINED)
  ScreenSize: tuple[w, h: cint] = (w: 800.cint, h: 600.cint)

proc main() =
  var
    window: sdl.WindowPtr

  if sdl.init(sdl.INIT_VIDEO).toBool == false:
    sdlError"SDL_Init Error"

  window = sdl.createWindow("Hello, world!",
                             WindowPos.x, WindowPos.y,
                             ScreenSize.w, ScreenSize.h,
                             sdl.SDL_WINDOW_SHOWN)

  if window == nil:
    sdlError"SDL_CreateWindow Error"


when isMainModule:
  main()
