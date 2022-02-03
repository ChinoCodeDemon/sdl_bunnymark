project('sdl_bunnymark', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'default_library=static'])


libs = [dependency('sdl2'), dependency('SDL2_image'), dependency('SDL2_ttf')]

src = ['sdl_bunnymark.cpp', 'Window.cpp', 'Bunny.cpp']

exe = executable('sdl_bunnymark', src,
  install : true,
  dependencies: libs,
  win_subsystem: 'windows')

test('basic', exe)
