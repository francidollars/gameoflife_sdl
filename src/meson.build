SRC_FILES=['cellmap.c' , 'sdl_funcs.c' , 'twodim_tree.c' , 'datastructure.c']
HEADER_FILES=['cellmap.h' , 'sdl_funcs.h' , 'datastructure.h']

sdl_dep = dependency('SDL2')

executable(
	meson.project_name(),
	files('main.c', SRC_FILES),
	dependencies : [sdl_dep],
	install : true
)
	
