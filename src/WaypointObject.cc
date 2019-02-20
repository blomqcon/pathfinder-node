
#include "WaypointObject.h"

// It would have been cool if this value was derived from the v8::Number type.
// However the default value comes from a magic number on the v8::Local type definition (v8.h).
#define WAYPOINT_DEFAULT_VALUE 0.0;

WaypointObject::WaypointObject(Waypoint value)
    : value_(value)
{
}

WaypointObject::~WaypointObject()
{
}

NAN_MODULE_INIT(WaypointObject::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Waypoint").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    v8::Local<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
    Nan::SetAccessor(itpl, Nan::New("x").ToLocalChecked(), GetX, SetX);
    Nan::SetAccessor(itpl, Nan::New("y").ToLocalChecked(), GetY, SetY);
    Nan::SetAccessor(itpl, Nan::New("angle").ToLocalChecked(), GetAngle, SetAngle);
    
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Waypoint").ToLocalChecked(),
    Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(WaypointObject::New)
{
    if (info.IsConstructCall())
    {
        double x = WaypointObject::GetNumberParameter(info, 0);
        double y = WaypointObject::GetNumberParameter(info, 1);
        double angle = WaypointObject::GetNumberParameter(info, 2);
        
        Waypoint value = { x, y, angle };
        WaypointObject *obj = new WaypointObject(value);
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

NAN_GETTER(WaypointObject::GetX)
{
    WaypointObject* obj = Nan::ObjectWrap::Unwrap<WaypointObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.x);
}

NAN_SETTER(WaypointObject::SetX)
{
    WaypointObject* obj = Nan::ObjectWrap::Unwrap<WaypointObject>(info.Holder());
    obj->value_.x = WaypointObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.x);
}

NAN_GETTER(WaypointObject::GetY)
{
    WaypointObject* obj = Nan::ObjectWrap::Unwrap<WaypointObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.y);
}

NAN_SETTER(WaypointObject::SetY)
{
    WaypointObject* obj = Nan::ObjectWrap::Unwrap<WaypointObject>(info.Holder());
    obj->value_.y = WaypointObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.y);
}

NAN_GETTER(WaypointObject::GetAngle)
{
    WaypointObject* obj = Nan::ObjectWrap::Unwrap<WaypointObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_.angle);
}

NAN_SETTER(WaypointObject::SetAngle)
{
    WaypointObject* obj = Nan::ObjectWrap::Unwrap<WaypointObject>(info.Holder());
    obj->value_.angle = WaypointObject::GetNumberSetter(value);
    info.GetReturnValue().Set(obj->value_.angle);
}

double WaypointObject::GetNumberParameter(Nan::NAN_METHOD_ARGS_TYPE info, int paramIndex)
{
    if (info[paramIndex]->IsUndefined())
        return WAYPOINT_DEFAULT_VALUE;

    if (!info[paramIndex]->IsNumber())
    {
        Nan::ThrowTypeError("Number parameter expected");
        return 0;
    }

    return Nan::To<double>(info[paramIndex]).FromJust();
}

double WaypointObject::GetNumberSetter(v8::Local<v8::Value> value)
{
    if (!value->IsNumber())
    {
        Nan::ThrowTypeError("Property only supports numbers");
        return -10;
    }

    return Nan::To<double>(value).FromJust();
}