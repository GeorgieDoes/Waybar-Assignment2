test_inc = include_directories(
    '../../include', 
    '../../src',
    '../../' 
)

custom_test_src = [
    'networkModuleTest.cpp',
    'multimediaTest.cpp',
    'faultToleranceTest.cpp',
    'data/mocks.cpp',

    '../../src/modules/network.cpp',
    '../../src/modules/pulseaudio.cpp',
    '../../src/config.cpp',
    '../../src/util/sanitize_str.cpp',
    '../../src/ALabel.cpp',
    '../../src/AModule.cpp',
    '../../src/util/audio_backend.cpp',
]

custom_test_exe = executable(
    'waybar_custom_suite',
    custom_test_src,
    include_directories: test_inc,
    dependencies: [
        dependency('catch2-with-main', fallback: ['catch2', 'catch2_with_main_dep']), 
        dependency('jsoncpp'), 
        dependency('sigc++-2.0'),
        dependency('libnl-3.0'),
        dependency('libnl-genl-3.0'),
        dependency('libpulse'),
        dependency('gtkmm-3.0'),
        dependency('spdlog'),
        dependency('fmt')
    ],
    cpp_args: [
        '-DTEST_DATA_DIR="' + meson.current_source_dir() + '/data"',
        '-fPIC'
    ]
)

test('Waybar Custom Requirements Suite', custom_test_exe)
