{
  "variables": {
    "pathfinder_root%": "C:/dev/Robotics/pathfinder-node/native-lib/pathfinder-core/2019.1.12/windowsx86-64"
  },
  "targets": [
    {
      "target_name": "pathfinder-node",
      "sources": [
        "src/pathfinder-node.cc",
        "src/PathfinderConvert.cc",
        "src/WaypointObject.cc",
      ],
      "libraries": [  ],
      'library_dirs': [
        # "native-lib/pathfinder-core/2019.1.11/windowsx86-64"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "native-lib/pathfinder-core/2019.1.12/headers"
      ],
      'link_settings': {
        'libraries': ['-l<@(pathfinder_root)/pathfinder'],
        "ldflags": [
            "-L<@(pathfinder_root)",
            "-Wl,-rpath,<@(pathfinder_root)",
        ]
      },
    }
  ]
}