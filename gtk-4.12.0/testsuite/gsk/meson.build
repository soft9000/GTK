compare_render = executable('compare-render',
  ['compare-render.c', '../reftests/reftest-compare.c'],
  dependencies: libgtk_dep,
  c_args: common_cflags,
)

node_parser = executable('node-parser', 'node-parser.c',
  dependencies: libgtk_dep,
  c_args: common_cflags,
)

compare_render_tests = [
  'big-checkerboard',
  'big-checkerboard-scaled-down',
  'big-checkerboard-scaled-down-nearest',
  'big-checkerboard-scaled-down2',
  'blend-difference',
  'blend-modes',
  'blend-invisible-child',
  'blend-in-rotate',
  'blend-normal',
  'border-bottom-right',
  'border-one-rounded',
  'borders-rotated',
  'borders-scaled',
  'clip-coordinates-2d',
  'clip-coordinates-3d',
  'clip-in-rounded-clip1',
  'clip-in-rounded-clip2',
  'clip-in-rounded-clip3',
  'clipped-repeat',
  'clipped_rounded_clip',
  'clip-nested1',
  'clip-translate-offscreen',
  'color-blur0',
  'color-matrix-identity',
  'color-matrix-parsing',
  'crossfade-clip-both-children',
  'cross-fade-in-opacity',
  'cross-fade-in-rotate',
  'css-background',
  'empty-blend',
  'empty-blur',
  'empty-border',
  'empty-cairo',
  'empty-clip',
  'empty-color',
  'empty-color-matrix',
  'empty-container',
  'empty-cross-fade',
  'empty-debug',
  'empty-inset-shadow',
  'empty-linear-gradient',
  'empty-mask',
  'empty-opacity',
  'empty-outset-shadow',
  'empty-repeat',
  'empty-rounded-clip',
  'empty-shadow',
  'empty-texture',
  'empty-transform',
  'huge-height',
  'huge-width',
  'inset-shadow-multiple',
  'invalid-transform',
  'issue-3615',
  'mask',
  'mask-clipped-inverted-alpha',
  'mask-modes',
  'mask-modes-with-alpha',
  'nested-rounded-clips',
  'opacity_clip',
  'opacity-overdraw',
  'opacity-overlapping-children',
  'outset_shadow_offset_both',
  'outset_shadow_offset_x',
  'outset_shadow_offset_y',
  'outset_shadow_rounded_top',
  'outset_shadow_simple',
  'repeat',
  'repeat-no-repeat',
  'repeat-empty-child-bounds',
  'repeat-negative-coords',
  'repeat-texture',
  'repeating-gradient-scaled',
  'scale-textures-negative-ngl',
  'scale-up-down',
  'scaled-cairo',
  'scaled-texture',
  'shadow-in-opacity',
  'texture-scale-magnify-10000x',
  'texture-scale-magnify-rotate',
  'texture-scale-stripes',
  'texture-url',
  'transform-in-transform',
  'transform-in-transform-in-transform',
  'z-transform-clipping-bounds-3d',
]

# these are too sensitive to differences in the renderers
# to run in ci, but still useful to keep around
informative_render_tests = [
  'big-glyph',
  'empty-text',
  'huge-glyph',
  'rounded-clip-in-clip-3d', # both cairo and gl fail this one
]

renderers = [
  { 'name': 'gl' },
  { 'name': 'broadway', 'exclude_term': '-3d' },
  { 'name': 'cairo', 'exclude_term': '-3d' },
]

compare_xfails = [
  # Both tests fail because of some font rendering issue
  'empty-linear-gradient',
  'unaligned-offscreen',
  'upside-down-label-3d', # not really 3d, but cairo fails it
]

compare_xfails_small_texture = [
  'big-checkerboard',
  'big-checkerboard-scaled-down',
  'big-checkerboard-scaled-down2'
]

