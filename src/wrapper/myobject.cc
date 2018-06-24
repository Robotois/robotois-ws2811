// myobject.cc
#include "myobject.h"
#include "../robotois-ws2811.h"

using v8::Exception;
using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;

Persistent<Function> MyObject::constructor;

MyObject::MyObject(int width, int height, uint8_t brightness, uint8_t pin) {
  ledStripInit(width, height, brightness, pin);
}

MyObject::~MyObject() {
}

void MyObject::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  // NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ledOn", ledOn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ledOff", ledOff);
  NODE_SET_PROTOTYPE_METHOD(tpl, "allLedOn", allLedOn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "allLedOff", allLedOff);
  NODE_SET_PROTOTYPE_METHOD(tpl, "release", release);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "MyObject"),
               tpl->GetFunction());
}

void MyObject::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  int width, height, brightness, gpio;
  MyObject *obj;
  uint8_t _argc = args.Length();
  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    // double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    switch (_argc) {
      case 0:
        obj = new MyObject();
        break;
      case 1: // Led strip
        width = (int) args[0]-> NumberValue();
        obj = new MyObject(width, 1);
        break;
      case 2: // Led strip with brightness
        width = (int) args[0]-> NumberValue();
        brightness = (int) args[1]-> NumberValue();
        obj = new MyObject(width, 1, brightness);
        break;
      case 3: // Led strip with brightness
        width = (int) args[0]-> NumberValue();
        height = (int) args[1]-> NumberValue();
        brightness = (int) args[2]-> NumberValue();
        obj = new MyObject(width, height, brightness);
        break;
      case 4: // Led strip with brightness
        width = (int) args[0]-> NumberValue();
        height = (int) args[1]-> NumberValue();
        brightness = (int) args[2]-> NumberValue();
        gpio = (int) args[3]-> NumberValue();
        obj = new MyObject(width, height, brightness, gpio);
        break;
      default:
        obj = new MyObject();
    }
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Context> context = isolate->GetCurrentContext();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Object> result =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
  }
}

void MyObject::ledOn(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  int ledNumber = 0;
  uint8_t red, green, blue;
  // Check the number of arguments passed.
  if (args.Length() == 4) {
    ledNumber = (int) args[0]->NumberValue();
    red = (uint8_t) args[1]->NumberValue();
    green = (uint8_t) args[2]->NumberValue();
    blue = (uint8_t) args[3]->NumberValue();
  } else {
    red = (uint8_t) args[0]->NumberValue();
    green = (uint8_t) args[1]->NumberValue();
    blue = (uint8_t) args[2]->NumberValue();
  }

  // Perform the operation
  turnOn(ledNumber, blue, green, red);
}

void MyObject::allLedOn(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Perform the operation
  uint8_t red = (uint8_t) args[0]->NumberValue(),
    green = (uint8_t) args[1]->NumberValue(),
    blue = (uint8_t) args[2]->NumberValue();

  allOn(blue, green, red);
}

void MyObject::ledOff(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  int ledNumber = 0;
  // Check the number of arguments passed.
  if (args.Length() == 1) {
    ledNumber = (int) args[0]->NumberValue();
  }

  // Perform the operation
  turnOff(ledNumber);
}

void MyObject::allLedOff(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  allOff();
}

void MyObject::release(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Perform the operation
  ledStripRelease();
}
