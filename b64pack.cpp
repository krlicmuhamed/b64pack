#include <node.h>
#include "b64pack.h"

using namespace v8;


Handle<Value> Compress(const Arguments& args) {
    HandleScope scope;

    // Ensure that we got a callback. Generally, your functions should have
    // optional callbacks. In this case, you can declare an empty
    // Local<Function> handle and check for content before calling.
    if (!args[1]->IsFunction()) {
        return ThrowException(Exception::TypeError(
            String::New("Second argument must be a callback function")));
    }
    // There's no a ToFunction(), use a Cast instead. This is the second argument.
    Local<Function> callback = Local<Function>::Cast(args[1]);

    // First argument is a string.
    String::AsciiValue arg0(args[0]->ToString());
    char* msg = (char*) *arg0;
    size_t msglen = sizeof(msg);

    bool ok = false;
    try{
      b64pack_compress(msg, &msglen);
      ok = true;
    }catch(const char* ex){
      ok = false;
      Local<Value> err = Exception::Error(String::New(ex));

      const unsigned argc = 1;
      Local<Value> argv[argc] = { err };

      callback->Call(Context::GetCurrent()->Global(), argc, argv);
    }

    if(ok) {
      // In case the operation succeeded, convention is to pass null as the
      // first argument before the result arguments.
      const unsigned argc = 2;
      Local<Value> argv[argc] = {
          Local<Value>::New(Null() ),
          Local<Value>::New(String::New(msg->ToString() ));
      };

      // Note: When calling this in an asynchronous function that just returned
      // from the threadpool, you have to wrap this in a v8::TryCatch.
      // You can also pass another handle as the "this" parameter.
      callback->Call(Context::GetCurrent()->Global(), argc, argv);
    }

    return Undefined();
}

Handle<Value> Decompress(const Arguments& args) {
    HandleScope scope;

    // Ensure that we got a callback. Generally, your functions should have
    // optional callbacks. In this case, you can declare an empty
    // Local<Function> handle and check for content before calling.
    if (!args[1]->IsFunction()) {
        return ThrowException(Exception::TypeError(
            String::New("Second argument must be a callback function")));
    }
    // There's no a ToFunction(), use a Cast instead. This is the second argument.
    Local<Function> callback = Local<Function>::Cast(args[1]);

    // First argument is a string.
    String::AsciiValue arg0(args[0]->ToString());
    char* msg = (char*) *arg0;
    size_t msglen = sizeof(msg);

    bool ok = false;
    try{
      b64pack_decompress(msg, &msglen);
      ok = true;
    }catch(const char* ex){
      ok = false;
      Local<Value> err = Exception::Error(String::New(ex));

      const unsigned argc = 1;
      Local<Value> argv[argc] = { err };

      callback->Call(Context::GetCurrent()->Global(), argc, argv);
    }

    if(ok) {
      // In case the operation succeeded, convention is to pass null as the
      // first argument before the result arguments.
      const unsigned argc = 2;
      Local<Value> argv[argc] = {
          Local<Value>::New(Null() ),
          Local<Value>::New(String::New(msg->ToString() ));
      };

      // Note: When calling this in an asynchronous function that just returned
      // from the threadpool, you have to wrap this in a v8::TryCatch.
      // You can also pass another handle as the "this" parameter.
      callback->Call(Context::GetCurrent()->Global(), argc, argv);
    }

    return Undefined();
}

void RegisterModule(Handle<Object> target) {
    target->Set(String::NewSymbol("compress"),
        FunctionTemplate::New(Compress)->GetFunction());

    target->Set(String::NewSymbol("decompress"),
        FunctionTemplate::New(Decompress)->GetFunction());
}

NODE_MODULE(b64pack, RegisterModule);