foreach renderer : renderers
  foreach testname : compare_render_tests

    renderer_name = renderer.get('name')
    exclude_term = renderer.get('exclude_term', '')

    suites = [
      'gsk',
      'gsk-compare',
      'gsk-' + renderer_name,
      'gsk-compare-' + renderer_name,
    ]

    if compare_xfails.contains(testname)
      suites += 'failing'
    endif

    if compare_xfails_small_texture.contains(testname)
      suites += 'wayland_gles_failing'
    endif

    if ((exclude_term == '' or not testname.contains(exclude_term)) and
        (renderer_name != 'broadway' or broadway_enabled))
      test(renderer_name + ' ' + testname, compare_render,
        args: [
          '--output', join_paths(meson.current_build_dir(), 'compare', renderer_name),
          join_paths(meson.current_source_dir(), 'compare', testname + '.node'),
          join_paths(meson.current_source_dir(), 'compare', testname + '.png'),
        ],
        env: [
          'GSK_RENDERER=' + renderer_name,
          'GTK_A11Y=test',
          'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
          'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir())
        ],
        suite: suites,
      )
      test(renderer_name + ' ' + testname + ' flipped', compare_render,
        args: [
          '--flip',
          '--output', join_paths(meson.current_build_dir(), 'compare', renderer_name),
          join_paths(meson.current_source_dir(), 'compare', testname + '.node'),
          join_paths(meson.current_source_dir(), 'compare', testname + '.png'),
        ],
        env: [
          'GSK_RENDERER=' + renderer_name,
          'GTK_A11Y=test',
          'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
          'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir())
        ],
        suite: suites + [ 'gsk-compare-flipped-' + renderer_name ],
      )
      test(renderer_name + ' ' + testname + ' repeated', compare_render,
        args: [
          '--repeat',
          '--output', join_paths(meson.current_build_dir(), 'compare', renderer_name),
          join_paths(meson.current_source_dir(), 'compare', testname + '.node'),
          join_paths(meson.current_source_dir(), 'compare', testname + '.png'),
        ],
        env: [
          'GSK_RENDERER=' + renderer_name,
          'GTK_A11Y=test',
          'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
          'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir())
        ],
        suite: suites + [ 'gsk-compare-repeated-' + renderer_name ],
      )
      test(renderer_name + ' ' + testname + ' rotated', compare_render,
        args: [
          '--rotate',
          '--output', join_paths(meson.current_build_dir(), 'compare', renderer_name),
          join_paths(meson.current_source_dir(), 'compare', testname + '.node'),
          join_paths(meson.current_source_dir(), 'compare', testname + '.png'),
        ],
        env: [
          'GSK_RENDERER=' + renderer_name,
          'GTK_A11Y=test',
          'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
          'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir())
        ],
        suite: suites + [ 'gsk-compare-rotated-' + renderer_name ],
      )
      test(renderer_name + ' ' + testname + ' masked', compare_render,
        args: [
          '--mask',
          '--output', join_paths(meson.current_build_dir(), 'compare', renderer_name),
          join_paths(meson.current_source_dir(), 'compare', testname + '.node'),
          join_paths(meson.current_source_dir(), 'compare', testname + '.png'),
        ],
        env: [
          'GSK_RENDERER=' + renderer_name,
          'GTK_A11Y=test',
          'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
          'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir())
        ],
        suite: suites + [ 'gsk-compare-masked-' + renderer_name ],
      )
    endif
  endforeach
endforeach

