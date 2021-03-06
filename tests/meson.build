subdir('dummyatk')

xmlloader = static_library('xmlloader', [ 'atk-object-xml-loader.c' ],
                           dependencies: [ glib_dep, gobject_dep, libxml_dep, atk_dep, dummyatk_dep ],
                           include_directories: [ root_inc, include_directories('.') ])
xmlloader_dep = declare_dependency(link_with: xmlloader)

testutils = static_library('testutils', [ 'atk_test_util.c' ],
                           dependencies: [ glib_dep, atspi_dep ],
                           include_directories: [ root_inc, include_directories('.') ])
testutils_dep = declare_dependency(link_with: testutils)

# tests:
#  - name
#  - sources
#  - dependencies
tests = [
  [
    'atk-test', [
      'atk_suite.c',
      'atk_test_accessible.c',
      'atk_test_action.c',
      'atk_test_component.c',
      'atk_test_collection.c',
      'atk_test_document.c',
      'atk_test_editable_text.c',
      'atk_test_hyperlink.c',
      'atk_test_hypertext.c',
      'atk_test_image.c',
      'atk_test_selection.c',
      'atk_test_state_set.c',
      'atk_test_table.c',
      'atk_test_table_cell.c',
      'atk_test_text.c',
      'atk_test_value.c',
    ],
    [
      glib_dep,
      atspi_dep,
      xmlloader_dep,
      testutils_dep,
      dummyatk_dep,
    ]
  ],

  [
    'app-test',
    [
      'test-application.c',
    ],
    [
      glib_dep,
      atk_dep,
      xmlloader_dep,
      testutils_dep,
      dummyatk_dep,
      libatk_bridge_dep,
    ]
  ],
]

foreach t: tests
  test_name = t[0]
  test_sources = t[1]
  test_deps = t[2]

  test_bin = executable(test_name, test_sources,
                        dependencies: test_deps,
                        include_directories: root_inc,
                        c_args: [
                          '-DTESTS_BUILD_DIR="@0@"'.format(meson.current_build_dir()),
                          '-DTESTS_SRC_DIR="@0@"'.format(meson.current_source_dir()),
                          '-DTESTS_DATA_DIR="@0@"'.format(join_paths(meson.current_source_dir(), 'data')),
                        ])
endforeach
