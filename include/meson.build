config_h = configuration_data()
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
configure_file(
  output: 'gameoflife_sdl2-config.h',
  configuration: config_h,
)

project_header_files = files('sdl_funcs.h', 'SDL_FontCache.h', 'datastructure.h', 'cellmap.h', 'twodim_tree.h')

