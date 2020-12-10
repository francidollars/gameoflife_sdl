project('gameoflife_sdl2', 'c', 
          version: '0.1.0',
    meson_version: '>= 0.50.0',
  default_options: [ 'warning_level=2',
                     'c_std=gnu11',
                   ],
)

# Variables tracking sources and libraries
library_path = [] # Used to set library path to external dependencies
project_sources = []
project_header_files = [] # Currently unused

inc = [include_directories('include')]

subdir('include')
subdir('external')

# This triggers the builds of sources
subdir('src')
# This links all the static libs into the main source file to form a binary

project_gol_deps = [
  dependency('SDL2'),
  dependency('SDL2_ttf'),
]

executable(
	meson.project_name(),
	project_sources,
	include_directories : inc,
	dependencies : project_gol_deps,
	install : true
)

