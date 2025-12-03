project('jikan', 'c',
  version : '0.1.0',
  default_options : [
    'c_std=c11',
    'warning_level=3',
    'werror=true'
  ]
)

cc = meson.get_compiler('c')
compiler_name = cc.get_id()
compiler_version = cc.version()

conf_data = configuration_data()
conf_data.set('CC', '@0@ @1@'.format(compiler_name, compiler_version))

configure_file(
  input : 'config.h.in',
  output : 'config.h',
  configuration : conf_data,
  format : 'meson'
)

sources = files('src/main.c')
inc_dirs = include_directories('.')

base_args = [
	'-Wno-poison-system-directories'
]
link_args = []

if compiler_name == 'clang'
  base_args += ['-Weverything', '-ferror-limit=100']
elif compiler_name == 'gcc'
  base_args += ['-Wall', '-Wextra', '-Wpedantic']
  if host_machine.system() == 'windows'
    base_args += ['-Wno-unknown-pragmas']
  endif
elif compiler_name == 'msvc'
  base_args += ['/W4', '/WX']
endif

if host_machine.system() == 'windows'
  add_project_arguments('-D_GNU_SOURCE', '-DMINGW', language : 'c')
  link_args += ['-lshlwapi']
endif

debug_args = base_args + ['-g', '-O0', '-DDEBUG']
release_args = base_args + ['-O3', '-DNDEBUG']

jikan_debug = executable('jikan-debug',
  sources,
  include_directories : inc_dirs,
  c_args : debug_args,
  link_args : link_args,
  build_by_default : false,
  install : false
)

jikan_release = executable('jikan-release',
  sources,
  include_directories : inc_dirs,
  c_args : release_args,
  link_args : link_args,
  build_by_default : true,
  install : true
)

if not meson.is_cross_build()
  run_target('run-debug',  command : jikan_debug,  depends : jikan_debug)
  run_target('run-release',command : jikan_release,depends : jikan_release)
endif

