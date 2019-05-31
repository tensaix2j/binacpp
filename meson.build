project('binacpp', 'cpp', version : '0.1')

SRCDIR = 'src/'
src = [
	SRCDIR + 'binacpp.cpp',
	SRCDIR + 'binacpp_logger.cpp',
	SRCDIR + 'binacpp_utils.cpp',
	SRCDIR + 'binacpp_websocket.cpp'
]

include_dir = include_directories('src/')

thread_dep = dependency('threads')
curl_dep = dependency('libcurl')
websocket_dep = dependency('libwebsockets')
openssl_dep = dependency('openssl')
jsoncpp_dep = dependency('jsoncpp')

cppargs = [
  '-Wall',
  '-Wextra'
]

binacpp_lib = shared_library('binacpp',
  sources : src,
  cpp_args : cppargs,
  dependencies : [thread_dep, curl_dep, websocket_dep, openssl_dep, jsoncpp_dep],
  # cpp_pch : 'pch/cpp_pch.h'
)

binacpp_dep = declare_dependency(include_directories : include_dir, link_with : binacpp_lib)