node_parser_tests = [
  'blend.node',
  'blend-unknown-mode.errors',
  'blend-unknown-mode.node',
  'blend-unknown-mode.ref.node',
  'border.node',
  'color.node',
  'conic-gradient.node',
  'conic-gradient.ref.node',
  'crash1.errors',
  'crash1.node',
  'crash1.ref.node',
  'crash2.errors',
  'crash2.node',
  'crash2.ref.node',
  'crash3.node',
  'crash3.ref.node',
  'crash4.errors',
  'crash4.node',
  'crash4.ref.node',
  'debug.node',
  'debug-fail.node',
  'debug-fail.ref.node',
  'debug-fail.errors',
  'empty-blend.node',
  'empty-blend.ref.node',
  'empty-blur.node',
  'empty-blur.ref.node',
  'empty-border.node',
  'empty-border.ref.node',
  'empty-cairo.node',
  'empty-cairo.ref.node',
  'empty-clip.node',
  'empty-clip.ref.node',
  'empty-color.node',
  'empty-color.ref.node',
  'empty-color-matrix.node',
  'empty-color-matrix.ref.node',
  'empty-container.node',
  'empty-container.ref.node',
  'empty-cross-fade.node',
  'empty-cross-fade.ref.node',
  'empty-debug.node',
  'empty-debug.ref.node',
  'empty-inset-shadow.node',
  'empty-inset-shadow.ref.node',
  'empty-linear-gradient.node',
  'empty-linear-gradient.ref.node',
  'empty-mask.node',
  'empty-mask.ref.node',
  'empty-opacity.node',
  'empty-opacity.ref.node',
  'empty-outset-shadow.node',
  'empty-outset-shadow.ref.node',
  'empty-repeat.node',
  'empty-repeat.ref.node',
  'empty-rounded-clip.node',
  'empty-rounded-clip.ref.node',
  'empty-shadow.node',
  'empty-shadow.ref.node',
  'empty-text.node',
  'empty-text.ref.node',
  'empty-texture.node',
  'empty-texture.ref.node',
  'empty-texture-scale.node',
  'empty-texture-scale.ref.node',
  'empty-transform.node',
  'empty-transform.ref.node',
  'glshader.node',
  'glshader.ref.node',
  'glshader.errors',
  'gradient-fail.node',
  'gradient-fail.ref.node',
  'gradient-fail.errors',
  'mask-modes.node',
  'mask-modes.ref.node',
  'node-names.node',
  'node-names-everywhere.errors',
  'node-names-everywhere.node',
  'node-names-everywhere.ref.node',
  'radial-gradient.node',
  'radial-gradient.ref.node',
  'repeating-linear-gradient.node',
  'repeating-linear-gradient.ref.node',
  'repeating-radial-gradient.node',
  'repeating-radial-gradient.ref.node',
  'rounded-rect.node',
  'shadow.node',
  'shadow-fail.node',
  'shadow-fail.ref.node',
  'shadow-fail.errors',
  'string-error.errors',
  'string-error.node',
  'string-error.ref.node',
  'testswitch.node',
  'text-fail.node',
  'text-fail.ref.node',
  'text-fail.errors',
  'texture-fail.node',
  'texture-fail.ref.node',
  'texture-fail.ref.errors',
  'texture-names.node',
  'texture-scale-filters.node',
  'texture-scale-filters.ref.node',
  'texture-scale-unknown-filter.errors',
  'texture-scale-unknown-filter.node',
  'texture-scale-unknown-filter.ref.node',
  'transform-fail.node',
  'transform-fail.ref.node',
  'transform-fail.errors',
  'widgetfactory.node',
]

foreach test : node_parser_tests
  if test.endswith('.node') and not test.endswith('.ref.node')
    test('parser ' + test, node_parser,
      args: [
        join_paths(meson.current_source_dir(), 'nodeparser', test)
      ],
      env: [
        'GSK_RENDERER=opengl',
        'GTK_A11Y=test',
        'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
        'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir())
      ],
      suite: 'gsk',
    )
  endif
endforeach

tests = [
  ['transform'],
  ['shader'],
]

test_cargs = []

foreach t : tests
  test_name = t.get(0)
  test_srcs = ['@0@.c'.format(test_name)] + t.get(1, [])
  test_extra_cargs = t.get(2, [])
  test_extra_ldflags = t.get(3, [])

  test_exe = executable(test_name, test_srcs,
    dependencies : libgtk_dep,
    c_args : test_cargs + test_extra_cargs + common_cflags,
    link_args : test_extra_ldflags,
  )

  test(test_name, test_exe,
    args: [ '--tap', '-k' ],
    protocol: 'tap',
    env: [
      'GSK_RENDERER=cairo',
      'GTK_A11Y=test',
      'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
      'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir())
    ],
    suite: 'gsk',
  )
endforeach

internal_tests = [
  [ 'diff' ],
  [ 'half-float' ],
  ['rounded-rect'],
  ['misc'],
]

foreach t : internal_tests
  test_name = t.get(0)
  test_srcs = ['@0@.c'.format(test_name)] + t.get(1, [])
  test_extra_cargs = t.get(2, [])
  test_extra_ldflags = t.get(3, [])

  test_exe = executable(test_name,
    sources: test_srcs,
    dependencies : libgtk_static_dep,
    c_args : test_cargs + test_extra_cargs + common_cflags + ['-DGTK_COMPILATION'],
    link_args : test_extra_ldflags,
  )

  test(test_name, test_exe,
    args: [ '--tap', '-k' ],
    protocol: 'tap',
    env: [
      'GSK_RENDERER=cairo',
      'GTK_A11Y=test',
      'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
      'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir())
    ],
    suite: 'gsk',
  )
endforeach


