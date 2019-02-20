#include <nan.h>
#include <pathfinder.h>

// #include "WaypointObject.h"
// #include "SegmentObject.h"

// For debugging only:
#include <iostream>

// TODO: Download published Pathfinder binaries + headers.
// TODO: Reference + link aggainst Pathfinder-Core (binding.gyp).
// TODO: Reference and use Pathfinder-Core here.

void GenerateTrajectory (const Nan::FunctionCallbackInfo<v8::Value>& info) {
  std::cout << "Number of arguments: " << info.Length() << "\n";

  if (info.Length() != 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  v8::Local<v8::Array> waypointObjects = v8::Local<v8::Array>::Cast(info[0]);
  v8::Local<v8::Object> trajectoryConfigObject = v8::Local<v8::Array>::Cast(info[1]);

  // TODO: Remember to delete this memory
  Waypoint* waypoints = new Waypoint[waypointObjects->Length()];
  for (unsigned int i = 0; i < waypointObjects->Length(); i++)
  {
    v8::Local<v8::Object> waypointObject = waypointObjects->Get(i).As<v8::Object>();

    // TODO: Be more error tolerent
    v8::MaybeLocal<v8::Value> xValue = waypointObject->GetRealNamedProperty(Nan::GetCurrentContext(), Nan::New("x").ToLocalChecked());
    v8::MaybeLocal<v8::Value> yValue = waypointObject->GetRealNamedProperty(Nan::GetCurrentContext(), Nan::New("y").ToLocalChecked());
    v8::MaybeLocal<v8::Value> angleValue = waypointObject->GetRealNamedProperty(Nan::GetCurrentContext(), Nan::New("angle").ToLocalChecked());

    v8::Local<v8::Number> xNumber = xValue.ToLocalChecked().As<v8::Number>();
    v8::Local<v8::Number> yNumber = yValue.ToLocalChecked().As<v8::Number>();
    v8::Local<v8::Number> angleNumber = angleValue.ToLocalChecked().As<v8::Number>();

    waypoints[i] = { xNumber->Value(), yNumber->Value(), angleNumber->Value() };
  }

  TrajectoryCandidate candidate;
  pathfinder_prepare(waypoints, waypointObjects->Length(), FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, 0.001, 15.0, 10.0, 60.0, &candidate);

  // TODO: need to free trjacetory
  int length = candidate.length;
  Segment *trajectory = new Segment[length];
  //pathfinder_generate(&candidate, trajectory);

  v8::Local<v8::Array> trajectoryArray = Nan::New<v8::Array>();
  for (int i = 0; i < length; i++ ) {
    Segment segment = trajectory[i];
    v8::Local<v8::Object> segmentObject = Nan::New<v8::Object>();
    
    Nan::Set(segmentObject, Nan::New("dt").ToLocalChecked(), Nan::New(segment.dt));
    Nan::Set(segmentObject, Nan::New("x").ToLocalChecked(), Nan::New(segment.x));
    Nan::Set(segmentObject, Nan::New("y").ToLocalChecked(), Nan::New(segment.y));
    Nan::Set(segmentObject, Nan::New("position").ToLocalChecked(), Nan::New(segment.position));
    Nan::Set(segmentObject, Nan::New("velocity").ToLocalChecked(), Nan::New(segment.velocity));
    Nan::Set(segmentObject, Nan::New("acceleration").ToLocalChecked(), Nan::New(segment.acceleration));
    Nan::Set(segmentObject, Nan::New("jerk").ToLocalChecked(), Nan::New(segment.jerk));
    Nan::Set(segmentObject, Nan::New("heading").ToLocalChecked(), Nan::New(segment.heading));

    trajectoryArray->Set(i, segmentObject);
  }

  info.GetReturnValue().Set(trajectoryArray);
}

void Init(v8::Local<v8::Object> exports) {
  // WaypointObject::Init(exports);
  // SegmentObject::Init(exports);

  exports->Set(Nan::New("GenerateTrajectory").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GenerateTrajectory)->GetFunction());
}

// Module enterpoint: Called when the module is loaded.
NODE_MODULE(pathfinder_node, Init)
