
#include "TrajectoryObject.h"

// It would have been cool if this value was derived from the v8::Number type.
// However the default value comes from a magic number on the v8::Local type definition (v8.h).
#define WAYPOINT_DEFAULT_VALUE 0.0;

TrajectoryObject::TrajectoryObject(Segment value[])
    : value_(value)
{
}

TrajectoryObject::~TrajectoryObject()
{
}

NAN_MODULE_INIT(TrajectoryObject::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Trajectory").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    v8::Local<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
    Nan::SetAccessor(itpl, Nan::New("segments").ToLocalChecked(), GetSegments, SetSegments);
    
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Trajectory").ToLocalChecked(),
    Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(TrajectoryObject::New)
{
    if (info.IsConstructCall())
    {
        //double x = TrajectoryObject::GetNumberParameter(info, 0);
        
        Segment* value = new Segment[10];
        TrajectoryObject *obj = new TrajectoryObject(value);
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    else
    {
        const int argc = 3;
        v8::Local<v8::Value> argv[argc] = { info[0], info[1], info[2] };
        v8::Local<v8::Function> cons = Nan::New(constructor());
        Nan::MaybeLocal<v8::Object> instance = Nan::NewInstance(cons, argc, argv);
        if (!instance.IsEmpty())
        {
            info.GetReturnValue().Set(instance.ToLocalChecked());
        }
    }
}

NAN_GETTER(TrajectoryObject::GetSegments)
{
    TrajectoryObject* obj = Nan::ObjectWrap::Unwrap<TrajectoryObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_);
}

NAN_SETTER(TrajectoryObject::SetSegments)
{
    
    //TrajectoryObject* obj = Nan::ObjectWrap::Unwrap<TrajectoryObject>(info.Holder());
    //obj->value_.heading = TrajectoryObject::GetNumberSetter(value);
    //info.GetReturnValue().Set(obj->value_.heading);

    // TODO: consider making this throw an error
    //info.GetReturnValue().Set(null);
}