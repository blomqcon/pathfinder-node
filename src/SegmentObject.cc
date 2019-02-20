
#include "SegmentObject.h"

// It would have been cool if this value was derived from the v8::Number type.
// However the default value comes from a magic number on the v8::Local type definition (v8.h).
#define SEGMENT_DEFAULT_VALUE 0.0;

SegmentObject::SegmentObject(Segment value)
    : value_(value)
{
}

SegmentObject::~SegmentObject()
{
}

NAN_MODULE_INIT(SegmentObject::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Waypoint").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    //double dt, x, y, position, velocity, acceleration, jerk, heading;
    v8::Local<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
    Nan::SetAccessor(itpl, Nan::New("dt").ToLocalChecked(), GetDt, SetDt);
    Nan::SetAccessor(itpl, Nan::New("x").ToLocalChecked(), GetX, SetX);
    Nan::SetAccessor(itpl, Nan::New("y").ToLocalChecked(), GetY, SetY);
    Nan::SetAccessor(itpl, Nan::New("position").ToLocalChecked(), GetPosition, SetPosition);
    Nan::SetAccessor(itpl, Nan::New("velocity").ToLocalChecked(), GetVelocity, SetVelocity);
    Nan::SetAccessor(itpl, Nan::New("acceleration").ToLocalChecked(), GetAcceleration, SetAcceleration);
    Nan::SetAccessor(itpl, Nan::New("jerk").ToLocalChecked(), GetJerk, SetJerk);
    Nan::SetAccessor(itpl, Nan::New("heading").ToLocalChecked(), GetHeading, SetHeading);
    
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Segment").ToLocalChecked(),
    Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SegmentObject::New)
{
    if (info.IsConstructCall())
    {
        double dt = SegmentObject::GetNumberParameter(info, 0);
        double x = SegmentObject::GetNumberParameter(info, 1);
        double y = SegmentObject::GetNumberParameter(info, 2);
        double position = SegmentObject::GetNumberParameter(info, 3);
        double velocity = SegmentObject::GetNumberParameter(info, 4);
        double acceleration = SegmentObject::GetNumberParameter(info, 5);
        double jerk = SegmentObject::GetNumberParameter(info, 6);
        double heading = SegmentObject::GetNumberParameter(info, 7);
        
        Segment value = { dt, x, y, position, velocity, acceleration, jerk, heading };
        SegmentObject *obj = new SegmentObject(value);
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

NAN_GETTER(SegmentObject::GetDt)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.dt);
}

NAN_SETTER(SegmentObject::SetDt)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    obj->value_.dt = SegmentObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.dt);
}

NAN_GETTER(SegmentObject::GetX)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.x);
}

NAN_SETTER(SegmentObject::SetX)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    obj->value_.x = SegmentObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.x);
}

NAN_GETTER(SegmentObject::GetY)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.y);
}

NAN_SETTER(SegmentObject::SetY)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    obj->value_.y = SegmentObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.y);
}

NAN_GETTER(SegmentObject::GetPosition)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.position);
}

NAN_SETTER(SegmentObject::SetPosition)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    obj->value_.position = SegmentObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.position);
}

NAN_GETTER(SegmentObject::GetVelocity)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.velocity);
}

NAN_SETTER(SegmentObject::SetVelocity)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    obj->value_.velocity = SegmentObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.velocity);
}

NAN_GETTER(SegmentObject::GetAcceleration)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.acceleration);
}

NAN_SETTER(SegmentObject::SetAcceleration)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    obj->value_.acceleration = SegmentObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.acceleration);
}

NAN_GETTER(SegmentObject::GetJerk)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.jerk);
}

NAN_SETTER(SegmentObject::SetJerk)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    obj->value_.jerk = SegmentObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.jerk);
}

NAN_GETTER(SegmentObject::GetHeading)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.heading);
}

NAN_SETTER(SegmentObject::SetHeading)
{
    SegmentObject* obj = Nan::ObjectWrap::Unwrap<SegmentObject>(info.Holder());
    obj->value_.heading = SegmentObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.heading);
}

double SegmentObject::GetNumberParameter(Nan::NAN_METHOD_ARGS_TYPE info, int paramIndex)
{
    if (info[paramIndex]->IsUndefined())
        return SEGMENT_DEFAULT_VALUE;

    if (!info[paramIndex]->IsNumber())
    {
        Nan::ThrowTypeError("Number parameter expected");
        return 0;
    }

    return Nan::To<double>(info[paramIndex]).FromJust();
}

double SegmentObject::GetNumberSetter(v8::Local<v8::Value> value)
{
    if (!value->IsNumber())
    {
        Nan::ThrowTypeError("Property only supports numbers");
        return -10;
    }

    return Nan::To<double>(value).FromJust();
}