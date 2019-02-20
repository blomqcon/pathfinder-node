#include <nan.h>
#include <pathfinder.h>

#include "PathfinderConvert.h"
// #include "WaypointObject.h"
// #include "SegmentObject.h"

// For debugging only:
#include <iostream>

// TODO: Download published Pathfinder binaries + headers.
// TODO: Reference + link aggainst Pathfinder-Core (binding.gyp).
// TODO: Reference and use Pathfinder-Core here.

void generateTrajectory (const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // std::cout << "Number of arguments: " << info.Length() << "\n";
  if (info.Length() != 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  v8::Local<v8::Array> waypointObjects = v8::Local<v8::Array>::Cast(info[0]);
  v8::Local<v8::Object> trajectoryConfigObject = v8::Local<v8::Array>::Cast(info[1]);

  // TODO: Remember to delete this memory
  int numWaypoints = waypointObjects->Length();
  Waypoint* waypoints = PathfinderConvert::allocateWaypoints(waypointObjects);
  
  TrajectoryCandidate candidate;
  pathfinder_prepare(waypoints, numWaypoints, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, 0.001, 15.0, 10.0, 60.0, &candidate);

  if (candidate.length <= 0)
  {
    // TODO: invalid waypoints + config
  }

  // TODO: Remember to Delete this memory
  Segment* trajectory = new Segment[candidate.length];
  pathfinder_generate(&candidate, trajectory);
  v8::Local<v8::Array> trajectoryArray = PathfinderConvert::createTrajectoryArray(trajectory, candidate.length);

  info.GetReturnValue().Set(trajectoryArray);
}

void generateTankTrajectories (const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() != 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  v8::Local<v8::Array> segmentObjects = v8::Local<v8::Array>::Cast(info[0]);
  v8::Local<v8::Number> wheelbaseWidthObject = v8::Local<v8::Number>::Cast(info[1]);

  double wheelbaseWidth = wheelbaseWidthObject->Value();
  Segment* trajectory = PathfinderConvert::allocateSegments(segmentObjects);

  int trajectoryLength = segmentObjects->Length();
  Segment* leftTrajectory = new Segment[trajectoryLength];
  Segment* rightTrajectory = new Segment[trajectoryLength];

  pathfinder_modify_tank(trajectory, trajectoryLength, leftTrajectory, rightTrajectory, wheelbaseWidth);

  v8::Local<v8::Array> leftTrajectoryArray = PathfinderConvert::createTrajectoryArray(leftTrajectory, trajectoryLength);
  v8::Local<v8::Array> rightTrajectoryArray = PathfinderConvert::createTrajectoryArray(rightTrajectory, trajectoryLength);

  v8::Local<v8::Object> trajectories = Nan::New<v8::Object>();
  Nan::Set(trajectories, Nan::New("leftTrajectory").ToLocalChecked(), leftTrajectoryArray);
  Nan::Set(trajectories, Nan::New("rightTrajectory").ToLocalChecked(), rightTrajectoryArray);
  
  info.GetReturnValue().Set(trajectories);
}

void serializeTrajectory(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() != 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  v8::Local<v8::String> filePathObject = v8::Local<v8::String>::Cast(info[0]);
  v8::Local<v8::Array> segmentObjects = v8::Local<v8::Array>::Cast(info[1]);

  char* filePath = (char*)malloc(filePathObject->Utf8Length());
  filePathObject->WriteUtf8(filePath, filePathObject->Utf8Length());
  

  //FILE* fp = fopen(filePath, "wb");
  FILE* fp = fopen("test_serialize.trajectory", "w+");
  Segment* trajectory = PathfinderConvert::allocateSegments(segmentObjects);
  std::cout << "Segements-To-Serialize: " << segmentObjects->Length() << "\n";
  //std::cout << "File-Path: " << filePath << "\n\n\n";
  
  //pathfinder_serialize_csv(fp, trajectory, segmentObjects->Length() - 1);
  pathfinder_serialize_csv(fp, trajectory, 50);
  std::cout << "Here Here Here " << "\n";

  delete trajectory;
  fclose(fp);

  info.GetReturnValue().SetUndefined();
}

void deserializeTrajectory(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() != 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  v8::Local<v8::String> filePathObject = v8::Local<v8::String>::Cast(info[0]);

  char* filePath = (char*)malloc(filePathObject->Utf8Length());
  filePathObject->WriteUtf8(filePath, filePathObject->Utf8Length());
  FILE *fp = fopen(filePath, "rb");

  // Pre allocate for a huge amount of segments
  // Note: This is the strategy pathfinder-java uses.
  Segment* segments = new Segment[4096];
  int length = pathfinder_deserialize(fp, segments);
  v8::Local<v8::Array> trajectoryArray = PathfinderConvert::createTrajectoryArray(segments, length);
  
  delete segments;
  fclose(fp);

  info.GetReturnValue().Set(trajectoryArray);
}

void Init(v8::Local<v8::Object> exports) {
  // WaypointObject::Init(exports);
  // SegmentObject::Init(exports);

  exports->Set(Nan::New("generateTrajectory").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(generateTrajectory)->GetFunction());

  exports->Set(Nan::New("generateTankTrajectories").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(generateTankTrajectories)->GetFunction());

  exports->Set(Nan::New("serializeTrajectory").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(serializeTrajectory)->GetFunction());

  exports->Set(Nan::New("deserializeTrajectory").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(deserializeTrajectory)->GetFunction());
}

// Module enterpoint: Called when the module is loaded.
NODE_MODULE(pathfinder_node, Init)
